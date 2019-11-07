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

#include "clpp/core.hpp"
#include "clpp/platform.hpp"
#include "controllers/menu.hpp"
#include "controllers_manager.hpp"
#include "event/quit_event.hpp"
#include "event/window_event.hpp"
#include "resources_manager.hpp"
#include "sdl_window.hpp"
#include "widget.hpp"
#include "widgets/button.hpp"
#include "widgets/image.hpp"
#include "widgets/label.hpp"
#include "widgets/select.hpp"
#include "widgets_manager.hpp"
#include "windows_manager.hpp"

using std::placeholders::_1;

namespace cozz {

MenuModel::MenuModel(std::shared_ptr<clpp::Core> cl_core) : cl_core_(cl_core) {}

void MenuModel::Create() {
    const auto& ubuntu12_font = resources_manager_.lock()->LoadFont("Ubuntu12", "resources/fonts/ubuntu.ttf", 12);
    const auto& ubuntu14_font = resources_manager_.lock()->LoadFont("Ubuntu14", "resources/fonts/ubuntu.ttf", 14);
    const auto& logo_image = resources_manager_.lock()->LoadImage("FractolLogo", "resources/images/logo.jpg");
    const auto& app_icon = resources_manager_.lock()->LoadImage("AppIcon", "resources/images/icon.png");

    window_ = windows_manager_.lock()->CreateWindow<zzgui::SDLWindow>("Main Menu", logo_image->GetSize().first, 600);
    window_.lock()->IfClosed(std::bind(&MenuController::OnWindowClose, GetController().lock().get(), _1));

    window_.lock()->SetIcon(app_icon);

    GetController().lock()->RegisterWindow(window_);
    CreateMenuWidgets();
}

void MenuModel::CreateMenuWidgets() {
    const auto resources_manager = resources_manager_.lock();
    const auto& ubuntu12_font = resources_manager->Get<zzgui::FontResource>("Ubuntu12");
    const auto& ubuntu14_font = resources_manager->Get<zzgui::FontResource>("Ubuntu14");
    const auto& logo_image = resources_manager->Get<zzgui::ImageResource>("FractolLogo");
    const auto& window_id = window_.lock()->GetId();

    widgets_manager_ = std::make_shared<zzgui::WidgetsManager>(event_handler_);

    widgets_manager_->Create<zzgui::Image>(window_id, logo_image, 0, 0);
    fps_counter_ = widgets_manager_->Create<zzgui::Label>(window_id, "", ubuntu12_font, 0, 0);
    fps_counter_.lock()->SetPosition(0, window_.lock()->GetHeight() - fps_counter_.lock()->GetSize().second);

    auto mandelbrot_fractal_button =
        widgets_manager_->Create<zzgui::Button>(window_id, "Mandelbrot Fractal", ubuntu14_font, 0, 0);
    mandelbrot_fractal_button.lock()->SetAutosize(false);
    mandelbrot_fractal_button.lock()->SetSize(200, 30);
    mandelbrot_fractal_button.lock()->OnClick(
        std::bind(&MenuController::OnMandelbrotFractalButtonClick, GetController().lock().get(), _1));
    mandelbrot_fractal_button.lock()->SetPosition(
        window_.lock()->GetWidth() / 2 - mandelbrot_fractal_button.lock()->GetSize().first - 5,
        logo_image->GetSize().second + 30);

    auto julia_fractal_button =
        widgets_manager_->Create<zzgui::Button>(window_id, "Julia Fractal", ubuntu14_font, 0, 0);
    julia_fractal_button.lock()->SetAutosize(false);
    julia_fractal_button.lock()->SetSize(200, 30);
    julia_fractal_button.lock()->OnClick(
        std::bind(&MenuController::OnJuliaFractalButtonClick, GetController().lock().get(), _1));
    julia_fractal_button.lock()->SetPosition(window_.lock()->GetWidth() / 2 + 5, logo_image->GetSize().second + 30);

    auto exit_button = widgets_manager_->Create<zzgui::Button>(window_id, "Exit", ubuntu14_font, 0, 0);
    exit_button.lock()->SetAutosize(false);
    exit_button.lock()->SetSize(100, 30);
    exit_button.lock()->OnClick(std::bind(&MenuController::OnExitButtonClick, GetController().lock().get(), _1));
    exit_button.lock()->SetPosition(window_.lock()->GetWidth() / 2 - exit_button.lock()->GetSize().first / 2,
                                    window_.lock()->GetHeight() - exit_button.lock()->GetSize().second - 20);

    auto settings_button = widgets_manager_->Create<zzgui::Button>(window_id, "Settings", ubuntu14_font, 0, 0);
    settings_button.lock()->SetAutosize(false);
    settings_button.lock()->SetSize(100, 30);
    settings_button.lock()->OnClick(
        std::bind(&MenuController::OnSettingsButtonClick, GetController().lock().get(), _1));
    settings_button.lock()->SetPosition(
        window_.lock()->GetWidth() / 2 - settings_button.lock()->GetSize().first / 2,
        exit_button.lock()->GetPosition().second - settings_button.lock()->GetSize().second - 5);
}

void MenuModel::CreateSettingsWidgets() {
    const auto resources_manager = resources_manager_.lock();
    const auto& ubuntu12_font = resources_manager->Get<zzgui::FontResource>("Ubuntu12");
    const auto& ubuntu14_font = resources_manager->Get<zzgui::FontResource>("Ubuntu14");
    const auto& logo_image = resources_manager->Get<zzgui::ImageResource>("FractolLogo");
    const auto& window_id = window_.lock()->GetId();

    widgets_manager_ = std::make_shared<zzgui::WidgetsManager>(event_handler_);

    widgets_manager_->Create<zzgui::Image>(window_id, logo_image, 0, 0);

    auto back_button = widgets_manager_->Create<zzgui::Button>(window_id, "Back", ubuntu14_font, 0, 0);
    back_button.lock()->SetAutosize(false);
    back_button.lock()->SetSize(100, 30);
    back_button.lock()->OnClick(std::bind(&MenuController::OnMenuButtonClick, GetController().lock().get(), _1));
    back_button.lock()->SetPosition(window_.lock()->GetWidth() / 2 - back_button.lock()->GetSize().first / 2,
                                    window_.lock()->GetHeight() - back_button.lock()->GetSize().second - 20);

    std::vector<std::pair<std::string, std::shared_ptr<clpp::Platform>>> platform_select_list;
    for (const auto& platform : cl_core_->GetPlatforms()) {
        const auto& platform_name = platform.first;
        const auto& platform_ptr = platform.second;

        platform_select_list.push_back(std::make_pair(platform_name, platform_ptr));
    }

    auto platform_select_label = widgets_manager_->Create<zzgui::Label>(window_id, "Platform:", ubuntu14_font, 40,
                                                                        logo_image->GetSize().second + 30);
    platform_select_label.lock()->SetBackgroundColor({0xFF, 0xFF, 0xFF});
    platform_select_label.lock()->SetBorderColor({0xFF, 0xFF, 0xFF});
    platform_select_label.lock()->SetForegroundColor({0, 0, 0});
    platform_select_label.lock()->SetTextAlign(zzgui::Label::TextAlign::kLeftBottom);

    auto platform_select = widgets_manager_->Create<zzgui::Select<std::shared_ptr<clpp::Platform>>>(
        window_id, platform_select_list, ubuntu12_font,
        platform_select_label.lock()->GetPosition().first + platform_select_label.lock()->GetSize().first + 10,
        logo_image->GetSize().second + 30);
    platform_select.lock()->OnChange(
        std::bind(&MenuController::OnPlatformSelectChange, GetController().lock().get(), _1));
    platform_select.lock()->SetPadding(7);
}

void MenuModel::Update(float delta) {
    if (!fps_counter_.expired()) {
        fps_counter_.lock()->SetText(std::to_string((uint64_t)(1.0 / delta)) + "FPS");
    }
}

std::weak_ptr<zzgui::Window> MenuModel::GetWindow() const { return window_; }

std::weak_ptr<zzgui::WidgetsManager> MenuModel::GetWidgetsManager() const { return widgets_manager_; }

}  // namespace cozz
