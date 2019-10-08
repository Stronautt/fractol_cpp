/*
 * This file is part of LibZZmvc.

 * LibZZmvc is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * LibZZmvc is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with LibZZmvc. If not, see <https://www.gnu.org/licenses/>.
 *
 * Author: Pavlo Hrytsenko
*/

#include "controllers_manager.hpp"

#include <algorithm>

#include "controller.hpp"

namespace cozz {

namespace zzmvc {

void ControllersManager::Push(std::shared_ptr<Controller> controller) { controllers_.emplace_back(controller); }

void ControllersManager::Pop() { controllers_.pop_back(); }

void ControllersManager::Render() const {
    std::for_each(controllers_.begin(), controllers_.end(), [](auto controller) { controller->Render(); });
}

void ControllersManager::Set(std::shared_ptr<Controller> controller) {
    Clear();
    Push(controller);
}

void ControllersManager::Clear() { controllers_.clear(); }

}  // namespace zzmvc

}  // namespace cozz
