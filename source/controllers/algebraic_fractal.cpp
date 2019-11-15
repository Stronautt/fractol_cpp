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

#include "controllers/algebraic_fractal.hpp"

#include "application.hpp"
#include "controllers/menu.hpp"
#include "controllers_manager.hpp"
#include "event/keyboard_event.hpp"
#include "event/mouse_button_event.hpp"
#include "event/mouse_motion_event.hpp"
#include "event/mouse_wheel_event.hpp"
#include "event/window_event.hpp"
#include "windows_manager.hpp"

namespace cozz {

AlgebraicFractalController::AlgebraicFractalController(const zzgui::Application& app,
                                                       std::shared_ptr<clpp::Core> cl_core,
                                                       std::shared_ptr<AlgebraicFractalModel> model)
    : Controller(std::make_shared<AlgebraicFractalView>(model)), app_(app), cl_core_(cl_core), drag_(false) {}

void AlgebraicFractalController::Create() {}

void AlgebraicFractalController::Render(float delta) {
    try {
        Controller::Render(delta);
    } catch (const std::exception& e) {
        app_.ShowErrorMessage(e.what());
        model_->GetWindow().lock()->Close(event_handler_.lock());
    }
}

void AlgebraicFractalController::OnWindowClose(const zzgui::WindowCloseEvent&) {
    controllers_manager_.lock()->Erase(shared_from_this());
}

void AlgebraicFractalController::OnKeyboard(const zzgui::KeyboardEvent& event) {
    if (!event.IsPressed()) {
        return;
    }

    auto window = model_->GetWindow().lock();
    switch (event.GetKey()) {
        case zzgui::KeyMap::kUp:
            model_->Move(0, -1);
            break;
        case zzgui::KeyMap::kDown:
            model_->Move(0, 1);
            break;
        case zzgui::KeyMap::kLeft:
            model_->Move(-1, 0);
            break;
        case zzgui::KeyMap::kRight:
            model_->Move(1, 0);
            break;
        case zzgui::KeyMap::kKeyPadPlus:
            model_->Zoom(true);
            break;
        case zzgui::KeyMap::kMinus:
        case zzgui::KeyMap::kKeyPadMinus:
            model_->Zoom(false);
            break;
        case zzgui::KeyMap::kR:
            model_->RandomizeColor();
            break;
        case zzgui::KeyMap::kP:
            model_->ToogleMouseFollowing();
            break;
        case zzgui::KeyMap::kPageUp:
            model_->IncDepth(1);
            break;
        case zzgui::KeyMap::kPageDown:
            model_->IncDepth(-1);
            break;
        case zzgui::KeyMap::kTab:
            window->SetFullscreenDesktop(window->GetFullscreenDesktop() ^ true);
            break;
        default:
            break;
    }
}

void AlgebraicFractalController::OnMouseButton(const zzgui::MouseButtonEvent& event) {
    if (event.GetButton() == zzgui::KeyMap::kLeftMouseButton) {
        drag_ = event.IsPressed();
    }
}

void AlgebraicFractalController::OnMouseMotion(const zzgui::MouseMotionEvent& event) {
    const auto& mouse_pos = event.GetPosition();

    model_->FollowMouse(mouse_pos.first, mouse_pos.second);
    if (drag_) {
        const auto& direction = event.GetDirection();
        model_->Drag(-direction.first, -direction.second);
    }
}

void AlgebraicFractalController::OnMouseWheel(const zzgui::MouseWheelEvent& event) {
    const auto& mouse_pos = event.GetPosition();

    model_->Zoom(mouse_pos.first, mouse_pos.second, event.GetScrolledByY() > 0);
}

}  // namespace cozz
