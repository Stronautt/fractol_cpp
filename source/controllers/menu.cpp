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
#include "models/burningshipfract.hpp"
#include "models/juliafract.hpp"
#include "models/mandelfract.hpp"
#include "views/algebraic_fractal.hpp"

namespace cozz {

MenuController::MenuController(const zzgui::Application& app, std::shared_ptr<clpp::Core> cl_core)
    : Controller(std::make_shared<MenuView>(std::make_shared<MenuModel>(cl_core))), app_(app), cl_core_(cl_core) {}

void MenuController::Create() {}

bool MenuController::OnWindowClose(const zzgui::WindowCloseEvent&) {
    controllers_manager_.lock()->Erase(shared_from_this());
    return false;
}

bool MenuController::OnMandelbrotFractalButtonClick(const zzgui::MouseButtonEvent&) const {
    try {
        controllers_manager_.lock()->Push(std::make_shared<AlgebraicFractalController>(
            app_, cl_core_,
            std::make_shared<MandelfractModel>(cl_core_, model_->GetClPlatform(), model_->GetClDevice())));
    } catch (const std::exception& e) {
        app_.ShowErrorMessage(e.what());
    }
    return true;
}

bool MenuController::OnJuliaFractalButtonClick(const zzgui::MouseButtonEvent&) const {
    try {
        controllers_manager_.lock()->Push(std::make_shared<AlgebraicFractalController>(
            app_, cl_core_,
            std::make_shared<JuliafractModel>(cl_core_, model_->GetClPlatform(), model_->GetClDevice())));
    } catch (const std::exception& e) {
        app_.ShowErrorMessage(e.what());
    }
    return true;
}

bool MenuController::OnBurningShipFractalButtonClick(const zzgui::MouseButtonEvent&) const {
    try {
        controllers_manager_.lock()->Push(std::make_shared<AlgebraicFractalController>(
            app_, cl_core_,
            std::make_shared<BurningshipfractModel>(cl_core_, model_->GetClPlatform(), model_->GetClDevice())));
    } catch (const std::exception& e) {
        app_.ShowErrorMessage(e.what());
    }
    return true;
}

bool MenuController::OnExitButtonClick(const zzgui::MouseButtonEvent&) const {
    event_handler_.lock()->PushEvent(zzgui::QuitEvent());
    return true;
}

bool MenuController::OnMenuButtonClick(const zzgui::MouseButtonEvent&) const {
    model_->CreateMenuWidgets();
    return true;
}

bool MenuController::OnSettingsButtonClick(const zzgui::MouseButtonEvent&) const {
    model_->CreateSettingsWidgets();
    return true;
}

void MenuController::OnPlatformSelectChange(std::shared_ptr<clpp::Platform> platform) const {
    model_->SetClPlatform(platform);
}

void MenuController::OnDeviceSelectChange(std::shared_ptr<clpp::Device> device) const { model_->SetClDevice(device); }

}  // namespace cozz
