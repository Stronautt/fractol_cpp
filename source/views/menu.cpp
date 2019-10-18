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

#include "models/menu.hpp"
#include "controllers/menu.hpp"
#include "views/menu.hpp"

#include <iostream>

#include "model.hpp"
#include "painter.hpp"
#include "view.tpp"
#include "widget.hpp"
#include "window.hpp"

namespace cozz {

MenuView::MenuView(std::weak_ptr<MenuModel> model) : View(model) {}

MenuView::~MenuView() = default;

void MenuView::Create() {
    auto window = GetModel().lock()->GetWindow().lock();
    painter_ = std::make_shared<zzgui::Painter>(window->GetCanvas());
}

void MenuView::Render(float /*delta*/) {
    auto model = GetModel().lock();

    for (const auto& widget : model->GetWidgets()) {
        widget->Draw(painter_);
    }
}

void MenuView::Resize(uint64_t /*width*/, uint64_t /*height*/) {}

void MenuView::Show() {}

void MenuView::Pause() {}

void MenuView::Resume() {}

void MenuView::Hide() {}

}  // namespace cozz
