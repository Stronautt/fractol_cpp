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

#include "event.hpp"

namespace cozz {

namespace zzgui {

Event::Event(Type type, Window::ID window_id)
    : type_(type), timestamp_(std::chrono::system_clock::now()), window_id_(window_id) {}

Event::~Event() = default;

Event::Type Event::GetType() const { return type_; }

std::chrono::system_clock::time_point Event::GetTimestamp() const { return timestamp_; }

Window::ID Event::GetWindowId() const { return window_id_; }

}  // namespace zzgui

}  // namespace cozz
