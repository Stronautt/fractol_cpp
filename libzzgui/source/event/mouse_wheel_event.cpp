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

#include "event/mouse_wheel_event.hpp"

namespace cozz {

namespace zzgui {

MouseWheelEvent::MouseWheelEvent(Window::ID window_id, uint64_t x, uint64_t y, int64_t scrolled_x, int64_t scrolled_y,
                                 bool inversed)
    : Event(Event::Type::kMouseWheel, window_id),
      x_(x),
      y_(y),
      scrolled_x_(scrolled_x),
      scrolled_y_(scrolled_y),
      inversed_(inversed) {}

std::pair<uint64_t, uint64_t> MouseWheelEvent::GetPosition() const { return std::make_pair(x_, y_); }

int64_t MouseWheelEvent::GetScrolledByX() const { return scrolled_x_; }

int64_t MouseWheelEvent::GetScrolledByY() const { return scrolled_y_; }

bool MouseWheelEvent::IsInversed() const { return inversed_; }

}  // namespace zzgui

}  // namespace cozz
