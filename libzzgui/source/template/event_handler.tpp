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
EventHandler::HandlerID EventHandler::RegisterEventCallback(const std::function<void(const EventType&)>& callback) {
    return callbacks_map_.emplace(MakePair(callback, std::make_pair(false, 0)));
}

template <class EventType>
EventHandler::HandlerID EventHandler::RegisterEventCallback(const std::function<void(const EventType&)>& callback,
                                                            Window::ID id) {
    return callbacks_map_.emplace(MakePair(callback, std::make_pair(true, id)));
}

template <class EventType>
std::pair<Event::Type, std::tuple<bool, Window::ID, std::function<void(const Event&)>>> EventHandler::MakePair(
    const std::function<void(const EventType&)>& callback, const std::pair<bool, Window::ID>& window_id) const {
    static_assert(std::is_convertible<EventType, Event>::value);

    return std::make_pair(ConvertEventType(typeid(EventType)),
                          std::make_tuple(window_id.first, window_id.second, ConvertCallback(callback)));
}

template <class EventType>
std::function<void(const Event&)> EventHandler::ConvertCallback(
    const std::function<void(const EventType&)>& callback) const {
    return reinterpret_cast<const std::function<void(const Event&)>&>(callback);
}

}  // namespace zzgui

}  // namespace cozz
