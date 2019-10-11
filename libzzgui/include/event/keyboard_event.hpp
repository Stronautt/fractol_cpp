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

#ifndef LIBZZGUI_INCLUDE_EVENT_KEYBOARD_EVENT_HPP_
#define LIBZZGUI_INCLUDE_EVENT_KEYBOARD_EVENT_HPP_

#include "event.hpp"

#include "key_map.hpp"

namespace cozz {

namespace zzgui {

class KeyboardEvent final : public Event {
  public:
    KeyboardEvent(uint32_t window_id, bool pressed, bool is_repeat, KeyMap key);

    bool IsPressed() const;

    bool IsRepeat() const;

    KeyMap GetKey() const;

  protected:
    bool pressed_;
    bool is_repeat_;
    KeyMap key_;
};

}  // namespace zzgui

}  // namespace cozz

#endif  // LIBZZGUI_INCLUDE_EVENT_KEYBOARD_EVENT_HPP_
