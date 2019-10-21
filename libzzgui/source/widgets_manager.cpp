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

#include "widgets_manager.hpp"

namespace cozz {

namespace zzgui {

WidgetsManager::WidgetsManager(std::weak_ptr<EventHandler> event_handler) : event_handler_(event_handler) {
    if (event_handler_.expired()) {
        throw std::runtime_error("Bad event handler");
    }
}

WidgetsManager::~WidgetsManager() { event_handler_.lock()->UnregisterEventCallbacks(registered_callbacks_); }

const std::list<std::shared_ptr<Widget>>& WidgetsManager::GetWidgets() const { return widgets_; }

}  // namespace zzgui

}  // namespace cozz
