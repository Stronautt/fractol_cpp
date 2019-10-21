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

#ifndef LIBZZGUI_INCLUDE_INTERFACES_BASE_VIEW_HPP_
#define LIBZZGUI_INCLUDE_INTERFACES_BASE_VIEW_HPP_

#include <cstdint>
#include <memory>

namespace cozz {

namespace zzgui {

class Window;
class EventHandler;
class WindowsManager;
class ResourceManager;
class BaseModel;
class BaseController;

class BaseView {
  public:
    virtual ~BaseView() = default;

    virtual void Create() = 0;

    virtual void Render(float delta) = 0;

    virtual void Resized(std::weak_ptr<Window> window) = 0;

    virtual void Show() = 0;

    virtual void Pause() = 0;

    virtual void Resume() = 0;

    virtual void Hide() = 0;

    virtual void SetEventHandler(std::weak_ptr<EventHandler> event_handler) = 0;

    virtual void SetWindowsManager(std::weak_ptr<WindowsManager> windows_manager) = 0;

    virtual void SetResourceManager(std::weak_ptr<ResourceManager> resource_manager) = 0;

    virtual void SetBaseModel(std::weak_ptr<BaseModel> model) = 0;

    virtual void SetBaseController(std::weak_ptr<BaseController> controller) = 0;

    virtual std::weak_ptr<EventHandler> GetEventHandler() const = 0;

    virtual std::weak_ptr<WindowsManager> GetWindowsManager() const = 0;

    virtual std::weak_ptr<ResourceManager> GetResourceManager() const = 0;

    virtual std::weak_ptr<BaseModel> GetBaseModel() const = 0;

    virtual std::weak_ptr<BaseController> GetBaseController() const = 0;
};

}  // namespace zzgui

}  // namespace cozz

#endif  // LIBZZGUI_INCLUDE_INTERFACES_BASE_VIEW_HPP_
