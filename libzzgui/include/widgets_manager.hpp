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

#ifndef LIBZZGUI_INCLUDE_WIDGETS_MANAGER_HPP_
#define LIBZZGUI_INCLUDE_WIDGETS_MANAGER_HPP_

#include <list>
#include <memory>

#include "event_handler.hpp"
#include "widget.hpp"
#include "window.hpp"

namespace cozz {

namespace zzgui {

class Widget;

class WidgetsManager final {
  public:
    explicit WidgetsManager(std::weak_ptr<EventHandler> event_handler);

    ~WidgetsManager();

    template <class WidgetType, class... Args>
    std::weak_ptr<WidgetType> Create(Window::ID id, const Args&... args);

    template <class WidgetType, class... Args>
    std::weak_ptr<WidgetType> Create(const Args&... args);

    const std::list<std::shared_ptr<Widget>>& GetWidgets() const;

  private:
    std::weak_ptr<EventHandler> event_handler_;

    std::list<std::shared_ptr<Widget>> widgets_;

    std::list<EventHandler::HandlerID> registered_callbacks_;
};

}  // namespace zzgui

}  // namespace cozz

#include "widgets_manager.tpp"

#endif  // LIBZZGUI_INCLUDE_WIDGETS_MANAGER_HPP_
