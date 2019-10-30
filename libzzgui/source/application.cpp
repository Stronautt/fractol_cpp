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

#include "application.hpp"

#include <chrono>

#include "event/quit_event.hpp"

namespace cozz {

namespace zzgui {

thread_local float Application::delta_time_ = 0;

Application::~Application() = default;

float Application::GetDeltaTime() { return delta_time_; }

void Application::UpdateDeltaTime() {
    static thread_local auto tp = std::chrono::high_resolution_clock::now();

    delta_time_ = std::chrono::duration_cast<std::chrono::duration<float, std::ratio<1>>>(
                      std::chrono::high_resolution_clock::now() - tp)
                      .count();
    tp = std::chrono::high_resolution_clock::now();
}

void Application::Terminate() { Terminate(QuitEvent()); }

}  // namespace zzgui

}  // namespace cozz
