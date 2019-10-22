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

#ifndef LIBZZGUI_INCLUDE_INTERFACES_BASE_MODEL_HPP_
#define LIBZZGUI_INCLUDE_INTERFACES_BASE_MODEL_HPP_

#include <memory>

namespace cozz {

namespace zzgui {

class EventHandler;
class WindowsManager;
class ResourcesManager;
class BaseController;

class BaseModel {
  public:
    virtual ~BaseModel() = default;

    virtual void Create() = 0;

    virtual void Update(float delta) = 0;

    virtual void SetEventHandler(std::weak_ptr<EventHandler> event_handler) = 0;

    virtual void SetWindowsManager(std::weak_ptr<WindowsManager> windows_manager) = 0;

    virtual void SetResourcesManager(std::weak_ptr<ResourcesManager> resources_manager) = 0;

    virtual void SetBaseController(std::weak_ptr<BaseController> controller) = 0;

    virtual std::weak_ptr<EventHandler> GetEventHandler() const = 0;

    virtual std::weak_ptr<WindowsManager> GetWindowsManager() const = 0;

    virtual std::weak_ptr<ResourcesManager> GetResourcesManager() const = 0;

    virtual std::weak_ptr<BaseController> GetBaseController() const = 0;
};

}  // namespace zzgui

}  // namespace cozz

#endif  // LIBZZGUI_INCLUDE_INTERFACES_BASE_MODEL_HPP_
