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

#ifndef FRACTOL_INCLUDE_EVENT_MOUSE_MOTION_EVENT_HPP_
#define FRACTOL_INCLUDE_EVENT_MOUSE_MOTION_EVENT_HPP_

#include "event.hpp"

#include <utility>

namespace cozz {

class MouseMotionEvent final : public Event {
  public:
    enum ButtonState : uint8_t {
        kReleased = 0x0,
        kLeftPressed = 0x1,    /* 0000 0001 */
        kMiddlePressed = 0x2,  /* 0000 0010 */
        kRightPressed = 0x4,   /* 0000 0100 */
        kExtra1Pressed = 0x8,  /* 0000 1000 */
        kExtra2Pressed = 0x10, /* 0001 0000 */
    };

    MouseMotionEvent(uint32_t window_id, ButtonState state, int32_t x, int32_t y);

    std::pair<int32_t, int32_t> GetPosition() const;

    bool IsLeftButtonPressed() const;

    bool IsMiddleButtonPressed() const;

    bool IsRightButtonPressed() const;

    bool IsExtra1ButtonPressed() const;

    bool IsExtra2ButtonPressed() const;

  protected:
    ButtonState state_;
    int32_t x_;
    int32_t y_;
};

MouseMotionEvent::ButtonState operator|(MouseMotionEvent::ButtonState a, MouseMotionEvent::ButtonState b);

MouseMotionEvent::ButtonState operator&(MouseMotionEvent::ButtonState a, MouseMotionEvent::ButtonState b);

MouseMotionEvent::ButtonState& operator|=(MouseMotionEvent::ButtonState& a, MouseMotionEvent::ButtonState b);

}  // namespace cozz

#endif  // FRACTOL_INCLUDE_EVENT_MOUSE_MOTION_EVENT_HPP_
