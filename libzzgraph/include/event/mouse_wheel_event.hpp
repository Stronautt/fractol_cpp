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

#ifndef FRACTOL_INCLUDE_EVENT_MOUSE_WHEEL_EVENT_HPP_
#define FRACTOL_INCLUDE_EVENT_MOUSE_WHEEL_EVENT_HPP_

#include "event.hpp"

namespace cozz {

class MouseWheelEvent final : public Event {
  public:
    MouseWheelEvent(uint32_t window_id, int32_t scrolled_x, int32_t scrolled_y, bool inversed);

    int32_t GetScrolledByX() const;

    int32_t GetScrolledByY() const;

    bool IsInversed() const;

  protected:
    int32_t scrolled_x_;
    int32_t scrolled_y_;
    bool inversed_;
};

}  // namespace cozz

#endif  // FRACTOL_INCLUDE_EVENT_MOUSE_WHEEL_EVENT_HPP_
