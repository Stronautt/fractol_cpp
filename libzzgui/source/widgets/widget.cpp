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

namespace cozz {

namespace zzgui {

Widget::Widget(uint64_t x, uint64_t y, uint64_t width, uint64_t height)
    : x_(x), y_(y), width_(width), height_(height) {}

Widget::~Widget() = default;

std::pair<uint64_t, uint64_t> Widget::GetPosition() const { return std::make_pair(x_, y_); }

std::pair<uint64_t, uint64_t> Widget::GetSize() const { return std::make_pair(width_, height_); }

void Widget::SetPosition(uint64_t x, uint64_t y) {
    x_ = x;
    y_ = y;
}

void Widget::SetSize(uint64_t width, uint64_t height) {
    width_ = width;
    height_ = height;
}

}  // namespace zzgui

}  // namespace cozz
