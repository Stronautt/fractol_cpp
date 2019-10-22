/*
 * This file is part of LibZZgui.

 * LibZZgui is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * LibZZgui is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with LibZZgui. If not, see <https://www.gnu.org/licenses/>.
 *
 * Author: Pavlo Hrytsenko
*/

#ifndef FRACTOL_INCLUDE_MODELS_MENU_HPP_
#define FRACTOL_INCLUDE_MODELS_MENU_HPP_

#include "model.hpp"

#include <memory>
#include <vector>

namespace cozz {

class MenuController;

namespace zzgui {

class Window;
class Widget;
class WidgetsManager;
class Label;

}  // namespace zzgui

class MenuModel final : public zzgui::Model<MenuController> {
  public:
    MenuModel();
    ~MenuModel();

    virtual void Create() override;

    virtual void Update(float delta) override;

    std::weak_ptr<zzgui::Window> GetWindow() const;

    std::weak_ptr<zzgui::WidgetsManager> GetWidgetsManager() const;

  private:
    std::weak_ptr<zzgui::Window> window_;

    std::shared_ptr<zzgui::WidgetsManager> widgets_manager_;

    std::shared_ptr<zzgui::Label> fps_counter_;
};

}  // namespace cozz

#endif  // FRACTOL_INCLUDE_MODELS_MENU_HPP_
