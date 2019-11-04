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

#include "controllers/menu.hpp"

#include "application.hpp"
#include "controllers/algebraic_fractal.hpp"
#include "controllers_manager.hpp"
#include "models/juliafract.hpp"
#include "models/mandelfract.hpp"
#include "views/algebraic_fractal.hpp"

namespace cozz {

MenuController::MenuController(const zzgui::Application& app, std::shared_ptr<clpp::Core> cl_core)
    : Controller(std::make_shared<MenuView>(std::make_shared<MenuModel>())), app_(app), cl_core_(cl_core) {}

void MenuController::Create() {}

void MenuController::OnWindowClose(const zzgui::WindowCloseEvent&) {
    controllers_manager_.lock()->Erase(shared_from_this());
}

void MenuController::OnMandelbrotFractalButtonClick(const zzgui::MouseButtonEvent&) const {
    try {
        controllers_manager_.lock()->Push(
            std::make_shared<AlgebraicFractalController>(app_, cl_core_, std::make_shared<MandelfractModel>(cl_core_)));
    } catch (const std::exception& e) {
        app_.ShowErrorMessage(e.what());
    }
}

void MenuController::OnJuliaFractalButtonClick(const zzgui::MouseButtonEvent&) const {
    try {
        controllers_manager_.lock()->Push(
            std::make_shared<AlgebraicFractalController>(app_, cl_core_, std::make_shared<JuliafractModel>(cl_core_)));
    } catch (const std::exception& e) {
        app_.ShowErrorMessage(e.what());
    }
}

void MenuController::OnExitButtonClick(const zzgui::MouseButtonEvent&) const {
    event_handler_.lock()->PushEvent(zzgui::QuitEvent());
}

}  // namespace cozz
