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

#ifndef LIBZZGUI_INCLUDE_INTERFACES_EVENT_HANDLER_HPP_
#define LIBZZGUI_INCLUDE_INTERFACES_EVENT_HANDLER_HPP_

#include <functional>
#include <list>
#include <map>
#include <typeinfo>
#include <utility>

#include "event.hpp"
#include "event/keyboard_event.hpp"
#include "event/mouse_button_event.hpp"
#include "event/mouse_motion_event.hpp"
#include "event/mouse_wheel_event.hpp"
#include "event/quit_event.hpp"
#include "event/window_event.hpp"
#include "event/window_moved_event.hpp"
#include "event/window_resized_event.hpp"
#include "window.hpp"

namespace cozz {

namespace zzgui {

class EventHandler {
  public:
    struct CallbacksComarator {
        bool operator()(const std::pair<Window::ID, uint64_t>& pair_a,
                        const std::pair<Window::ID, uint64_t>& pair_b) const;
    };
    using HandlerID =
        std::pair<std::map<Event::Type, std::multimap<std::pair<Window::ID, uint64_t>,
                                                      std::function<bool(const Event&)>, CallbacksComarator>>::iterator,
                  std::multimap<std::pair<Window::ID, uint64_t>, std::function<bool(const Event&)>,
                                CallbacksComarator>::iterator>;

    virtual ~EventHandler();

    virtual bool Poll() const = 0;

    template <class EventType>
    void PushEvent(const EventType& event) const;

    template <class EventType>
    HandlerID RegisterEventCallback(const std::function<bool(const EventType&)>& callback, uint64_t priority = 0);

    template <class EventType>
    HandlerID RegisterEventCallback(const std::function<bool(const EventType&)>& callback, Window::ID id,
                                    uint64_t priority = 0);

    virtual std::list<HandlerID> RegisterWindowEventCallbacks(Window& window) final;

    virtual void UnregisterEventCallback(HandlerID id) final;

    virtual void UnregisterEventCallbacks(const std::list<HandlerID>& ids) final;

  protected:
    std::map<Event::Type,
             std::multimap<std::pair<Window::ID, uint64_t>, std::function<bool(const Event&)>, CallbacksComarator>>
        callbacks_map_;

    virtual bool TriggerCallbacks(const Event& event) const final;

  private:
    Event::Type ConvertEventType(const std::type_info& type) const;

    template <class EventType>
    std::function<bool(const Event&)> ConvertCallback(const std::function<bool(const EventType&)>& callback) const;
};

}  // namespace zzgui

}  // namespace cozz

#include "event_handler.tpp"

#endif  // LIBZZGUI_INCLUDE_INTERFACES_EVENT_HANDLER_HPP_
