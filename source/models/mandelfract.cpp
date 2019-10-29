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

#include "models/mandelfract.hpp"

#include <random>

#include "clpp/core.hpp"
#include "clpp/shader.hpp"
#include "controllers/mandelfract.hpp"
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

MandelfractModel::MandelfractModel(std::shared_ptr<clpp::Core> cl_core)
    : cl_core_(cl_core),
      scale_coefficient_(0.004),
      offset_(std::make_pair(-0.5, 0)),
      color_coefficients_(std::make_tuple(9.0, 15, 8.5)),
      change_color_automaticaly_(false),
      color_change_speed_(0.1F) {}

MandelfractModel::~MandelfractModel() { event_handler_.lock()->UnregisterEventCallbacks(registered_callbacks_); }

void MandelfractModel::Create() {
    const auto& ubuntu12_font = resources_manager_.lock()->LoadFont("Ubuntu12", "resources/fonts/ubuntu.ttf", 12);
    const auto& app_icon = resources_manager_.lock()->LoadImage("AppIcon", "resources/images/icon.png");

    try {
        cl_shader_ = cl_core_->GetPlatform("nvidia")->LoadShader({"resources/shaders/mandelfract.cl"});
    } catch (const clpp::cl_error&) {
        cl_shader_ = cl_core_->GetPlatform()->LoadShader({"resources/shaders/mandelfract.cl"});
    }

    try {
        cl_shader_->BuildFor(CL_DEVICE_TYPE_GPU);
    } catch (const clpp::cl_error&) {
        cl_shader_->Build();
    }

    window_ = windows_manager_.lock()->CreateWindow<zzgui::SDLWindow>("Mandelbrot Fractal", 800, 600);
    auto window_id = window_.lock()->GetId();
    window_.lock()->IfClosed(std::bind(&MandelfractController::OnWindowClose, GetController().lock().get(), _1));

    window_.lock()->SetIcon(app_icon);

    GetController().lock()->RegisterWindow(window_);

    registered_callbacks_.emplace_back(event_handler_.lock()->RegisterEventCallback<zzgui::KeyboardEvent>(
        std::bind(&MandelfractController::OnKeyboard, GetController().lock().get(), _1), window_.lock()->GetId()));
    registered_callbacks_.emplace_back(event_handler_.lock()->RegisterEventCallback<zzgui::MouseWheelEvent>(
        std::bind(&MandelfractController::OnMouseWheel, GetController().lock().get(), _1), window_.lock()->GetId()));

    widgets_manager_ = std::make_shared<zzgui::WidgetsManager>(event_handler_);

    fps_counter_ = widgets_manager_->Create<zzgui::Label>(window_id, "", ubuntu12_font, 0, 0);
    fps_counter_->SetPosition(0, window_.lock()->GetHeight() - fps_counter_->GetSize().second);
}

void MandelfractModel::Update(float delta) {
    thread_local static float update;

    fps_counter_->SetText(std::to_string((uint64_t)(1.0 / delta)) + "FPS");

    if (change_color_automaticaly_) {
        update += delta;
        if (update >= color_change_speed_) {
            RandomizeColor();
            update = 0;
        }
    }

    auto canvas = window_.lock()->GetCanvas().lock();
    const auto& canvas_width = canvas->GetWidth();
    const auto& canvas_height = canvas->GetHeight();

    cl_shader_->Calculate("fill_mandelfract", canvas->GetRawPixels(), canvas_height * canvas->GetPitch(),
                          {canvas_width, canvas_height}, offset_.first, offset_.second, scale_coefficient_,
                          canvas_width, canvas_height);
}

void MandelfractModel::SetScaleCoeficient(double value) { scale_coefficient_ = value; }

void MandelfractModel::IncScaleCoeficient(double value) { scale_coefficient_ += value; }

void MandelfractModel::SetOffset(double offset_x, double offset_y) {
    offset_.first = offset_x;
    offset_.second = offset_y;
}

namespace {
inline constexpr double lerp(double v0, double v1, double t) { return (1 - t) * v0 + t * v1; }
}  // namespace

void MandelfractModel::Move(int8_t mult_x, int8_t mult_y) {
    offset_.first += mult_x * scale_coefficient_ * kAmplification;
    offset_.second += mult_y * scale_coefficient_ * kAmplification;
}

void MandelfractModel::Zoom(bool in) { Zoom(window_.lock()->GetWidth() / 2.0, window_.lock()->GetHeight() / 2.0, in); }

void MandelfractModel::Zoom(uint64_t x, uint64_t y, bool in) {
    if (in) {
        offset_.first =
            lerp(offset_.first, offset_.first + (x - window_.lock()->GetWidth() / 2.0) * scale_coefficient_, 0.05);
        offset_.second =
            lerp(offset_.second, offset_.second + (y - window_.lock()->GetHeight() / 2.0) * scale_coefficient_, 0.05);
        scale_coefficient_ -= scale_coefficient_ / kAmplification;
    } else {
        scale_coefficient_ += scale_coefficient_ / kAmplification;
    }
}

void MandelfractModel::RandomizeColor() {
    static thread_local std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> r(1.0, 8.0);
    std::uniform_real_distribution<double> g(1.0, 15.0);
    std::uniform_real_distribution<double> b(1.0, 10.0);

    std::get<0>(color_coefficients_) = r(mt);
    std::get<1>(color_coefficients_) = g(mt);
    std::get<2>(color_coefficients_) = b(mt);
}

void MandelfractModel::IncColorChangeSpeed(double value) { color_change_speed_ += value; }

void MandelfractModel::ToogleChangeColor() { change_color_automaticaly_ ^= true; }

std::weak_ptr<zzgui::Window> MandelfractModel::GetWindow() const { return window_; }

std::weak_ptr<zzgui::WidgetsManager> MandelfractModel::GetWidgetsManager() const { return widgets_manager_; }

double MandelfractModel::GetScaleCoeficient() const { return scale_coefficient_; }

const std::pair<double, double>& MandelfractModel::GetOffset() const { return offset_; }

const std::tuple<double, double, double>& MandelfractModel::GetColorCoefficients() const { return color_coefficients_; }

}  // namespace cozz
