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

#ifndef LIBZZGUI_INCLUDE_EVENT_MOUSE_MOTION_EVENT_HPP_
#define LIBZZGUI_INCLUDE_EVENT_MOUSE_MOTION_EVENT_HPP_

#include "event.hpp"

#include <utility>

namespace cozz {

namespace zzgui {

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

    MouseMotionEvent(uint32_t window_id, ButtonState state, uint64_t x, uint64_t y, int64_t x_dir, int64_t y_dir);

    std::pair<uint64_t, uint64_t> GetPosition() const;

    std::pair<int64_t, int64_t> GetDirection() const;

    bool IsLeftButtonPressed() const;

    bool IsMiddleButtonPressed() const;

    bool IsRightButtonPressed() const;

    bool IsExtra1ButtonPressed() const;

    bool IsExtra2ButtonPressed() const;

  protected:
    ButtonState state_;
    uint64_t x_;
    uint64_t y_;
    int64_t x_dir_;
    int64_t y_dir_;
};

MouseMotionEvent::ButtonState operator|(MouseMotionEvent::ButtonState a, MouseMotionEvent::ButtonState b);

MouseMotionEvent::ButtonState operator&(MouseMotionEvent::ButtonState a, MouseMotionEvent::ButtonState b);

MouseMotionEvent::ButtonState& operator|=(MouseMotionEvent::ButtonState& a, MouseMotionEvent::ButtonState b);

}  // namespace zzgui

}  // namespace cozz

#endif  // LIBZZGUI_INCLUDE_EVENT_MOUSE_MOTION_EVENT_HPP_
