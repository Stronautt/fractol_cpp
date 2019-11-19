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

#include "widgets/select.hpp"

#include <stdexcept>

#include "event/mouse_button_event.hpp"
#include "painter.hpp"
#include "resources/font_resource.hpp"

namespace cozz {

namespace zzgui {

template <class Data>
Select<Data>::Select(const std::vector<std::pair<std::string, Data>>& options, std::shared_ptr<FontResource> font,
                     uint64_t x, uint64_t y)
    : Widget(x, y, 0, 0),
      font_(font),
      autosize_(true),
      focus_(false),
      border_thickness_(1),
      border_color_({0xC0, 0xC0, 0xC0}),
      background_color_({0, 0, 0, 0}),
      foreground_color_({0, 0, 0}) {
    if (!font_) {
        throw std::runtime_error("Bad font resource");
    }
    SetOptions(options);
}

template <class Data>
void Select<Data>::Draw(std::shared_ptr<Painter> painter) {
    const uint64_t options_size = options_.size();

    uint64_t rect_height = focus_ ? height_ * options_size : height_;
    painter->DrawRect({x_, y_}, width_, rect_height, border_color_);
    painter->DrawFilledRect({x_ + border_thickness_, y_ + border_thickness_}, width_ - border_thickness_ * 2,
                            rect_height - border_thickness_ * 2, background_color_);

    uint64_t it = 0;
    for (const auto& option : options_) {
        painter->DrawText(
            {x_ + padding_left_, y_ + height_ * (it + 1) - options_text_size_[it].second - padding_bottom_},
            option.first, font_, foreground_color_);
        if (!focus_) {
            break;
        }
        if (it < options_size - 1) {
            painter->DrawLine({x_, y_ + height_ * (it + 1)}, {x_ + width_, y_ + height_ * (it + 1)}, border_color_);
        }
        ++it;
    }
}

template <class Data>
void Select<Data>::SetSize(uint64_t width, uint64_t height) {
    if (!autosize_) {
        Widget::SetSize(width, height);
    }
}

template <class Data>
void Select<Data>::SetOptions(const std::vector<std::pair<std::string, Data>>& options) {
    options_ = options;
    uint64_t max_width = 0;
    uint64_t max_height = 0;
    for (const auto& option : options_) {
        options_text_size_.push_back(font_->CalcTextSize(option.first));
        if (options_text_size_.back().first > max_width) {
            max_width = options_text_size_.back().first;
        }
        if (options_text_size_.back().second > max_height) {
            max_height = options_text_size_.back().second;
        }
    }
    if (autosize_) {
        Widget::SetSize(max_width, max_height);
    }
}

template <class Data>
void Select<Data>::SetFont(std::shared_ptr<FontResource> font) {
    font_ = font;
}

template <class Data>
void Select<Data>::SetAutosize(bool value) {
    autosize_ = value;
}

template <class Data>
void Select<Data>::SetBorderThickness(uint16_t thickness) {
    border_thickness_ = thickness;
}

template <class Data>
void Select<Data>::SetBorderColor(const Canvas::PixelColor& border_color) {
    border_color_ = border_color;
}

template <class Data>
void Select<Data>::SetBackgroundColor(const Canvas::PixelColor& background_color) {
    background_color_ = background_color;
}

template <class Data>
void Select<Data>::SetForegroundColor(const Canvas::PixelColor& foreground_color) {
    foreground_color_ = foreground_color;
}

template <class Data>
const std::vector<std::pair<std::string, Data>>& Select<Data>::GetOptions() const {
    return options_;
}

template <class Data>
std::shared_ptr<FontResource> Select<Data>::GetFont() const {
    return font_;
}

template <class Data>
uint16_t Select<Data>::GetBorderThickness() const {
    return border_thickness_;
}

template <class Data>
const Canvas::PixelColor& Select<Data>::GetBorderColor() const {
    return border_color_;
}

template <class Data>
const Canvas::PixelColor& Select<Data>::GetBackgroundColor() const {
    return background_color_;
}

template <class Data>
const Canvas::PixelColor& Select<Data>::GetForegroundColor() const {
    return foreground_color_;
}

template <class Data>
void Select<Data>::OnChange(std::function<void(const Data&)> func) {
    change_callback_ = func;
}

template <class Data>
bool Select<Data>::DoOnMouseButton(const MouseButtonEvent& event) {
    if (event.GetButton() == KeyMap::kLeftMouseButton) {
        if (event.IsPressed()) {
            y_ += 2;

            if (focus_ && change_callback_) {
                const auto& mouse_pos = event.GetPosition();
                const uint64_t options_size = options_.size();

                uint64_t count = (mouse_pos.second - y_) / height_;
                if (count > options_size - 1) {
                    count = options_size - 1;
                }
                change_callback_(options_[count].second);
                std::swap(options_[0], options_[count]);
            }
        } else {
            y_ -= 2;
            focus_ ^= true;
        }
    }
    return true;
}

template <class Data>
bool Select<Data>::InBounds(uint64_t x, uint64_t y, const Event& event) {
    uint64_t rect_height = focus_ ? height_ * options_.size() : height_;
    if (x >= x_ && x <= x_ + width_ && y >= y_ && y <= y_ + rect_height) {
        return true;
    }
    if (dynamic_cast<const MouseButtonEvent*>(&event)) {
        focus_ = false;
    }
    return false;
}

}  // namespace zzgui

}  // namespace cozz
