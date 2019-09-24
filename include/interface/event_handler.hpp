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

#ifndef FRACTOL_INCLUDE_INTERFACE_EVENT_HANDLER_HPP_
#define FRACTOL_INCLUDE_INTERFACE_EVENT_HANDLER_HPP_

#include <functional>

namespace cozz {

#include "Event.hpp"

class EventHandler {
  public:
    virtual ~EventHandler() = default;

    virtual bool Poll() = 0;

    uint64_t RegisterEventCallback(Event::Type type, std::function<void(const Event&)>) final;

    void UnregisterEventCallback(Event::Type type, uint64_t id) final;
};

}  // namespace cozz

#endif  // FRACTOL_INCLUDE_INTERFACE_EVENT_HANDLER_HPP_
