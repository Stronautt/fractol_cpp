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

Controller::Controller(std::weak_ptr<EventHandler> event_handler, std::weak_ptr<Model> model, std::weak_ptr<View> view)
    : event_handler_(event_handler) {
    if (event_handler_.expired()) {
        throw std::runtime_error("Bad event handler");
    }
    SetModelAndView(model, view);
}

Controller::~Controller() = default;

void Controller::Render(float delta) {
    if (!model_.expired()) {
        model_.lock()->Update(delta);
    }
    if (!view_.expired()) {
        view_.lock()->Render(delta);
    }
}

void Controller::Pause() {
    if (!view_.expired()) {
        view_.lock()->Pause();
    }
}

void Controller::Resume() {
    if (!view_.expired()) {
        view_.lock()->Resume();
    }
}

void Controller::Resize(uint64_t width, uint64_t height) {
    if (!view_.expired()) {
        view_.lock()->Resize(width, height);
    }
}

void Controller::SetModelAndView(std::weak_ptr<Model> model, std::weak_ptr<View> view) {
    if (model.expired() || view.expired()) {
        throw std::runtime_error("Bad model or view");
    } else {
        model_ = model;
        view_ = view;
    }
}

std::weak_ptr<EventHandler> Controller::GetEventHandler() const { return event_handler_; }

std::weak_ptr<Model> Controller::GetModel() const { return model_; }

std::weak_ptr<View> Controller::GetView() const { return view_; }

}  // namespace zzgui

}  // namespace cozz
