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

Model::~Model() = default;

void Model::SetEventHandler(std::weak_ptr<EventHandler> event_handler) {
    if (event_handler.expired()) {
        throw std::runtime_error("Bad event handler");
    }
    event_handler_ = event_handler;
}

void Model::SetWindowsManager(std::weak_ptr<WindowsManager> windows_manager) {
    if (windows_manager.expired()) {
        throw std::runtime_error("Bad event handler");
    }
    windows_manager_ = windows_manager;
}

void Model::SetResourceManager(std::weak_ptr<ResourceManager> resource_manager) {
    if (resource_manager.expired()) {
        throw std::runtime_error("Bad event handler");
    }
    resource_manager_ = resource_manager;
}

void Model::SetController(std::weak_ptr<Controller> controller) {
    if (controller.expired()) {
        throw std::runtime_error("Bad event handler");
    }
    controller_ = controller;
}

std::weak_ptr<EventHandler> Model::GetEventHandler() const { return event_handler_; }

std::weak_ptr<WindowsManager> Model::GetWindowsManager() const { return windows_manager_; }

std::weak_ptr<ResourceManager> Model::GetResourceManager() const { return resource_manager_; }

std::weak_ptr<Controller> Model::GetController() const { return controller_; }

}  // namespace zzgui

}  // namespace cozz
