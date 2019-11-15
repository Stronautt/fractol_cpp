/*
 * This file is part of Fractol.

 * Fractol is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Fractol is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Fractol. If not, see <https://www.gnu.org/licenses/>.
 *
 * Author: Pavlo Hrytsenko
*/

#include "models/algebraic_fractal.hpp"

#include <random>
#include <sstream>

#include "clpp/core.hpp"
#include "clpp/exception.hpp"
#include "clpp/shader.hpp"
#include "controllers/algebraic_fractal.hpp"
#include "controllers_manager.hpp"
#include "event/quit_event.hpp"
#include "event/window_event.hpp"
#include "resources_manager.hpp"
#include "sdl_window.hpp"
#include "widget.hpp"
#include "widgets/button.hpp"
#include "widgets/image.hpp"
#include "widgets/label.hpp"
#include "widgets_manager.hpp"
#include "windows_manager.hpp"

using std::placeholders::_1;

namespace cozz {

AlgebraicFractalModel::AlgebraicFractalModel(const std::string& name, std::shared_ptr<clpp::Core> cl_core,
                                             std::shared_ptr<clpp::Platform> cl_platform, Parameters parameters,
                                             const std::vector<std::string>& source_paths)
    : name_(name),
      cl_core_(cl_core),
      cl_platform_(cl_platform),
      parameters_(parameters),
      source_paths_(source_paths),
      follow_mouse_(false) {
    if (!cl_core_ || !cl_platform_) {
        throw clpp::cl_error("OpenCL is not availiable");
    }
}

AlgebraicFractalModel::~AlgebraicFractalModel() {
    event_handler_.lock()->UnregisterEventCallbacks(registered_callbacks_);
}

void AlgebraicFractalModel::Create() {
    const auto& ubuntu10_font = resources_manager_.lock()->LoadFont("Ubuntu10", "resources/fonts/ubuntu.ttf", 10);
    const auto& ubuntu14_font =
        resources_manager_.lock()->LoadFont("Ubuntu14", "resources/fonts/fonts_awesome.ttf", 14);
    const auto& app_icon = resources_manager_.lock()->LoadImage("AppIcon", "resources/images/icon.png");
    const std::string build_options = "-I resources/shaders -cl-std=CL1.2";

    cl_shader_ = cl_platform_->LoadShader(source_paths_);
    cl_platform_->BuildShader(cl_shader_, build_options);

    window_ = windows_manager_.lock()->CreateWindow<zzgui::SDLWindow>(name_.c_str(), 800, 600);
    auto window_id = window_.lock()->GetId();
    window_.lock()->IfClosed(std::bind(&AlgebraicFractalController::OnWindowClose, GetController().lock().get(), _1));

    window_.lock()->SetIcon(app_icon);

    GetController().lock()->RegisterWindow(window_);

    registered_callbacks_.emplace_back(event_handler_.lock()->RegisterEventCallback<zzgui::KeyboardEvent>(
        std::bind(&AlgebraicFractalController::OnKeyboard, GetController().lock().get(), _1), window_.lock()->GetId()));
    registered_callbacks_.emplace_back(event_handler_.lock()->RegisterEventCallback<zzgui::MouseButtonEvent>(
        std::bind(&AlgebraicFractalController::OnMouseButton, GetController().lock().get(), _1),
        window_.lock()->GetId()));
    registered_callbacks_.emplace_back(event_handler_.lock()->RegisterEventCallback<zzgui::MouseMotionEvent>(
        std::bind(&AlgebraicFractalController::OnMouseMotion, GetController().lock().get(), _1),
        window_.lock()->GetId()));
    registered_callbacks_.emplace_back(event_handler_.lock()->RegisterEventCallback<zzgui::MouseWheelEvent>(
        std::bind(&AlgebraicFractalController::OnMouseWheel, GetController().lock().get(), _1),
        window_.lock()->GetId()));

    widgets_manager_ = std::make_shared<zzgui::WidgetsManager>(event_handler_);

    fps_counter_ = widgets_manager_->Create<zzgui::Label>(window_id, 0, "", ubuntu10_font, 0, 0);
    fps_counter_.lock()->SetForegroundColor({0xFF, 0xFF, 0xFF});
    fps_counter_.lock()->SetPosition(0, window_.lock()->GetHeight() - fps_counter_.lock()->GetSize().second);

    fractal_info_.depth = widgets_manager_->Create<zzgui::Label>(window_id, 0, "", ubuntu10_font, 0, 0);
    fractal_info_.depth.lock()->SetForegroundColor({0xFF, 0xFF, 0xFF});
    fractal_info_.depth.lock()->SetBorderColor({0, 0, 0, 0});
    fractal_info_.depth.lock()->SetPadding(4, 0);

    fractal_info_.scale_coefficient = widgets_manager_->Create<zzgui::Label>(
        window_id, 0, "", ubuntu10_font, 0,
        fractal_info_.depth.lock()->GetPosition().second + fractal_info_.depth.lock()->GetSize().second);
    fractal_info_.scale_coefficient.lock()->SetForegroundColor({0xFF, 0xFF, 0xFF});
    fractal_info_.scale_coefficient.lock()->SetBorderColor({0, 0, 0, 0});
    fractal_info_.scale_coefficient.lock()->SetPadding(4, 0);

    fractal_info_.pivot =
        widgets_manager_->Create<zzgui::Label>(window_id, 0, "", ubuntu10_font, 0,
                                               fractal_info_.scale_coefficient.lock()->GetPosition().second +
                                                   fractal_info_.scale_coefficient.lock()->GetSize().second);
    fractal_info_.pivot.lock()->SetForegroundColor({0xFF, 0xFF, 0xFF});
    fractal_info_.pivot.lock()->SetBorderColor({0, 0, 0, 0});
    fractal_info_.pivot.lock()->SetPadding(4, 0);

    fractal_info_.dynamic_coefficients = widgets_manager_->Create<zzgui::Label>(
        window_id, 0, "", ubuntu10_font, 0,
        fractal_info_.pivot.lock()->GetPosition().second + fractal_info_.pivot.lock()->GetSize().second);
    fractal_info_.dynamic_coefficients.lock()->SetForegroundColor({0xFF, 0xFF, 0xFF});
    fractal_info_.dynamic_coefficients.lock()->SetBorderColor({0, 0, 0, 0});
    fractal_info_.dynamic_coefficients.lock()->SetPadding(4, 0);
}

namespace {

template <class T>
std::string ToString(T arg) {
    std::ostringstream stream;
    stream << arg;
    return stream.str();
}

}  // namespace

void AlgebraicFractalModel::Update(float delta) {
    fps_counter_.lock()->SetText(std::to_string((uint64_t)(1.0 / delta)) + "FPS");
    fractal_info_.depth.lock()->SetText("Depth: " + ToString(parameters_.depth));
    fractal_info_.scale_coefficient.lock()->SetText("Scale coefficient: " + ToString(parameters_.scale_coefficient));
    fractal_info_.pivot.lock()->SetText("Pivot: (" + std::to_string(parameters_.pivot.x) + ";" +
                                        ToString(parameters_.pivot.y) + ")");
    fractal_info_.dynamic_coefficients.lock()->SetText("Dynamic coefficients: (" + std::to_string(parameters_.c.x) +
                                                       ";" + ToString(parameters_.c.y) + ")");

    auto canvas = window_.lock()->GetCanvas().lock();
    const auto& canvas_width = canvas->GetWidth();
    const auto& canvas_height = canvas->GetHeight();

    cl_shader_->Calculate("compute_fractal", canvas->GetRawPixels(), canvas_height * canvas->GetPitch(),
                          {canvas_width, canvas_height}, parameters_);
}

void AlgebraicFractalModel::IncScaleCoeficient(double value) { parameters_.scale_coefficient += value; }

namespace {
inline constexpr double lerp(double v0, double v1, double t) { return (1 - t) * v0 + t * v1; }
}  // namespace

void AlgebraicFractalModel::Drag(double x_dir, double y_dir) { Move(x_dir / kAmplification, y_dir / kAmplification); }

void AlgebraicFractalModel::Move(double mult_x, double mult_y) {
    parameters_.pivot.x += mult_x * parameters_.scale_coefficient * kAmplification;
    parameters_.pivot.y += mult_y * parameters_.scale_coefficient * kAmplification;
}

void AlgebraicFractalModel::Zoom(bool in) {
    Zoom(window_.lock()->GetWidth() / 2.0, window_.lock()->GetHeight() / 2.0, in);
}

void AlgebraicFractalModel::Zoom(uint64_t x, uint64_t y, bool in) {
    if (in) {
        parameters_.pivot.x =
            lerp(parameters_.pivot.x,
                 parameters_.pivot.x + (x - window_.lock()->GetWidth() / 2.0) * parameters_.scale_coefficient, 0.05);
        parameters_.pivot.y =
            lerp(parameters_.pivot.y,
                 parameters_.pivot.y + (y - window_.lock()->GetHeight() / 2.0) * parameters_.scale_coefficient, 0.05);
        parameters_.scale_coefficient -= parameters_.scale_coefficient / kAmplification;
    } else {
        parameters_.scale_coefficient += parameters_.scale_coefficient / kAmplification;
    }
}

void AlgebraicFractalModel::IncDepth(uint16_t value) { parameters_.depth += value; }

void AlgebraicFractalModel::RandomizeColor() {
    static thread_local std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> r(1.0, 8.0);
    std::uniform_real_distribution<double> g(1.0, 15.0);
    std::uniform_real_distribution<double> b(1.0, 10.0);

    parameters_.color_coefficients.r = r(mt);
    parameters_.color_coefficients.g = g(mt);
    parameters_.color_coefficients.b = b(mt);
}

void AlgebraicFractalModel::FollowMouse(uint64_t x, uint64_t y) {
    if (follow_mouse_) {
        const auto& window = window_.lock();
        parameters_.c.x = -1.4 * x / window->GetWidth();
        parameters_.c.y = 0.5403 * y / window->GetHeight();
    }
}

void AlgebraicFractalModel::ToogleMouseFollowing() { follow_mouse_ ^= true; }

std::weak_ptr<zzgui::Window> AlgebraicFractalModel::GetWindow() const { return window_; }

std::weak_ptr<zzgui::WidgetsManager> AlgebraicFractalModel::GetWidgetsManager() const { return widgets_manager_; }

}  // namespace cozz
