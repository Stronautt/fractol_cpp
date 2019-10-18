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

#include "font_resource.hpp"
#include "painter.hpp"

namespace cozz {

namespace zzgui {

Label::Label(const std::string& text, std::shared_ptr<FontResource> font, uint64_t x, uint64_t y)
    : Widget(x, y, 0, 0), text_(text), font_(font) {}

void Label::Draw(std::shared_ptr<Painter> painter) { painter->DrawText({x_, y_}, text_, font_); }

void Label::SetText(const std::string& text) { text_ = text; }

const std::string& Label::GetText() const { return text_; }

void Label::SetFont(std::shared_ptr<FontResource> font) { font_ = font; }

std::shared_ptr<FontResource> Label::GetFont() const { return font_; }

}  // namespace zzgui

}  // namespace cozz
