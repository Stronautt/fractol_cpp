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

#include "event_handler.hpp"

#include "window.hpp"

namespace cozz {

namespace zzgui {

using std::placeholders::_1;

EventHandler::~EventHandler() = default;

std::list<EventHandler::HandlerID> EventHandler::RegisterWindowEventCallbacks(Window& window) {
    return {RegisterEventCallback<WindowMovedEvent>(std::bind(&Window::OnMove, &window, _1)),
            RegisterEventCallback<WindowResizedEvent>(std::bind(&Window::OnResize, &window, _1))};
}

void EventHandler::UnregisterEventCallback(HandlerID id) { callbacks_map_.erase(id); }

void EventHandler::UnregisterEventCallbacks(const std::list<HandlerID>& ids) {
    std::for_each(ids.begin(), ids.end(), std::bind(&EventHandler::UnregisterEventCallback, this, _1));
}

void EventHandler::TriggerCallbacks(const Event& e) const {
    for (auto it = callbacks_map_.find(e.GetType()); it != callbacks_map_.end() && it->first == e.GetType(); it++) {
        const auto& event_callback = it->second;
        event_callback(e);
    }
}

Event::Type EventHandler::ConvertEventType(const std::type_info& type) const {
    /* clang-format off */
    if      (type == typeid(WindowShownEvent))          { return Event::Type::kWindowShown; }
    else if (type == typeid(WindowHiddenEvent))         { return Event::Type::kWindowHidden; }
    else if (type == typeid(WindowExposedEvent))        { return Event::Type::kWindowExposed; }
    else if (type == typeid(WindowMovedEvent))          { return Event::Type::kWindowMoved; }
    else if (type == typeid(WindowResizedEvent))        { return Event::Type::kWindowResized; }
    else if (type == typeid(WindowMinimizedEvent))      { return Event::Type::kWindowMinimized; }
    else if (type == typeid(WindowMaximizedEvent))      { return Event::Type::kWindowMaximized; }
    else if (type == typeid(WindowRestoredEvent))       { return Event::Type::kWindowRestored; }
    else if (type == typeid(WindowEnterEvent))          { return Event::Type::kWindowEnter; }
    else if (type == typeid(WindowLeaveEvent))          { return Event::Type::kWindowLeave; }
    else if (type == typeid(WindowFocusGainedEvent))    { return Event::Type::kWindowFocusGained; }
    else if (type == typeid(WindowFocusLostEvent))      { return Event::Type::kWindowFocusLost; }
    else if (type == typeid(WindowCloseEvent))          { return Event::Type::kWindowClose; }
    else if (type == typeid(WindowTakeFocusEvent))      { return Event::Type::kWindowTakeFocus; }
    else if (type == typeid(KeyboardEvent))             { return Event::Type::kKeyboard; }
    else if (type == typeid(MouseMotionEvent))          { return Event::Type::kMouseMotion; }
    else if (type == typeid(MouseButtonEvent))          { return Event::Type::kMouseButton; }
    else if (type == typeid(MouseWheelEvent))           { return Event::Type::kMouseWheel; }
    else if (type == typeid(QuitEvent))                 { return Event::Type::kQuit; }
    else {
        throw std::out_of_range("Unknown event type");
    }
    /* clang-format on */
}

}  // namespace zzgui

}  // namespace cozz
