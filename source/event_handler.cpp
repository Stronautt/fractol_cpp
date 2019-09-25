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

#include "event_handler.hpp"

namespace cozz {

EventHandler::~EventHandler() = default;

void EventHandler::UnregisterEventCallback(EventHandlerID id) { callbacks_map_.erase(id); }

void EventHandler::TriggerCallbacks(const Event& event) const {
    for (auto it = callbacks_map_.find(event.GetType()); it != callbacks_map_.end() && it->first == event.GetType();
         it++) {
        it->second(event);
    }
}

}  // namespace cozz
