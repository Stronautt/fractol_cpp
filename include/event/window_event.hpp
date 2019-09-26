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

#ifndef FRACTOL_INCLUDE_WINDOW_EVENT_HPP_
#define FRACTOL_INCLUDE_WINDOW_EVENT_HPP_

#include "event.hpp"

namespace cozz {

template <Event::Type EventType>
class WindowEvent : public Event {
  public:
    WindowEvent(uint32_t window_id) : Event(EventType, window_id) {}

    virtual ~WindowEvent() = default;
};

using WindowShownEvent = WindowEvent<Event::Type::kWindowShown>;
using WindowHiddenEvent = WindowEvent<Event::Type::kWindowHidden>;
using WindowExposedEvent = WindowEvent<Event::Type::kWindowExposed>;
using WindowMinimizedEvent = WindowEvent<Event::Type::kWindowMinimized>;
using WindowMaximizedEvent = WindowEvent<Event::Type::kWindowMaximized>;
using WindowRestoredEvent = WindowEvent<Event::Type::kWindowRestored>;
using WindowEnterEvent = WindowEvent<Event::Type::kWindowEnter>;
using WindowLeaveEvent = WindowEvent<Event::Type::kWindowLeave>;
using WindowFocusGainedEvent = WindowEvent<Event::Type::kWindowFocusGained>;
using WindowFocusLostEvent = WindowEvent<Event::Type::kWindowFocusLost>;
using WindowCloseEvent = WindowEvent<Event::Type::kWindowClose>;
using WindowTakeFocusEvent = WindowEvent<Event::Type::kWindowTakeFocus>;

}  // namespace cozz

#endif  // FRACTOL_INCLUDE_WINDOW_EVENT_HPP_
