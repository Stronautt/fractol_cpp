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

#include <algorithm>
#include <stdexcept>

#include "window.hpp"

namespace cozz {

namespace zzgui {

using std::placeholders::_1;

EventHandler::~EventHandler() = default;

bool EventHandler::CallbacksComarator::operator()(std::pair<Window::ID, uint64_t> pair_a,
                                                  std::pair<Window::ID, uint64_t> pair_b) {
    if (pair_a.first == pair_b.first) {
        return pair_a.second > pair_b.second;
    } else {
        return pair_a.first < pair_b.first;
    }
}

std::list<EventHandler::HandlerID> EventHandler::RegisterWindowEventCallbacks(Window& window) {
    const auto& window_id = window.GetId();
    return {RegisterEventCallback<WindowMovedEvent>(std::bind(&Window::OnMove, &window, _1), window_id),
            RegisterEventCallback<WindowResizedEvent>(std::bind(&Window::OnResize, &window, _1), window_id),
            RegisterEventCallback<WindowCloseEvent>(std::bind(&Window::OnClose, &window, _1), window_id)};
}

void EventHandler::UnregisterEventCallback(HandlerID id) { id.first->second.erase(id.second); }

void EventHandler::UnregisterEventCallbacks(const std::list<HandlerID>& ids) {
    std::for_each(ids.begin(), ids.end(), std::bind(&EventHandler::UnregisterEventCallback, this, _1));
}

bool EventHandler::TriggerCallbacks(const Event& e) const {
    try {
        const auto callbacks = callbacks_map_.at(e.GetType());

        bool callback_triggered = false;
        for (const auto& callback_pair : callbacks) {
            const auto& window_id = callback_pair.first.first;
            const auto& event_callback = callback_pair.second;

            if (window_id != Window::ID::kUnknown && e.GetWindowId() != window_id) {
                continue;
            } else if (event_callback && event_callback(e)) {
                return true;
            }
            callback_triggered = true;
        }
        return callback_triggered;
    } catch (const std::out_of_range&) {
        return false;
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
