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

#include "widget.hpp"

#include "event/mouse_button_event.hpp"
#include "event/mouse_motion_event.hpp"
#include "event/window_event.hpp"

namespace cozz {

namespace zzgui {

Widget::Widget(int64_t x, int64_t y, int64_t width, int64_t height)
    : x_(x), y_(y), padding_left_(5), padding_right_(5), padding_top_(5), padding_bottom_(5) {
    SetSize(width, height);
}

Widget::~Widget() = default;

void Widget::SetPosition(int64_t x, int64_t y) {
    x_ = x;
    y_ = y;
}

void Widget::SetSize(int64_t width, int64_t height) {
    width_ = width + padding_left_ + padding_right_;
    height_ = height + padding_top_ + padding_bottom_;
}

void Widget::SetPadding(int64_t padding) { SetPadding(padding, padding); }

void Widget::SetPadding(int64_t horizontal, int64_t vertical) {
    SetPadding(horizontal, horizontal, vertical, vertical);
}

void Widget::SetPadding(int64_t left, int64_t right, int64_t top, int64_t bottom) {
    auto raw_width = width_ - padding_left_ - padding_right_;
    auto raw_height = height_ - padding_top_ - padding_bottom_;

    padding_left_ = left;
    padding_right_ = right;
    padding_top_ = top;
    padding_bottom_ = bottom;

    Widget::SetSize(raw_width, raw_height);
}

std::pair<int64_t, int64_t> Widget::GetPosition() const { return std::make_pair(x_, y_); }

std::pair<int64_t, int64_t> Widget::GetSize() const { return std::make_pair(width_, height_); }

std::tuple<int64_t, int64_t, int64_t, int64_t> Widget::GetPadding() const {
    return std::make_tuple(padding_left_, padding_right_, padding_top_, padding_bottom_);
}

bool Widget::OnWindowLeave(const WindowLeaveEvent& event) {
    for (const auto& button_pair : button_queue_) {
        const auto& mouse_button = button_pair.first;
        const auto& mouse_button_event = button_pair.second;
        const auto& mouse_position = mouse_button_event.GetPosition();

        if (event.GetWindowId() == mouse_button_event.GetWindowId() && mouse_button_event.IsPressed()) {
            DoOnMouseButton(MouseButtonEvent(mouse_button_event.GetWindowId(), mouse_button, false,
                                             mouse_button_event.GetClicksCount(), mouse_position.first,
                                             mouse_position.second));
        }
    }
    button_queue_.clear();
    return false;
}

bool Widget::OnMouseMotion(const MouseMotionEvent& event) {
    auto mouse_position = event.GetPosition();

    if (InBounds(mouse_position.first, mouse_position.second, event)) {
        hover_ = true;
    } else {
        hover_ = false;
    }
    return false;
}

bool Widget::OnMouseButton(const MouseButtonEvent& event) {
    const auto& button = event.GetButton();

    if (!event.IsPressed()) {
        if (!button_queue_.empty()) {
            DoOnMouseButton(event);
            button_queue_.erase(button);
            if (button == KeyMap::kLeftMouseButton && click_callback_) {
                return click_callback_(event);
            }
        }
    } else {
        const auto& mouse_position = event.GetPosition();

        if (InBounds(mouse_position.first, mouse_position.second, event) &&
            button_queue_.find(button) == button_queue_.end()) {
            button_queue_.emplace(button, event);
            return DoOnMouseButton(event);
        }
    }
    return false;
}

void Widget::OnClick(std::function<bool(const MouseButtonEvent&)> func) { click_callback_ = func; }

void Widget::PlaceRight(std::weak_ptr<Widget> widget, int64_t offset_x, int64_t offset_y) {
    if (!widget.expired()) {
        x_ = widget.lock()->x_ + widget.lock()->width_ + offset_x;
        y_ = widget.lock()->y_ + offset_y;
    }
}

void Widget::PlaceLeft(std::weak_ptr<Widget> widget, int64_t offset_x, int64_t offset_y) {
    if (!widget.expired()) {
        x_ = widget.lock()->x_ - width_ - offset_x;
        y_ = widget.lock()->y_ + offset_y;
    }
}

void Widget::PlaceBottom(std::weak_ptr<Widget> widget, int64_t offset_y, int64_t offset_x) {
    if (!widget.expired()) {
        x_ = widget.lock()->x_ + offset_x;
        y_ = widget.lock()->y_ + widget.lock()->height_ + offset_y;
    }
}

void Widget::PlaceUp(std::weak_ptr<Widget> widget, int64_t offset_y, int64_t offset_x) {
    if (!widget.expired()) {
        x_ = widget.lock()->x_ + offset_x;
        y_ = widget.lock()->y_ - height_ - offset_y;
    }
}

}  // namespace zzgui

}  // namespace cozz
