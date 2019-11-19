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

#ifndef LIBZZGUI_INCLUDE_WINDOW_MANAGER_HPP_
#define LIBZZGUI_INCLUDE_WINDOW_MANAGER_HPP_

#include "window.hpp"

#include <functional>
#include <list>
#include <map>
#include <memory>
#include <utility>

#include "event_handler.hpp"

namespace cozz {

namespace zzgui {

class WindowsManager final {
  public:
    WindowsManager(std::shared_ptr<EventHandler> event_handler);

    template <class WindowType>
    std::weak_ptr<WindowType> CreateWindow(std::string title, uint64_t width, uint64_t height);

    template <class WindowType>
    std::weak_ptr<WindowType> CreateWindow(std::string title, uint64_t x, uint64_t y, uint64_t width, uint64_t height);

    void UpdateWindows() const;

    std::weak_ptr<Window> GetById(Window::ID id) const;

    std::shared_ptr<EventHandler> GetEventHandler() const;

  private:
    std::shared_ptr<EventHandler> event_handler_;
    std::map<Window::ID, std::pair<std::shared_ptr<Window>, std::list<EventHandler::HandlerID>>> windows_;

    bool OnWindowClose(const WindowCloseEvent& event);
};

}  // namespace zzgui

}  // namespace cozz

#include "windows_manager.tpp"

#endif  // LIBZZGUI_INCLUDE_WINDOW_MANAGER_HPP_
