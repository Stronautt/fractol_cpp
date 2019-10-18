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
#include <iostream>

#include "application.hpp"
#include "base_controller.hpp"
#include "base_model.hpp"
#include "base_view.hpp"

namespace cozz {

namespace zzgui {

ControllersManager::ControllersManager(std::weak_ptr<EventHandler> event_handler_,
                                       std::weak_ptr<WindowsManager> windows_manager_,
                                       std::weak_ptr<ResourceManager> resource_manager_)
    : event_handler_(event_handler_), windows_manager_(windows_manager_), resource_manager_(resource_manager_) {
    if (event_handler_.expired() || windows_manager_.expired() || resource_manager_.expired()) {
        throw std::logic_error("Bad event handler, windows manager or resource manager");
    }
}

void ControllersManager::Push(std::shared_ptr<BaseController> controller) {
    auto model = controller->GetBaseModel().lock();
    auto view = controller->GetBaseView().lock();
    controller->SetEventHandler(event_handler_);
    controller->SetWindowsManager(windows_manager_);
    controller->SetResourceManager(resource_manager_);
    model->SetBaseController(controller);
    view->SetBaseController(controller);
    controller->Create();
    model->Create();
    view->Create();
    controllers_.emplace_back(controller);
}

void ControllersManager::Pop() { controllers_.pop_back(); }

void ControllersManager::Render() const {
    std::for_each(controllers_.begin(), controllers_.end(),
                  [](auto& controller) { controller->Render(Application::GetDeltaTime()); });
}

void ControllersManager::Set(std::shared_ptr<BaseController> controller) {
    Clear();
    Push(controller);
}

void ControllersManager::Clear() { controllers_.clear(); }

std::weak_ptr<EventHandler> ControllersManager::GetEventHandler() const { return event_handler_; }

std::weak_ptr<WindowsManager> ControllersManager::GetWindowsManager() const { return windows_manager_; }

std::weak_ptr<ResourceManager> ControllersManager::GetResourceManager() const { return resource_manager_; }

}  // namespace zzgui

}  // namespace cozz
