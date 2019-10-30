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

#include <chrono>
#include <memory>
#include <thread>

#include <SDL2/SDL.h>

#include "controllers_manager.hpp"
#include "event/quit_event.hpp"
#include "event_handler.hpp"
#include "resources_manager.hpp"
#include "sdl_event_handler.hpp"
#include "widgets_manager.hpp"
#include "windows_manager.hpp"

namespace cozz {

namespace zzgui {

SdlApplication::SdlApplication()
    : is_running_(true),
      event_handler_(std::make_shared<zzgui::SDLEventHandler>()),
      windows_manager_(std::make_shared<zzgui::WindowsManager>(event_handler_)),
      resources_manager_(std::make_shared<zzgui::ResourcesManager>()),
      controller_manager_(std::make_shared<ControllersManager>(event_handler_, windows_manager_, resources_manager_)) {
    event_handler_->RegisterEventCallback<QuitEvent>(
        std::bind(static_cast<void (SdlApplication::*)(const QuitEvent&)>(&SdlApplication::Terminate), this,
                  std::placeholders::_1));
}

SdlApplication::~SdlApplication() = default;

void SdlApplication::Terminate(const QuitEvent&) { is_running_ = false; }

uint8_t SdlApplication::Run() {
    try {
        static thread_local auto tp = std::chrono::high_resolution_clock::now();
        std::chrono::milliseconds delay;

        while (is_running_) {
            event_handler_->Poll();
            if (is_running_) {
                controller_manager_->Render();
                windows_manager_->UpdateWindows();
                UpdateDeltaTime();

                const auto& now = std::chrono::high_resolution_clock::now();
                delay =
                    std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::milliseconds(17) - (now - tp));
                std::this_thread::sleep_for(delay);
                tp = now;
            }
        }
    } catch (const std::exception& e) {
        ShowErrorMessage(e.what());
        return Application::ExitCode::kGeneralFailure;
    } catch (...) {
        ShowErrorMessage("Unexpected fatal error occured");
        return Application::ExitCode::kFatalError;
    }
    return Application::ExitCode::kSuccess;
}

void SdlApplication::ShowInfoMessage(const std::string& message) const {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Info", message.c_str(), nullptr);
}

void SdlApplication::ShowErrorMessage(const std::string& message) const {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", message.c_str(), nullptr);
}

}  // namespace zzgui

}  // namespace cozz
