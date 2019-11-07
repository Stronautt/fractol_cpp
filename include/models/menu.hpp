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

#ifndef FRACTOL_INCLUDE_MODELS_MENU_HPP_
#define FRACTOL_INCLUDE_MODELS_MENU_HPP_

#include "model.hpp"

#include <memory>
#include <vector>

namespace cozz {

class MenuController;

namespace zzgui {

class Window;
class WidgetsManager;
class Label;

}  // namespace zzgui

namespace clpp {

class Core;

}  // namespace clpp

class MenuModel final : public zzgui::Model<MenuController> {
  public:
    MenuModel(std::shared_ptr<clpp::Core> cl_core);

    virtual void Create() override;

    virtual void Update(float delta) override;

    std::weak_ptr<zzgui::Window> GetWindow() const;

    std::weak_ptr<zzgui::WidgetsManager> GetWidgetsManager() const;

    void CreateMenuWidgets();

    void CreateSettingsWidgets();

  private:
    std::shared_ptr<clpp::Core> cl_core_;

    std::weak_ptr<zzgui::Window> window_;

    std::shared_ptr<zzgui::WidgetsManager> widgets_manager_;

    std::weak_ptr<zzgui::Label> fps_counter_;
};

}  // namespace cozz

#endif  // FRACTOL_INCLUDE_MODELS_MENU_HPP_
