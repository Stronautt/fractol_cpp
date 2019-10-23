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

#include "controller.tpp"
#include "controllers/mandelfract.hpp"
#include "controllers_manager.hpp"
#include "event/quit_event.hpp"
#include "event/window_event.hpp"
#include "model.tpp"
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

MandelfractModel::~MandelfractModel() { event_handler_.lock()->UnregisterEventCallbacks(registered_callbacks_); }

void MandelfractModel::Create() {
    const auto& ubuntu12_font = resources_manager_.lock()->LoadFont("Ubuntu12", "resources/fonts/ubuntu.ttf", 12);
    const auto& app_icon = resources_manager_.lock()->LoadImage("AppIcon", "resources/images/icon.png");

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

    scale_coefficient_ = 0.0040;
    offset_ = std::make_pair(-2.1, -1.2);
}

void MandelfractModel::Update(float delta) { fps_counter_->SetText(std::to_string((uint64_t)(1.0 / delta)) + "FPS"); }

void MandelfractModel::SetScaleCoeficient(double value) { scale_coefficient_ = value; }

void MandelfractModel::IncScaleCoeficient(double value) { scale_coefficient_ += value; }

void MandelfractModel::SetOffset(double offset_x, double offset_y) {
    offset_.first = offset_x;
    offset_.second = offset_y;
}

void MandelfractModel::Shift(double offset_x, double offset_y) {
    offset_.first += offset_x;
    offset_.second += offset_y;
}

std::weak_ptr<zzgui::Window> MandelfractModel::GetWindow() const { return window_; }

std::weak_ptr<zzgui::WidgetsManager> MandelfractModel::GetWidgetsManager() const { return widgets_manager_; }

double MandelfractModel::GetScaleCoeficient() const { return scale_coefficient_; }

std::pair<double, double> MandelfractModel::GetOffset() const { return offset_; }

}  // namespace cozz
