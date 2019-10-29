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

#include "controllers/mandelfract.hpp"

#include "controllers/menu.hpp"
#include "controllers_manager.hpp"
#include "event/keyboard_event.hpp"
#include "event/mouse_wheel_event.hpp"

namespace cozz {

MandelfractController::MandelfractController(std::shared_ptr<clpp::Core> cl_core)
    : Controller(std::make_shared<MandelfractView>(std::make_shared<MandelfractModel>(cl_core))), cl_core_(cl_core) {}

void MandelfractController::Create() {}

void MandelfractController::OnWindowClose(const zzgui::WindowCloseEvent&) {
    controllers_manager_.lock()->Erase(shared_from_this());
}

void MandelfractController::OnKeyboard(const zzgui::KeyboardEvent& event) {
    if (!event.IsPressed()) {
        return;
    }

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
            model_->ToogleChangeColor();
            break;
        case zzgui::KeyMap::kPageUp:
            model_->IncColorChangeSpeed(-0.01);
            break;
        case zzgui::KeyMap::kPageDown:
            model_->IncColorChangeSpeed(0.01);
            break;
        default:
            break;
    }
}

void MandelfractController::OnMouseWheel(const zzgui::MouseWheelEvent& event) {
    const auto& mouse_pos = event.GetPosition();

    model_->Zoom(mouse_pos.first, mouse_pos.second, event.GetScrolledByY() > 0);
}

}  // namespace cozz
