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

#ifndef LIBZZGUI_INCLUDE_INTERFACES_VIEW_HPP_
#define LIBZZGUI_INCLUDE_INTERFACES_VIEW_HPP_

#include <memory>

namespace cozz {

namespace zzgui {

class EventHandler;
class WindowsManager;
class ResourceManager;
class Model;
class Controller;

class View {
  public:
    virtual ~View();

    virtual void Create() = 0;

    virtual void Render(float delta) = 0;

    virtual void Resize(uint64_t width, uint64_t height) = 0;

    virtual void Show() = 0;

    virtual void Pause() = 0;

    virtual void Resume() = 0;

    virtual void Hide() = 0;

    void SetEventHandler(std::weak_ptr<EventHandler> event_handler);

    void SetWindowsManager(std::weak_ptr<WindowsManager> windows_manager);

    void SetResourceManager(std::weak_ptr<ResourceManager> resource_manager);

    void SetController(std::weak_ptr<Controller> controller);

    std::weak_ptr<EventHandler> GetEventHandler() const;

    std::weak_ptr<WindowsManager> GetWindowsManager() const;

    std::weak_ptr<ResourceManager> GetResourceManager() const;

    std::weak_ptr<Controller> GetController() const;

    std::weak_ptr<Model> GetModel() const;

  protected:
    std::weak_ptr<EventHandler> event_handler_;
    std::weak_ptr<WindowsManager> windows_manager_;
    std::weak_ptr<ResourceManager> resource_manager_;
    std::weak_ptr<Model> model_;
    std::weak_ptr<Controller> controller_;

    View(std::weak_ptr<Model> model);
};

}  // namespace zzgui

}  // namespace cozz

#endif  // LIBZZGUI_INCLUDE_INTERFACES_VIEW_HPP_
