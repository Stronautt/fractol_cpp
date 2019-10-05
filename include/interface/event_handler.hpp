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
#include <list>
#include <stdexcept>
#include <typeinfo>

#include "event.hpp"
#include "event/keyboard_event.hpp"
#include "event/mouse_button_event.hpp"
#include "event/mouse_motion_event.hpp"
#include "event/mouse_wheel_event.hpp"
#include "event/quit_event.hpp"
#include "event/window_event.hpp"
#include "event/window_moved_event.hpp"
#include "event/window_resized_event.hpp"

namespace cozz {

class Window;

class EventHandler {
  public:
    using HandlerID = std::multimap<Event::Type, std::function<void(const Event&)>>::iterator;

    virtual ~EventHandler();

    virtual bool Poll() const = 0;

    template <class EventType>
    HandlerID RegisterEventCallback(const std::function<void(const EventType&)>& callback) {
        return callbacks_map_.emplace(MakePair(callback));
    }

    virtual std::list<HandlerID> RegisterWindowEventCallbacks(Window& window) final;

    virtual void UnregisterEventCallback(HandlerID id) final;

    virtual void UnregisterEventCallbacks(const std::list<HandlerID>& ids) final;

  protected:
    std::multimap<Event::Type, std::function<void(const Event&)>> callbacks_map_;

    virtual void TriggerCallbacks(const Event& event) const final;

  private:
    template <class EventType>
    std::pair<Event::Type, std::function<void(const Event&)>> MakePair(const std::function<void(const EventType&)>& callback) const {
        static_assert(std::is_convertible<EventType, Event>::value);

        return std::make_pair(ConvertEventType(typeid(EventType)), ConvertCallback(callback));
    }

    Event::Type ConvertEventType(const std::type_info& type) const;

    template <class EventType>
    std::function<void(const Event&)> ConvertCallback(const std::function<void(const EventType&)>& callback) const {
        return reinterpret_cast<const std::function<void(const Event&)>&>(callback);
    }
};

}  // namespace cozz

#endif  // FRACTOL_INCLUDE_INTERFACE_EVENT_HANDLER_HPP_
