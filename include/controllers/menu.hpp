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

#ifndef FRACTOL_INCLUDE_CONTROLLERS_MENU_HPP_
#define FRACTOL_INCLUDE_CONTROLLERS_MENU_HPP_

#include "controller.hpp"

#include <memory>

#include "event/window_event.hpp"
#include "models/menu.hpp"
#include "views/menu.hpp"

namespace cozz {

namespace zzgui {

class Application;
class MouseButtonEvent;

}  // namespace zzgui

namespace clpp {

class Core;
class Platform;

}  // namespace clpp

class MenuController final : public zzgui::Controller<MenuModel, MenuView>,
                             public std::enable_shared_from_this<MenuController> {
  public:
    MenuController(const zzgui::Application& app, std::shared_ptr<clpp::Core> cl_core);

    virtual void Create() override;

    bool OnWindowClose(const zzgui::WindowCloseEvent& event);

    bool OnMandelbrotFractalButtonClick(const zzgui::MouseButtonEvent& event) const;

    bool OnJuliaFractalButtonClick(const zzgui::MouseButtonEvent& event) const;

    bool OnBurningShipFractalButtonClick(const zzgui::MouseButtonEvent& event) const;

    bool OnExitButtonClick(const zzgui::MouseButtonEvent& event) const;

    bool OnMenuButtonClick(const zzgui::MouseButtonEvent& event) const;

    bool OnSettingsButtonClick(const zzgui::MouseButtonEvent& event) const;

    void OnPlatformSelectChange(std::shared_ptr<clpp::Platform> platform) const;

    void OnDeviceSelectChange(std::shared_ptr<clpp::Device> device) const;

  private:
    const zzgui::Application& app_;

    std::shared_ptr<clpp::Core> cl_core_;
};

}  // namespace cozz

#endif  // FRACTOL_INCLUDE_CONTROLLERS_MENU_HPP_
