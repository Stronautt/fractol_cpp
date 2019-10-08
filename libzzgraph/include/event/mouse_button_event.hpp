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

#ifndef FRACTOL_INCLUDE_EVENT_MOUSE_BUTTON_EVENT_HPP_
#define FRACTOL_INCLUDE_EVENT_MOUSE_BUTTON_EVENT_HPP_

#include "event.hpp"

#include <utility>

#include "key_map.hpp"

namespace cozz {

class MouseButtonEvent final : public Event {
  public:
    MouseButtonEvent(uint32_t window_id, KeyMap button, bool pressed, uint8_t clicks, uint64_t x, uint64_t y);

    KeyMap GetButton() const;

    bool IsPressed() const;

    uint8_t GetClicksCount() const;

    std::pair<uint64_t, uint64_t> GetPosition() const;

  protected:
    KeyMap button_;
    bool pressed_;
    uint8_t clicks_;
    uint64_t x_;
    uint64_t y_;
};

}  // namespace cozz

#endif  // FRACTOL_INCLUDE_EVENT_MOUSE_BUTTON_EVENT_HPP_
