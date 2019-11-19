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

#ifndef LIBZZGUI_INCLUDE_EVENT_WINDOW_EVENT_HPP_
#define LIBZZGUI_INCLUDE_EVENT_WINDOW_EVENT_HPP_

#include "event.hpp"
#include "window.hpp"

namespace cozz {

namespace zzgui {

template <Event::Type EventType>
class WindowEvent : public Event {
  public:
    WindowEvent(Window::ID window_id) : Event(EventType, window_id) {}

    virtual ~WindowEvent() = default;
};

class WindowShownEvent : public WindowEvent<Event::Type::kWindowShown> {
    using WindowEvent::WindowEvent;
};
class WindowHiddenEvent : public WindowEvent<Event::Type::kWindowHidden> {
    using WindowEvent::WindowEvent;
};
class WindowExposedEvent : public WindowEvent<Event::Type::kWindowExposed> {
    using WindowEvent::WindowEvent;
};
class WindowMinimizedEvent : public WindowEvent<Event::Type::kWindowMinimized> {
    using WindowEvent::WindowEvent;
};
class WindowMaximizedEvent : public WindowEvent<Event::Type::kWindowMaximized> {
    using WindowEvent::WindowEvent;
};
class WindowRestoredEvent : public WindowEvent<Event::Type::kWindowRestored> {
    using WindowEvent::WindowEvent;
};
class WindowEnterEvent : public WindowEvent<Event::Type::kWindowEnter> {
    using WindowEvent::WindowEvent;
};
class WindowLeaveEvent : public WindowEvent<Event::Type::kWindowLeave> {
    using WindowEvent::WindowEvent;
};
class WindowFocusGainedEvent : public WindowEvent<Event::Type::kWindowFocusGained> {
    using WindowEvent::WindowEvent;
};
class WindowFocusLostEvent : public WindowEvent<Event::Type::kWindowFocusLost> {
    using WindowEvent::WindowEvent;
};
class WindowCloseEvent : public WindowEvent<Event::Type::kWindowClose> {
    using WindowEvent::WindowEvent;
};
class WindowTakeFocusEvent : public WindowEvent<Event::Type::kWindowTakeFocus> {
    using WindowEvent::WindowEvent;
};

}  // namespace zzgui

}  // namespace cozz

#endif  // LIBZZGUI_INCLUDE_EVENT_WINDOW_EVENT_HPP_
