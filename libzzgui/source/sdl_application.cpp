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

#include "sdl_application.hpp"

#include <memory>

#include "controllers_manager.hpp"
#include "event_handler.hpp"
#include "resource_manager.hpp"
#include "sdl_event_handler.hpp"
#include "windows_manager.hpp"

namespace cozz {

namespace zzgui {

SdlApplication::SdlApplication()
    : is_running_(true),
      event_handler_(std::make_shared<zzgui::SDLEventHandler>()),
      windows_manager_(std::make_shared<zzgui::WindowsManager>(event_handler_)),
      resource_manager_(std::make_shared<zzgui::ResourceManager>()),
      controller_manager_(std::make_unique<ControllersManager>(event_handler_, windows_manager_, resource_manager_)) {
    event_handler_->RegisterEventCallback<QuitEvent>(
        std::bind(&SdlApplication::Terminate, this, std::placeholders::_1));
}

SdlApplication::~SdlApplication() = default;

void SdlApplication::Terminate(const QuitEvent&) { is_running_ = false; }

uint8_t SdlApplication::Run() {
    while (is_running_) {
        event_handler_->Poll();
        controller_manager_->Render();
        windows_manager_->UpdateWindows();
        UpdateDeltaTime();
    }
    return 0;
}

}  // namespace zzgui

}  // namespace cozz
