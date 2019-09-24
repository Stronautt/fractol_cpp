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

#include "event/mouse_motion_event.hpp"

namespace cozz {

MouseMotionEvent::MouseMotionEvent(uint32_t window_id, ButtonState state, int32_t x, int32_t y)
    : Event(Event::Type::kMouseMotion, window_id), state_(state), x_(x), y_(y) {}

std::pair<int32_t, int32_t> MouseMotionEvent::GetPosition() const { return std::make_pair(x_, y_); }

bool MouseMotionEvent::IsLeftButtonPressed() const { return state_ & ButtonState::kLeftPressed; }

bool MouseMotionEvent::IsMiddleButtonPressed() const { return state_ & ButtonState::kMiddlePressed; }

bool MouseMotionEvent::IsRightButtonPressed() const { return state_ & ButtonState::kRightPressed; }

bool MouseMotionEvent::IsExtra1ButtonPressed() const { return state_ & ButtonState::kExtra1Pressed; }

bool MouseMotionEvent::IsExtra2ButtonPressed() const { return state_ & ButtonState::kExtra2Pressed; }

}  // namespace cozz
