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
#include "widgets_manager.hpp"
#include "windows_manager.hpp"

using std::placeholders::_1;

namespace cozz {

void MenuModel::Create() {
    const auto& ubuntu12_font = resources_manager_.lock()->LoadFont("Ubuntu12", "resources/fonts/ubuntu.ttf", 12);
    const auto& ubuntu14_font = resources_manager_.lock()->LoadFont("Ubuntu14", "resources/fonts/ubuntu.ttf", 14);
    const auto& logo_image = resources_manager_.lock()->LoadImage("FractolLogo", "resources/images/logo.jpg");
    const auto& app_icon = resources_manager_.lock()->LoadImage("AppIcon", "resources/images/icon.png");

    window_ = windows_manager_.lock()->CreateWindow<zzgui::SDLWindow>("Main Menu", logo_image->GetSize().first, 600);
    auto window_id = window_.lock()->GetId();
    window_.lock()->IfClosed(std::bind(&MenuController::OnWindowClose, GetController().lock().get(), _1));

    window_.lock()->SetIcon(app_icon);

    GetController().lock()->RegisterWindow(window_);

    widgets_manager_ = std::make_shared<zzgui::WidgetsManager>(event_handler_);

    widgets_manager_->Create<zzgui::Image>(window_id, logo_image, 0, 0);
    fps_counter_ = widgets_manager_->Create<zzgui::Label>(window_id, "", ubuntu12_font, 0, 0);
    fps_counter_->SetPosition(0, window_.lock()->GetHeight() - fps_counter_->GetSize().second);

    auto mandelbrot_fractal_button =
        widgets_manager_->Create<zzgui::Button>(window_id, "Mandelbrot Fractal", ubuntu14_font, 0, 0);
    mandelbrot_fractal_button->SetAutosize(false);
    mandelbrot_fractal_button->SetSize(150, 30);
    mandelbrot_fractal_button->OnClick(
        std::bind(&MenuController::OnMandelbrotFractalButtonClick, GetController().lock().get(), _1));
    mandelbrot_fractal_button->SetPosition(
        window_.lock()->GetWidth() / 2 - mandelbrot_fractal_button->GetSize().first - 10,
        logo_image->GetSize().second + 30);

    auto exit_button = widgets_manager_->Create<zzgui::Button>(window_id, "Exit", ubuntu14_font, 0, 0);
    exit_button->SetAutosize(false);
    exit_button->SetSize(100, 30);
    exit_button->OnClick(std::bind(&MenuController::OnExitButtonClick, GetController().lock().get(), _1));
    exit_button->SetPosition(window_.lock()->GetWidth() / 2 - exit_button->GetSize().first / 2,
                             window_.lock()->GetHeight() - exit_button->GetSize().second - 20);
}

void MenuModel::Update(float delta) { fps_counter_->SetText(std::to_string((uint64_t)(1.0 / delta)) + "FPS"); }

std::weak_ptr<zzgui::Window> MenuModel::GetWindow() const { return window_; }

std::weak_ptr<zzgui::WidgetsManager> MenuModel::GetWidgetsManager() const { return widgets_manager_; }

}  // namespace cozz
