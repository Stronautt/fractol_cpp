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

#ifndef LIBZZGUI_INCLUDE_CONTROLLERS_MANAGER_HPP_
#define LIBZZGUI_INCLUDE_CONTROLLERS_MANAGER_HPP_

#include <memory>
#include <vector>

namespace cozz {

namespace zzgui {

class EventHandler;
class WindowsManager;
class ResourceManager;
class Controller;

class ControllersManager final {
  public:
    ControllersManager(std::weak_ptr<EventHandler> event_handler_, std::weak_ptr<WindowsManager> windows_manager_,
                       std::weak_ptr<ResourceManager> resource_manager_);

    void Push(std::shared_ptr<Controller> controller);

    void Pop();

    void Render() const;

    void Set(std::shared_ptr<Controller> controller);

    void Clear();

    std::weak_ptr<EventHandler> GetEventHandler() const;

    std::weak_ptr<WindowsManager> GetWindowsManager() const;

    std::weak_ptr<ResourceManager> GetResourceManager() const;

  private:
    std::weak_ptr<EventHandler> event_handler_;
    std::weak_ptr<WindowsManager> windows_manager_;
    std::weak_ptr<ResourceManager> resource_manager_;

    std::vector<std::shared_ptr<Controller>> controllers_;
};

}  // namespace zzgui

}  // namespace cozz

#endif  // LIBZZGUI_INCLUDE_CONTROLLERS_MANAGER_HPP_
