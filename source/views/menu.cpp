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
#include "model.hpp"
#include "models/menu.hpp"
#include "painter.hpp"
#include "resources/font_resource.hpp"
#include "resources_manager.hpp"
#include "view.tpp"
#include "widget.hpp"
#include "widgets_manager.hpp"
#include "window.hpp"

namespace cozz {

MenuView::MenuView(std::weak_ptr<MenuModel> model) : View(model) {}

MenuView::~MenuView() = default;

void MenuView::Create() {
    auto model = GetModel().lock();

    if (model) {
        Resized(model->GetWindow());
    }
}

void MenuView::Render(float delta) {
    auto model = GetModel().lock();
    auto window = model->GetWindow().lock();
    auto canvas = window->GetCanvas().lock();

    canvas->Clear({0xFF, 0xFF, 0xFF});
    for (const auto& widget : model->GetWidgetsManager().lock()->GetWidgets()) {
        widget->Draw(painter_);
    }
    painter_->DrawText({0, 0}, std::to_string((uint64_t)(1.0 / delta)) + "FPS",
                       resources_manager_.lock()->Get<zzgui::FontResource>("Ubuntu12"), {0, 0, 0});
}

void MenuView::Resized(std::weak_ptr<zzgui::Window> window) {
    const auto window_ptr = window.lock();

    if (window_ptr) {
        painter_ = std::make_shared<zzgui::Painter>(window_ptr->GetCanvas());
    }
}

void MenuView::Show() {}

void MenuView::Pause() {}

void MenuView::Resume() {}

void MenuView::Hide() {}

}  // namespace cozz
