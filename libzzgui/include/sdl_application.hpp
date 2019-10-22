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

#ifndef LIBZZGUI_INCLUDE_SDL_APPLICATION_HPP_
#define LIBZZGUI_INCLUDE_SDL_APPLICATION_HPP_

#include "application.hpp"

#include <atomic>
#include <cstdint>
#include <memory>

namespace cozz {

namespace zzgui {

class EventHandler;
class WindowsManager;
class ResourcesManager;
class ControllersManager;
class QuitEvent;

class SdlApplication : public Application {
  public:
    SdlApplication();
    virtual ~SdlApplication();

    virtual uint8_t Run() override;

  protected:
    std::atomic<bool> is_running_;

    std::shared_ptr<EventHandler> event_handler_;
    std::shared_ptr<WindowsManager> windows_manager_;
    std::shared_ptr<ResourcesManager> resources_manager_;

    std::unique_ptr<ControllersManager> controller_manager_;

    virtual void Terminate(const QuitEvent& event) override;
};

}  // namespace zzgui

}  // namespace cozz

#endif  // LIBZZGUI_INCLUDE_SDL_APPLICATION_HPP_
