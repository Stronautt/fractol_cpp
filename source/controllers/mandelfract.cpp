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

#include "controller.tpp"
#include "controllers/menu.hpp"
#include "controllers_manager.hpp"
#include "event/keyboard_event.hpp"
#include "event/mouse_wheel_event.hpp"
#include "model.tpp"
#include "models/mandelfract.hpp"
#include "models/menu.hpp"
#include "view.tpp"
#include "views/mandelfract.hpp"
#include "views/menu.hpp"

namespace cozz {

MandelfractController::MandelfractController()
    : Controller(std::make_shared<MandelfractView>(std::make_shared<MandelfractModel>())) {}

void MandelfractController::Create() {}

void MandelfractController::OnWindowClose(const zzgui::WindowCloseEvent&) {
    controllers_manager_.lock()->Erase(shared_from_this());
}

void MandelfractController::OnKeyboard(const zzgui::KeyboardEvent& event) {
    switch (event.GetKey()) {
        case zzgui::KeyMap::kUp:
            model_->Shift(0, -0.00002 / model_->GetScaleCoeficient());
            break;
        case zzgui::KeyMap::kDown:
            model_->Shift(0, 0.00002 / model_->GetScaleCoeficient());
            break;
        case zzgui::KeyMap::kLeft:
            model_->Shift(-0.00002 / model_->GetScaleCoeficient(), 0);
            break;
        case zzgui::KeyMap::kRight:
            model_->Shift(0.00002 / model_->GetScaleCoeficient(), 0);
            break;
        case zzgui::KeyMap::kKeyPadPlus:
            model_->IncScaleCoeficient(-model_->GetScaleCoeficient() / 32.0);
            break;
        case zzgui::KeyMap::kMinus:
        case zzgui::KeyMap::kKeyPadMinus:
            model_->IncScaleCoeficient(model_->GetScaleCoeficient() / 32.0);
            break;
        default:
            break;
    }
}

namespace {
inline constexpr float lerp(float v0, float v1, float t) { return (1 - t) * v0 + t * v1; }
}  // namespace

void MandelfractController::OnMouseWheel(const zzgui::MouseWheelEvent& event) {
    const auto& offset = model_->GetOffset();
    const auto& mouse_pos = event.GetPosition();
    const auto& window = model_->GetWindow().lock();

    if (event.GetScrolledByY() > 0) {
        model_->SetOffset(
            lerp(offset.first,
                 offset.first + (mouse_pos.first - window->GetWidth() / 4.0) * model_->GetScaleCoeficient(), 0.07),
            lerp(offset.second,
                 offset.second + (mouse_pos.second - window->GetHeight() / 4.0) * model_->GetScaleCoeficient(), 0.07));
    }
    if (event.GetScrolledByY() > 0) {
        model_->IncScaleCoeficient(-model_->GetScaleCoeficient() / 32.0);
    } else {
        model_->IncScaleCoeficient(model_->GetScaleCoeficient() / 32.0);
    }
}

}  // namespace cozz
