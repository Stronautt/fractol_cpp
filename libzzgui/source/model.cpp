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

#include "model.hpp"

namespace cozz {

namespace zzgui {

Model::Model(std::weak_ptr<EventHandler> event_handler, std::weak_ptr<Controller> controller)
    : event_handler_(event_handler), controller_(controller) {
    if (event_handler_.expired() || controller_.expired()) {
        throw std::runtime_error("Bad event handler or controller");
    }
}

Model::~Model() = default;

std::weak_ptr<EventHandler> Model::GetEventHandler() const { return event_handler_; }

std::weak_ptr<Controller> Model::GetController() const { return controller_; }

}  // namespace zzgui

}  // namespace cozz
