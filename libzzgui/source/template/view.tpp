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

#include "view.hpp"

namespace cozz {

namespace zzgui {

template <class ModelType, class ControllerType>
View<ModelType, ControllerType>::View(std::weak_ptr<ModelType> model) : model_(model) {
    if (model_.expired()) {
        throw std::runtime_error("Bad model");
    }
}

template <class ModelType, class ControllerType>
View<ModelType, ControllerType>::~View() = default;

template <class ModelType, class ControllerType>
void View<ModelType, ControllerType>::SetEventHandler(std::weak_ptr<EventHandler> event_handler) {
    if (event_handler.expired()) {
        throw std::runtime_error("Bad event handler");
    }
    event_handler_ = event_handler;
}

template <class ModelType, class ControllerType>
void View<ModelType, ControllerType>::SetWindowsManager(std::weak_ptr<WindowsManager> windows_manager) {
    if (windows_manager.expired()) {
        throw std::runtime_error("Bad windows manager");
    }
    windows_manager_ = windows_manager;
}

template <class ModelType, class ControllerType>
void View<ModelType, ControllerType>::SetResourcesManager(std::weak_ptr<ResourcesManager> resources_manager) {
    if (resources_manager.expired()) {
        throw std::runtime_error("Bad resource manager");
    }
    resources_manager_ = resources_manager;
}

template <class ModelType, class ControllerType>
void View<ModelType, ControllerType>::SetBaseModel(std::weak_ptr<BaseModel> model) {
    SetModel(std::static_pointer_cast<ModelType>(model.lock()));
}


template <class ModelType, class ControllerType>
void View<ModelType, ControllerType>::SetBaseController(std::weak_ptr<BaseController> controller) {
    SetController(std::static_pointer_cast<ControllerType>(controller.lock()));
}

template <class ModelType, class ControllerType>
void View<ModelType, ControllerType>::SetModel(std::weak_ptr<ModelType> model) {
    if (model.expired()) {
        throw std::runtime_error("Bad model");
    }
    model_ = model;
}

template <class ModelType, class ControllerType>
void View<ModelType, ControllerType>::SetController(std::weak_ptr<ControllerType> controller) {
    if (controller.expired()) {
        throw std::runtime_error("Bad controller");
    }
    controller_ = controller;
}

template <class ModelType, class ControllerType>
std::weak_ptr<EventHandler> View<ModelType, ControllerType>::GetEventHandler() const {
    return event_handler_;
}

template <class ModelType, class ControllerType>
std::weak_ptr<WindowsManager> View<ModelType, ControllerType>::GetWindowsManager() const {
    return windows_manager_;
}

template <class ModelType, class ControllerType>
std::weak_ptr<ResourcesManager> View<ModelType, ControllerType>::GetResourcesManager() const {
    return resources_manager_;
}

template <class ModelType, class ControllerType>
std::weak_ptr<BaseModel> View<ModelType, ControllerType>::GetBaseModel() const {
    return GetModel();
}

template <class ModelType, class ControllerType>
std::weak_ptr<BaseController> View<ModelType, ControllerType>::GetBaseController() const {
    return GetController();
}

template <class ModelType, class ControllerType>
std::weak_ptr<ModelType> View<ModelType, ControllerType>::GetModel() const {
    return model_;
}

template <class ModelType, class ControllerType>
std::weak_ptr<ControllerType> View<ModelType, ControllerType>::GetController() const {
    return controller_;
}

}  // namespace zzgui

}  // namespace cozz
