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

namespace cozz {

namespace zzgui {

template <class EventType>
void EventHandler::PushEvent(const EventType& event) const {
    TriggerCallbacks(event);
}

template <class EventType>
EventHandler::HandlerID EventHandler::RegisterEventCallback(const std::function<bool(const EventType&)>& callback,
                                                            uint64_t priority) {
    return RegisterEventCallback(callback, Window::ID::kUnknown, priority);
}

template <class EventType>
EventHandler::HandlerID EventHandler::RegisterEventCallback(const std::function<bool(const EventType&)>& callback,
                                                            Window::ID id, uint64_t priority) {
    static_assert(std::is_convertible<EventType, Event>::value);

    const auto& event_type = ConvertEventType(typeid(EventType));

    auto callback_pair = std::make_pair(std::make_pair(id, priority), ConvertCallback(callback));

    HandlerID handler_id;
    handler_id.first = callbacks_map_.find(event_type);
    if (handler_id.first != callbacks_map_.end()) {
        handler_id.second = handler_id.first->second.emplace(callback_pair);
    } else {
        decltype(callbacks_map_.begin()->second) callbacks;

        handler_id.second = callbacks.emplace(callback_pair);
        handler_id.first = callbacks_map_.emplace(std::make_pair(event_type, std::move(callbacks))).first;
    }
    return handler_id;
}

template <class EventType>
std::function<bool(const Event&)> EventHandler::ConvertCallback(
    const std::function<bool(const EventType&)>& callback) const {
    return reinterpret_cast<const std::function<bool(const Event&)>&>(callback);
}

}  // namespace zzgui

}  // namespace cozz
