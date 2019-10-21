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

#include "controller.tpp"
#include "controllers/menu.hpp"
#include "model.tpp"
#include "resource_manager.hpp"
#include "sdl_window.hpp"
#include "widget.hpp"
#include "widgets/button.hpp"
#include "widgets_manager.hpp"
#include "windows_manager.hpp"

namespace cozz {

MenuModel::MenuModel() {}

MenuModel::~MenuModel() = default;

void MenuModel::Create() {
    auto ubuntu24_font = resource_manager_.lock()->LoadFont("Ubuntu12", "resources/fonts/ubuntu.ttf", 12);

    window_ = windows_manager_.lock()->CreateWindow<zzgui::SDLWindow>("Main Menu", 800, 600);

    GetController().lock()->RegisterWindow(window_);

    widgets_manager_ = std::make_shared<zzgui::WidgetsManager>(event_handler_);

    widgets_manager_->Create<zzgui::Button>("Hello World!", ubuntu24_font, 100, 100)
        ->OnClick([this, ubuntu24_font](auto) {
            static uint64_t x = 100, y = 100;
            widgets_manager_->Create<zzgui::Button>("Привет Мир!", ubuntu24_font, x += 30, y += 30);
        });
}

void MenuModel::Update(float /*delta*/) {}

std::weak_ptr<zzgui::Window> MenuModel::GetWindow() const { return window_; }

std::weak_ptr<zzgui::WidgetsManager> MenuModel::GetWidgetsManager() const { return widgets_manager_; }

}  // namespace cozz
