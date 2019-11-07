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

Select::Select(const std::vector<std::string>& options, std::shared_ptr<FontResource> font, uint64_t x, uint64_t y)
    : Widget(x, y, 0, 0),
      font_(font),
      autosize_(true),
      focus_(false),
      border_thickness_(1),
      border_color_({0xC1, 0xC1, 0xC1, 0xC1}),
      background_color_({0, 0, 0, 0}),
      foreground_color_({0xFF, 0xFF, 0xFF}) {
    if (!font_) {
        throw std::runtime_error("Bad font resource");
    }
    SetOptions(options);
}

void Select::Draw(std::shared_ptr<Painter> painter) {
    uint64_t rect_height = focus_ ? height_ * options_.size() : height_;
    painter->DrawRect({x_, y_}, width_, rect_height, border_color_);
    painter->DrawFilledRect({x_ + border_thickness_, y_ + border_thickness_}, width_ - border_thickness_ * 2,
                            rect_height - border_thickness_ * 2, background_color_);

    uint64_t options_size = options_.size();
    for (uint64_t it = 0; it < options_size; ++it) {
        painter->DrawText(
            {x_ + padding_left_, y_ + height_ * (it + 1) - options_text_size_[it].second - padding_bottom_},
            options_[it], font_, foreground_color_);
        if (!focus_) {
            break;
        }
        if (it < options_size - 1) {
            painter->DrawLine({x_, y_ + height_ * (it + 1)}, {x_ + width_, y_ + height_ * (it + 1)}, border_color_);
        }
    }
}

void Select::SetSize(uint64_t width, uint64_t height) {
    if (!autosize_) {
        Widget::SetSize(width, height);
    }
}

void Select::SetOptions(const std::vector<std::string>& options) {
    options_ = options;
    uint64_t max_width = 0;
    uint64_t max_height = 0;
    for (const auto& option : options_) {
        options_text_size_.push_back(font_->CalcTextSize(option));
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

void Select::SetFont(std::shared_ptr<FontResource> font) { font_ = font; }

void Select::SetAutosize(bool value) { autosize_ = value; }

void Select::SetBorderThickness(uint16_t thickness) { border_thickness_ = thickness; }

void Select::SetBorderColor(const Canvas::PixelColor& border_color) { border_color_ = border_color; }

void Select::SetBackgroundColor(const Canvas::PixelColor& background_color) { background_color_ = background_color; }

void Select::SetForegroundColor(const Canvas::PixelColor& foreground_color) { foreground_color_ = foreground_color; }

const std::vector<std::string>& Select::GetOptions() const { return options_; }

std::shared_ptr<FontResource> Select::GetFont() const { return font_; }

uint16_t Select::GetBorderThickness() const { return border_thickness_; }

const Canvas::PixelColor& Select::GetBorderColor() const { return border_color_; }

const Canvas::PixelColor& Select::GetBackgroundColor() const { return background_color_; }

const Canvas::PixelColor& Select::GetForegroundColor() const { return foreground_color_; }

void Select::DoOnMouseButton(const MouseButtonEvent& event) {
    if (!event.IsPressed()) {
        focus_ = true;
    }
}

bool Select::InBounds(uint64_t x, uint64_t y, const Event& event) {
    if (x >= x_ && x <= x_ + width_ && y >= y_ && y <= y_ + height_) {
        return true;
    }
    if (dynamic_cast<const MouseButtonEvent*>(&event)) {
        focus_ = false;
    }
    return false;
}

}  // namespace zzgui

}  // namespace cozz
