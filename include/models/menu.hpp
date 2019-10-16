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

namespace cozz {

namespace zzgui {
class Window;
}

class MenuModel final : public zzgui::Model {
  public:
    MenuModel();
    ~MenuModel();

    virtual void Create() override;

    virtual void Update(float delta) override;

  private:
    std::weak_ptr<zzgui::Window> window_;
};

}  // namespace cozz

#endif  // FRACTOL_INCLUDE_MODELS_MENU_HPP_
