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

#include "controllers_manager.hpp"

#include <algorithm>
#include <chrono>

#include "controller.hpp"

namespace cozz {

namespace zzgui {

thread_local float ControllersManager::delta_time_ = 0;

float ControllersManager::GetDeltaTime() { return delta_time_; }

void ControllersManager::UpdateDeltaTime() {
    static thread_local auto tp = std::chrono::high_resolution_clock::now();

    delta_time_ = std::chrono::duration_cast<std::chrono::duration<float, std::ratio<1>>>(
                      std::chrono::high_resolution_clock::now() - tp)
                      .count();
}

void ControllersManager::Push(std::shared_ptr<Controller> controller) { controllers_.emplace_back(controller); }

void ControllersManager::Pop() { controllers_.pop_back(); }

void ControllersManager::Render() const {
    std::for_each(controllers_.begin(), controllers_.end(),
                  [](auto& controller) { controller->Render(GetDeltaTime()); });
    UpdateDeltaTime();
}

void ControllersManager::Set(std::shared_ptr<Controller> controller) {
    Clear();
    Push(controller);
}

void ControllersManager::Clear() { controllers_.clear(); }

}  // namespace zzgui

}  // namespace cozz
