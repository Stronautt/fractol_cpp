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

#ifndef LIBZZGUI_INCLUDE_EVENT_WINDOW_RESIZED_EVENT_HPP_
#define LIBZZGUI_INCLUDE_EVENT_WINDOW_RESIZED_EVENT_HPP_

#include "window_event.hpp"

#include <cstdint>
#include <utility>

namespace cozz {

namespace zzgui {

class WindowResizedEvent final : public WindowEvent<Event::Type::kWindowResized> {
  public:
    WindowResizedEvent(Window::ID window_id, uint64_t new_width, uint64_t new_height);

    std::pair<uint64_t, uint64_t> GetSize() const;

  protected:
    uint64_t new_width_;
    uint64_t new_height_;
};

}  // namespace zzgui

}  // namespace cozz

#endif  // LIBZZGUI_INCLUDE_EVENT_WINDOW_RESIZED_EVENT_HPP_
