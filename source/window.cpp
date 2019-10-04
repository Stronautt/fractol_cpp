/*
 * This file is part of Fractol.

 * Fractol is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Fractol is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Fractol. If not, see <https://www.gnu.org/licenses/>.
 *
 * Author: Pavlo Hrytsenko
*/

#include "window.hpp"

#include "event/window_moved_event.hpp"
#include "event/window_resized_event.hpp"

namespace cozz {

Window::Window(uint64_t x, uint64_t y, uint64_t width, uint64_t height)
    : x_(x), y_(y), width_(width), height_(height) {}

Window::~Window() = default;

uint64_t Window::GetWidth() const { return width_; }

uint64_t Window::GetHeight() const { return height_; }

void Window::OnMove(const WindowMovedEvent& event) {
    auto new_position = event.GetPosition();
    x_ = new_position.first;
    y_ = new_position.second;
    Moved();
}

void Window::OnResize(const WindowResizedEvent& event) {
    auto new_size = event.GetSize();
    width_ = new_size.first;
    height_ = new_size.second;
    Resized();
}

}  // namespace cozz
