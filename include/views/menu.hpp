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

#ifndef FRACTOL_INCLUDE_VIEWS_MENU_HPP_
#define FRACTOL_INCLUDE_VIEWS_MENU_HPP_

#include "view.hpp"

#include <memory>

namespace cozz {

class MenuModel;
class MenuController;

namespace zzgui {

class Painter;

}  // namespace zzgui

class MenuView final : public zzgui::View<MenuModel, MenuController> {
  public:
    MenuView(std::weak_ptr<MenuModel> model);
    ~MenuView();

    virtual void Create() override;

    virtual void Render(float delta) override;

    virtual void Resize(uint64_t width, uint64_t height) override;

    virtual void Show() override;

    virtual void Pause() override;

    virtual void Resume() override;

    virtual void Hide() override;

  private:
    std::shared_ptr<zzgui::Painter> painter_;
};

}  // namespace cozz

#endif  // FRACTOL_INCLUDE_VIEWS_MENU_HPP_
