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

#include <stdexcept>

#include "painter.hpp"
#include "resources/font_resource.hpp"

namespace cozz {

namespace zzgui {

Label::Label(const std::string& text, std::shared_ptr<FontResource> font, uint64_t x, uint64_t y)
    : Widget(x, y, 0, 0),
      font_(font),
      autosize_(true),
      text_align_(TextAlign::kVerticalAndHorizontalCentered),
      border_thickness_(1),
      border_color_({0, 0, 0, 0}),
      background_color_({0, 0, 0, 0}),
      foreground_color_({0, 0, 0}) {
    if (!font_) {
        throw std::runtime_error("Bad font resource");
    }
    SetText(text);
}

void Label::Draw(std::shared_ptr<Painter> painter) {
    painter->DrawRect({x_, y_}, width_, height_, border_color_);
    painter->DrawFilledRect({x_ + border_thickness_, y_ + border_thickness_}, width_ - border_thickness_ * 2,
                            height_ - border_thickness_ * 2, background_color_);

    Canvas::Point pos;
    switch (text_align_) {
        case TextAlign::kLeftTop:
            pos = {x_ + padding_left_, y_ + padding_top_};
            break;
        case TextAlign::kLeftBottom:
            pos = {x_ + padding_left_, y_ + height_ - text_size_.second - padding_bottom_};
            break;
        case TextAlign::kRightTop:
            pos = {x_ + width_ - text_size_.first - padding_right_, y_ + padding_top_};
            break;
        case TextAlign::kRightBottom:
            pos = {x_ + width_ - text_size_.first - padding_right_, y_ + height_ - text_size_.second - padding_bottom_};
            break;
        case TextAlign::kLeftVerticalCentered:
            pos = {x_ + padding_left_, y_ + height_ / 2 - text_size_.second / 2};
            break;
        case TextAlign::kRightVerticalCentered:
            pos = {x_ + width_ - text_size_.first - padding_right_, y_ + height_ / 2 - text_size_.second / 2};
            break;
        case TextAlign::kTopHorizontalCentered:
            pos = {x_ + width_ / 2 - text_size_.first / 2, y_ + padding_top_};
            break;
        case TextAlign::kBottomHorizontalCentered:
            pos = {x_ + width_ / 2 - text_size_.first / 2, y_ + height_ - text_size_.second - padding_bottom_};
            break;
        case TextAlign::kVerticalAndHorizontalCentered:
            pos = {x_ + width_ / 2 - text_size_.first / 2, y_ + height_ / 2 - text_size_.second / 2};
            break;
        default:
            throw std::logic_error("Unknown text align type");
    }
    painter->DrawText({pos.x, pos.y}, text_, font_, foreground_color_);
}

void Label::SetSize(uint64_t width, uint64_t height) {
    if (!autosize_) {
        Widget::SetSize(width, height);
    }
}

void Label::SetText(const std::string& text) {
    text_ = text;
    text_size_ = font_->CalcTextSize(text_);
    if (autosize_) {
        Widget::SetSize(text_size_.first, text_size_.second);
    }
}

void Label::SetFont(std::shared_ptr<FontResource> font) { font_ = font; }

void Label::SetAutosize(bool value) { autosize_ = value; }

void Label::SetTextAlign(TextAlign text_align) { text_align_ = text_align; }

void Label::SetBorderThickness(uint16_t thickness) { border_thickness_ = thickness; }

void Label::SetBorderColor(const Canvas::PixelColor& border_color) { border_color_ = border_color; }

void Label::SetBackgroundColor(const Canvas::PixelColor& background_color) { background_color_ = background_color; }

void Label::SetForegroundColor(const Canvas::PixelColor& foreground_color) { foreground_color_ = foreground_color; }

const std::string& Label::GetText() const { return text_; }

std::shared_ptr<FontResource> Label::GetFont() const { return font_; }

Label::TextAlign Label::GetTextAlign() const { return text_align_; }

uint16_t Label::GetBorderThickness() const { return border_thickness_; }

const Canvas::PixelColor& Label::GetBorderColor() const { return border_color_; }

const Canvas::PixelColor& Label::GetBackgroundColor() const { return background_color_; }

const Canvas::PixelColor& Label::GetForegroundColor() const { return foreground_color_; }

bool Label::DoOnMouseButton(const MouseButtonEvent&) { return false; }

bool Label::InBounds(uint64_t x, uint64_t y, const Event&) {
    if (x >= x_ && x <= x_ + width_ && y >= y_ && y <= y_ + height_) {
        return true;
    }
    return false;
}

}  // namespace zzgui

}  // namespace cozz
