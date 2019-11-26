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

#include "models/pythagoras_tree_fractal.hpp"

#include "controllers/pythagoras_tree_fractal.hpp"
#include "resources_manager.hpp"
#include "sdl_window.hpp"
#include "widgets/label.hpp"
#include "widgets_manager.hpp"
#include "windows_manager.hpp"

namespace cozz {

PythagorasTreeFractalModel::PythagorasTreeFractalModel() : side_length_(kMaxSideLength), depth_(kMaxDepth) {}

void PythagorasTreeFractalModel::Create() {
    const auto& app_icon = resources_manager_.lock()->LoadImage("AppIcon", "resources/images/icon.png");
    const auto& ubuntu10_font = resources_manager_.lock()->LoadFont("Ubuntu10", "resources/fonts/ubuntu.ttf", 10);

    window_ = windows_manager_.lock()->CreateWindow<zzgui::SDLWindow>("Pythagoras Tree Fractal", 800, 600);
    const auto& window_id = window_.lock()->GetId();
    window_.lock()->IfClosed(std::bind(&PythagorasTreeFractalController::OnWindowClose, GetController().lock().get(),
                                       std::placeholders::_1));

    window_.lock()->SetIcon(app_icon);

    GetController().lock()->RegisterWindow(window_);

    widgets_manager_ = std::make_shared<zzgui::WidgetsManager>(event_handler_);

    fps_counter_ = widgets_manager_->Create<zzgui::Label>(window_id, 0, "", ubuntu10_font, 0, 0);
    fps_counter_.lock()->SetForegroundColor({0xFF, 0xFF, 0xFF});
    fps_counter_.lock()->SetPosition(0, window_.lock()->GetHeight() - fps_counter_.lock()->GetSize().second);

    window_.lock()->IfResized([this](auto&) {
        fps_counter_.lock()->SetPosition(0, window_.lock()->GetHeight() - fps_counter_.lock()->GetSize().second);
    });
}

void PythagorasTreeFractalModel::Update(float delta) {
    fps_counter_.lock()->SetText(std::to_string((uint64_t)(1.0 / delta)) + "FPS");
}

void PythagorasTreeFractalModel::Grow(int32_t value) {
    side_length_ = std::clamp(side_length_ + value, kMinSideLength, kMaxSideLength);
}

void PythagorasTreeFractalModel::IncSideLength(int32_t value) {
    depth_ = std::clamp(depth_ + value, kMinDepth, kMaxDepth);
}

std::weak_ptr<zzgui::Window> PythagorasTreeFractalModel::GetWindow() const { return window_; }

std::weak_ptr<zzgui::WidgetsManager> PythagorasTreeFractalModel::GetWidgetsManager() const { return widgets_manager_; }

uint32_t PythagorasTreeFractalModel::GetSideLength() const { return side_length_; }

uint32_t PythagorasTreeFractalModel::GetDepth() const { return depth_; }

}  // namespace cozz
