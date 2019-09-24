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

#include "event/window_event.hpp"

namespace cozz {

WindowEvent::WindowEvent(uint32_t window_id, WindowEvent::Type type)
    : Event(Event::Type::kWindow, window_id), event_(type) {}

WindowEvent::~WindowEvent() = default;

WindowEvent::Type WindowEvent::GetEvent() const { return event_; }

}  // namespace cozz
