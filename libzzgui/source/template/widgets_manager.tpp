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

#include "widgets_manager.hpp"

namespace cozz {

namespace zzgui {

template <class WidgetType, class... Args>
std::shared_ptr<WidgetType> WidgetsManager::Create(Window::ID id, const Args&... args) {
    auto widget = std::make_shared<WidgetType>(args...);

    registered_callbacks_.emplace_front(event_handler_.lock()->RegisterEventCallback<MouseButtonEvent>(
        std::bind(&Widget::OnMouseButton, widget.get(), std::placeholders::_1), id));
    registered_callbacks_.emplace_front(event_handler_.lock()->RegisterEventCallback<MouseMotionEvent>(
        std::bind(&Widget::OnMouseMotion, widget.get(), std::placeholders::_1), id));

    widgets_.emplace_back(widget);
    return widget;
}

template <class WidgetType, class... Args>
std::shared_ptr<WidgetType> WidgetsManager::Create(const Args&... args) {
    auto widget = std::make_shared<WidgetType>(args...);

    registered_callbacks_.emplace_front(event_handler_.lock()->RegisterEventCallback<MouseButtonEvent>(
        std::bind(&Widget::OnMouseButton, widget.get(), std::placeholders::_1)));
    registered_callbacks_.emplace_front(event_handler_.lock()->RegisterEventCallback<MouseMotionEvent>(
        std::bind(&Widget::OnMouseMotion, widget.get(), std::placeholders::_1)));

    widgets_.emplace_back(widget);
    return widget;
}

}  // namespace zzgui

}  // namespace cozz
