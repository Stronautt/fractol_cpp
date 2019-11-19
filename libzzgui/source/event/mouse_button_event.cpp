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

#include "event/mouse_button_event.hpp"

namespace cozz {

namespace zzgui {

MouseButtonEvent::MouseButtonEvent(Window::ID window_id, KeyMap button, bool pressed, uint8_t clicks, uint64_t x,
                                   uint64_t y)
    : Event(Event::Type::kMouseButton, window_id),
      button_(button > KeyMap::kMouseButtonsBegin && button < KeyMap::kMouseButtonsEnd
                  ? button
                  : throw event_error("Invalid mouse button")),
      pressed_(pressed),
      clicks_(clicks),
      x_(x),
      y_(y) {}

KeyMap MouseButtonEvent::GetButton() const { return button_; }

bool MouseButtonEvent::IsPressed() const { return pressed_; }

uint8_t MouseButtonEvent::GetClicksCount() const { return clicks_; }

std::pair<uint64_t, uint64_t> MouseButtonEvent::GetPosition() const { return std::make_pair(x_, y_); }

}  // namespace zzgui

}  // namespace cozz
