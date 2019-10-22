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

#include "widgets/label.hpp"

#include "painter.hpp"
#include "resources/font_resource.hpp"

namespace cozz {

namespace zzgui {

Label::Label(const std::string& text, std::shared_ptr<FontResource> font, uint64_t x, uint64_t y)
    : Widget(x, y, 0, 0),
      font_(font),
      border_thickness_(1),
      border_color_({0, 0, 0, 0}),
      background_color_({0, 0, 0, 0}),
      foreground_color_({0xFF, 0xFF, 0xFF}) {
    if (!font_) {
        throw std::runtime_error("Bad font resource");
    }
    SetText(text);
}

void Label::Draw(std::shared_ptr<Painter> painter) {
    painter->DrawRect({x_, y_}, width_, height_, border_color_);
    painter->DrawFilledRect({x_ + border_thickness_, y_ + border_thickness_}, width_ - border_thickness_ * 2,
                            height_ - border_thickness_ * 2, background_color_);
    painter->DrawText({x_ + padding_left_, y_ + padding_top_}, text_, font_, foreground_color_);
}

void Label::SetText(const std::string& text) {
    text_ = text;
    auto text_size = font_->CalcTextSize(text_);
    SetSize(text_size.first, text_size.second);
}

void Label::SetBorderThickness(uint16_t thickness) { border_thickness_ = thickness; }

void Label::SetBorderColor(const Canvas::PixelColor& border_color) { border_color_ = border_color; }

void Label::SetBackgroundColor(const Canvas::PixelColor& background_color) { background_color_ = background_color; }

void Label::SetForegroundColor(const Canvas::PixelColor& foreground_color) { foreground_color_ = foreground_color; }

const std::string& Label::GetText() const { return text_; }

void Label::SetFont(std::shared_ptr<FontResource> font) { font_ = font; }

std::shared_ptr<FontResource> Label::GetFont() const { return font_; }

uint16_t Label::GetBorderThickness() const { return border_thickness_; }

const Canvas::PixelColor& Label::GetBorderColor() const { return border_color_; }

const Canvas::PixelColor& Label::GetBackgroundColor() const { return background_color_; }

const Canvas::PixelColor& Label::GetForegroundColor() const { return foreground_color_; }

void Label::DoOnMouseButton(const MouseButtonEvent&) {}

}  // namespace zzgui

}  // namespace cozz
