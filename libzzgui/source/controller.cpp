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

#include "controllers_manager.hpp"
#include "model.hpp"
#include "view.hpp"

namespace cozz {

namespace zzgui {

Controller::Controller(std::shared_ptr<View> view) {
    if (!view) {
        throw std::runtime_error("Bad model or view");
    }
    SetModelAndView(view->GetModel().lock(), view);
}

Controller::~Controller() = default;

void Controller::Render(float delta) {
    model_->Update(delta);
    view_->Render(delta);
}

void Controller::Pause() { view_->Pause(); }

void Controller::Resume() { view_->Resume(); }

void Controller::Resize(uint64_t width, uint64_t height) { view_->Resize(width, height); }

void Controller::SetModelAndView(std::shared_ptr<Model> model, std::shared_ptr<View> view) {
    if (!model || !view) {
        throw std::runtime_error("Bad model or view");
    } else {
        model_ = model;
        view_ = view;
    }
}

void Controller::SetEventHandler(std::weak_ptr<EventHandler> event_handler) {
    if (event_handler.expired()) {
        throw std::runtime_error("Bad event handler");
    }
    event_handler_ = event_handler;
    model_->SetEventHandler(event_handler);
    view_->SetEventHandler(event_handler);
}

void Controller::SetWindowsManager(std::weak_ptr<WindowsManager> windows_manager) {
    if (windows_manager.expired()) {
        throw std::runtime_error("Bad event handler");
    }
    windows_manager_ = windows_manager;
    model_->SetWindowsManager(windows_manager);
    view_->SetWindowsManager(windows_manager);
}

void Controller::SetResourceManager(std::weak_ptr<ResourceManager> resource_manager) {
    if (resource_manager.expired()) {
        throw std::runtime_error("Bad event handler");
    }
    resource_manager_ = resource_manager;
    model_->SetResourceManager(resource_manager);
    view_->SetResourceManager(resource_manager);
}

std::weak_ptr<EventHandler> Controller::GetEventHandler() const { return event_handler_; }

std::weak_ptr<WindowsManager> Controller::GetWindowsManager() const { return windows_manager_; }

std::weak_ptr<ResourceManager> Controller::GetResourceManager() const { return resource_manager_; }

std::weak_ptr<Model> Controller::GetModel() const { return model_; }

std::weak_ptr<View> Controller::GetView() const { return view_; }

}  // namespace zzgui

}  // namespace cozz
