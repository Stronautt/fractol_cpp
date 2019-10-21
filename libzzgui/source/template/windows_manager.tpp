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

#include "windows_manager.hpp"

namespace cozz {

namespace zzgui {

template <class WindowType>
std::weak_ptr<Window> WindowsManager::CreateWindow(std::string title, uint64_t width, uint64_t height) {
    return CreateWindow<WindowType>(title, 0, 0, width, height);
}

template <class WindowType>
std::weak_ptr<Window> WindowsManager::CreateWindow(std::string title, uint64_t x, uint64_t y, uint64_t width, uint64_t height) {
    auto window = std::make_shared<WindowType>(title, x, y, width, height);

    windows_.emplace(window->GetId(), std::make_pair(window, event_handler_->RegisterWindowEventCallbacks(*window)));

    return window;
}

}  // namespace zzgui

}  // namespace cozz
