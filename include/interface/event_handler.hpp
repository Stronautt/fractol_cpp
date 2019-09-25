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

#ifndef FRACTOL_INCLUDE_INTERFACE_EVENT_HANDLER_HPP_
#define FRACTOL_INCLUDE_INTERFACE_EVENT_HANDLER_HPP_

#include <functional>
#include <map>
#include <stdexcept>
#include <typeindex>

#include "event.hpp"
#include "event/keyboard_event.hpp"
#include "event/mouse_button_event.hpp"
#include "event/mouse_motion_event.hpp"
#include "event/mouse_wheel_event.hpp"
#include "event/quit_event.hpp"
#include "event/window_event.hpp"

namespace cozz {

class EventHandler {
  public:
    using EventHandlerID = const std::multimap<Event::Type, std::function<void(const Event&)>>::iterator;

    virtual ~EventHandler();

    virtual bool Poll() const = 0;

    template <class EventType>
    EventHandlerID RegisterEventCallback(const std::function<void(const EventType&)>& callback) {
        static const std::map<std::type_index, Event::Type> event_types_map = {
            {std::type_index(typeid(WindowEvent)), Event::Type::kWindow},
            {std::type_index(typeid(KeyboardEvent)), Event::Type::kKeyboard},
            {std::type_index(typeid(MouseMotionEvent)), Event::Type::kMouseMotion},
            {std::type_index(typeid(MouseButtonEvent)), Event::Type::kMouseButton},
            {std::type_index(typeid(MouseWheelEvent)), Event::Type::kMouseWheel},
            {std::type_index(typeid(QuitEvent)), Event::Type::kQuit},
        };

        try {
            return callbacks_map_.emplace(event_types_map.at(std::type_index(typeid(EventType))),
                                          reinterpret_cast<const std::function<void(const Event&)>&>(callback));
        } catch (const std::out_of_range&) {
            throw std::logic_error("Unknown event type");
        }
    }

    virtual void UnregisterEventCallback(EventHandlerID id) final;

  protected:
    std::multimap<Event::Type, std::function<void(const Event&)>> callbacks_map_;

    void TriggerCallbacks(const Event& event) const;
};

}  // namespace cozz

#endif  // FRACTOL_INCLUDE_INTERFACE_EVENT_HANDLER_HPP_
