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

#include "event/window_resized_event.hpp"

namespace cozz {

namespace zzgui {

WindowResizedEvent::WindowResizedEvent(Window::ID window_id, uint64_t new_width, uint64_t new_height)
    : WindowEvent(window_id), new_width_(new_width), new_height_(new_height) {}

std::pair<uint64_t, uint64_t> WindowResizedEvent::GetSize() const { return std::make_pair(new_width_, new_height_); }

}  // namespace zzgui

}  // namespace cozz
