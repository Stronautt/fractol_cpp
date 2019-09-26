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

#ifndef FRACTOL_INCLUDE_window_resized_event_HPP_
#define FRACTOL_INCLUDE_window_resized_event_HPP_

#include "window_event.hpp"

#include <cstdint>
#include <utility>

namespace cozz {

class WindowResizedEvent final : public WindowEvent<Event::Type::kWindowResized> {
  public:
    WindowResizedEvent(uint32_t window_id, int32_t new_width, int32_t new_height);

    std::pair<int32_t, int32_t> GetSize() const;

  protected:
    int32_t new_width_;
    int32_t new_height_;
};

}  // namespace cozz

#endif  // FRACTOL_INCLUDE_window_resized_event_HPP_
