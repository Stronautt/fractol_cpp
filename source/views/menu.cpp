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

#include "views/menu.hpp"

#include "controllers/menu.hpp"
#include "models/menu.hpp"
#include "painter.hpp"
#include "resources/font_resource.hpp"
#include "resources_manager.hpp"
#include "widget.hpp"
#include "widgets/label.hpp"
#include "widgets_manager.hpp"
#include "window.hpp"

namespace cozz {

MenuView::MenuView(std::weak_ptr<MenuModel> model) : View(model) {}

void MenuView::Create() {
    auto model = GetModel().lock();
    painter_ = std::make_shared<zzgui::Painter>();
}

void MenuView::Render(float /*delta*/) {
    auto model = GetModel().lock();
    auto window = model->GetWindow().lock();
    auto canvas = window->GetCanvas().lock();

    painter_->Clear(canvas, {0xFF, 0xFF, 0xFF});
    const auto widgets_manager = model->GetWidgetsManager().lock();
    if (widgets_manager) {
        for (const auto& widget : widgets_manager->GetWidgets()) {
            widget.second->Draw(painter_, canvas);
        }
    }
}

void MenuView::Resized(std::weak_ptr<zzgui::Window> /*window*/) {}

void MenuView::Show() {}

void MenuView::Pause() {}

void MenuView::Resume() {}

void MenuView::Hide() {}

}  // namespace cozz
