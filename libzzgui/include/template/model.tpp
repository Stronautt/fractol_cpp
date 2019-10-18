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

template <class ControllerType>
Model<ControllerType>::~Model() = default;

template <class ControllerType>
void Model<ControllerType>::SetEventHandler(std::weak_ptr<EventHandler> event_handler) {
    if (event_handler.expired()) {
        throw std::runtime_error("Bad event handler");
    }
    event_handler_ = event_handler;
}

template <class ControllerType>
void Model<ControllerType>::SetWindowsManager(std::weak_ptr<WindowsManager> windows_manager) {
    if (windows_manager.expired()) {
        throw std::runtime_error("Bad windows manager");
    }
    windows_manager_ = windows_manager;
}

template <class ControllerType>
void Model<ControllerType>::SetResourceManager(std::weak_ptr<ResourceManager> resource_manager) {
    if (resource_manager.expired()) {
        throw std::runtime_error("Bad resource manager");
    }
    resource_manager_ = resource_manager;
}

template <class ControllerType>
void Model<ControllerType>::SetBaseController(std::weak_ptr<BaseController> controller) {
    SetController(std::static_pointer_cast<ControllerType>(controller.lock()));
}

template <class ControllerType>
void Model<ControllerType>::SetController(std::weak_ptr<ControllerType> controller) {
    if (controller.expired()) {
        throw std::runtime_error("Bad controller");
    }
    controller_ = controller;
}

template <class ControllerType>
std::weak_ptr<EventHandler> Model<ControllerType>::GetEventHandler() const {
    return event_handler_;
}

template <class ControllerType>
std::weak_ptr<WindowsManager> Model<ControllerType>::GetWindowsManager() const {
    return windows_manager_;
}

template <class ControllerType>
std::weak_ptr<ResourceManager> Model<ControllerType>::GetResourceManager() const {
    return resource_manager_;
}

template <class ControllerType>
std::weak_ptr<BaseController> Model<ControllerType>::GetBaseController() const {
    return GetController();
}

template <class ControllerType>
std::weak_ptr<ControllerType> Model<ControllerType>::GetController() const {
    return controller_;
}

}  // namespace zzgui

}  // namespace cozz
