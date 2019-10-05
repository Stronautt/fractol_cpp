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

#ifndef FRACTOL_INCLUDE_WINDOW_MANAGER_HPP_
#define FRACTOL_INCLUDE_WINDOW_MANAGER_HPP_

#include "window.hpp"

#include <memory>
#include <map>
#include <list>
#include <utility>
#include <functional>

#include "event_handler.hpp"

namespace cozz {

class WindowsManager final {
  public:
    WindowsManager(std::shared_ptr<EventHandler> event_handler);

    template <class WindowType>
    std::weak_ptr<Window> CreateWindow(std::string title, uint64_t width, uint64_t height) {
        return CreateWindow<WindowType>(title, 0, 0, width, height);
    }

    template <class WindowType>
    std::weak_ptr<Window> CreateWindow(std::string title, uint64_t x, uint64_t y, uint64_t width, uint64_t height) {
        auto window = std::make_shared<WindowType>(title, x, y, width, height);

        windows_.emplace(window->GetId(), std::make_pair(window, event_handler_->RegisterWindowEventCallbacks(*window)));

        return window;
    }

    void UpdateWindows() const;

    std::weak_ptr<Window> GetById(Window::ID id) const;

    std::shared_ptr<EventHandler> GetEventHandler() const;

  private:
    std::shared_ptr<EventHandler> event_handler_;
    std::map<Window::ID, std::pair<std::shared_ptr<Window>, std::list<EventHandler::HandlerID>>> windows_;

    void OnWindowClose(const WindowCloseEvent& event);
};

}  // namespace cozz

#endif  // FRACTOL_INCLUDE_WINDOW_MANAGER_HPP_
