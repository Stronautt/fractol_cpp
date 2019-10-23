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

#include "controller.hpp"

#include "event/window_resized_event.hpp"
#include "window.hpp"

namespace cozz {

namespace zzgui {

template <class ModelType, class ViewType>
Controller<ModelType, ViewType>::Controller(std::shared_ptr<ViewType> view) {
    if (!view) {
        throw std::runtime_error("Bad view");
    }
    SetModel(view->GetModel().lock());
    SetView(view);
}

template <class ModelType, class ViewType>
Controller<ModelType, ViewType>::~Controller() {
    event_handler_.lock()->UnregisterEventCallbacks(registered_event_callbacks_);
}

template <class ModelType, class ViewType>
void Controller<ModelType, ViewType>::Render(float delta) {
    model_->Update(delta);
    view_->Render(delta);
}

template <class ModelType, class ViewType>
void Controller<ModelType, ViewType>::Pause() {
    view_->Pause();
}

template <class ModelType, class ViewType>
void Controller<ModelType, ViewType>::Resume() {
    view_->Resume();
}

template <class ModelType, class ViewType>
void Controller<ModelType, ViewType>::Resized(std::weak_ptr<Window> window) {
    view_->Resized(window);
}

template <class ModelType, class ViewType>
void Controller<ModelType, ViewType>::SetControllersManager(std::weak_ptr<ControllersManager> controllers_manager) {
    if (controllers_manager.expired()) {
        throw std::runtime_error("Bad controllers manager");
    }
    controllers_manager_ = controllers_manager;
}

template <class ModelType, class ViewType>
void Controller<ModelType, ViewType>::SetEventHandler(std::weak_ptr<EventHandler> event_handler) {
    if (event_handler.expired()) {
        throw std::runtime_error("Bad event handler");
    }
    event_handler_ = event_handler;
    model_->SetEventHandler(event_handler);
    view_->SetEventHandler(event_handler);
    registered_event_callbacks_.emplace_back(event_handler_.lock()->template RegisterEventCallback<WindowResizedEvent>(
        std::bind(&Controller<ModelType, ViewType>::OnWindowResize, this, std::placeholders::_1)));
}

template <class ModelType, class ViewType>
void Controller<ModelType, ViewType>::SetWindowsManager(std::weak_ptr<WindowsManager> windows_manager) {
    if (windows_manager.expired()) {
        throw std::runtime_error("Bad windows manager");
    }
    windows_manager_ = windows_manager;
    model_->SetWindowsManager(windows_manager);
    view_->SetWindowsManager(windows_manager);
}

template <class ModelType, class ViewType>
void Controller<ModelType, ViewType>::SetResourcesManager(std::weak_ptr<ResourcesManager> resources_manager) {
    if (resources_manager.expired()) {
        throw std::runtime_error("Bad resource manager");
    }
    resources_manager_ = resources_manager;
    model_->SetResourcesManager(resources_manager);
    view_->SetResourcesManager(resources_manager);
}

template <class ModelType, class ViewType>
void Controller<ModelType, ViewType>::SetBaseModel(std::shared_ptr<BaseModel> model) {
    SetModel(std::static_pointer_cast<ModelType>(model));
}

template <class ModelType, class ViewType>
void Controller<ModelType, ViewType>::SetBaseView(std::shared_ptr<BaseView> view) {
    SetView(std::static_pointer_cast<ViewType>(view));
}

template <class ModelType, class ViewType>
void Controller<ModelType, ViewType>::SetModel(std::shared_ptr<ModelType> model) {
    if (!model) {
        throw std::runtime_error("Bad model");
    }
    model_ = model;
}

template <class ModelType, class ViewType>
void Controller<ModelType, ViewType>::SetView(std::shared_ptr<ViewType> view) {
    if (!view) {
        throw std::runtime_error("Bad view");
    }
    view_ = view;
}

template <class ModelType, class ViewType>
std::weak_ptr<ControllersManager> Controller<ModelType, ViewType>::GetControllersManager() const {
    return controllers_manager_;
}

template <class ModelType, class ViewType>
std::weak_ptr<EventHandler> Controller<ModelType, ViewType>::GetEventHandler() const {
    return event_handler_;
}

template <class ModelType, class ViewType>
std::weak_ptr<WindowsManager> Controller<ModelType, ViewType>::GetWindowsManager() const {
    return windows_manager_;
}

template <class ModelType, class ViewType>
std::weak_ptr<ResourcesManager> Controller<ModelType, ViewType>::GetResourcesManager() const {
    return resources_manager_;
}

template <class ModelType, class ViewType>
std::weak_ptr<BaseModel> Controller<ModelType, ViewType>::GetBaseModel() const {
    return GetModel();
}

template <class ModelType, class ViewType>
std::weak_ptr<BaseView> Controller<ModelType, ViewType>::GetBaseView() const {
    return GetView();
}

template <class ModelType, class ViewType>
std::weak_ptr<ModelType> Controller<ModelType, ViewType>::GetModel() const {
    return model_;
}

template <class ModelType, class ViewType>
std::weak_ptr<ViewType> Controller<ModelType, ViewType>::GetView() const {
    return view_;
}

template <class ModelType, class ViewType>
void Controller<ModelType, ViewType>::RegisterWindow(std::weak_ptr<Window> window) {
    registered_windows_.emplace_back(window);
}

template <class ModelType, class ViewType>
void Controller<ModelType, ViewType>::OnWindowResize(const WindowResizedEvent& event) {
    for (const auto& window : registered_windows_) {
        if (!window.expired()) {
            if (window.lock()->GetId() == event.GetWindowId()) {
                Resized(window);
            }
        }
    }
}

}  // namespace zzgui

}  // namespace cozz
