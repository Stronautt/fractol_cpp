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

#include "window.hpp"

#include "event/window_event.hpp"
#include "event/window_moved_event.hpp"
#include "event/window_resized_event.hpp"
#include "event_handler.hpp"

namespace cozz {

namespace zzgui {

Window::Window(std::string title, uint64_t x, uint64_t y, uint64_t width, uint64_t height)
    : title_(title), x_(x), y_(y), width_(width), height_(height) {}

Window::~Window() = default;

std::string Window::GetTitle() const { return title_; }

std::pair<int64_t, int64_t> Window::GetPosition() const { return std::make_pair(x_, y_); }

uint64_t Window::GetWidth() const { return width_; }

uint64_t Window::GetHeight() const { return height_; }

void Window::Close(std::shared_ptr<EventHandler> event_handler) { event_handler->PushEvent(WindowCloseEvent(GetId())); }

void Window::OnClose(const WindowCloseEvent& event) {
    if (event.GetWindowId() == GetId()) {
        if (on_close_callback_) {
            on_close_callback_(event);
        }
    }
}

void Window::IfClosed(std::function<void(const WindowCloseEvent&)> callback) { on_close_callback_ = callback; }

void Window::OnMove(const WindowMovedEvent& event) {
    if (event.GetWindowId() == GetId()) {
        auto new_position = event.GetPosition();
        x_ = new_position.first;
        y_ = new_position.second;
        Moved();
    }
}

void Window::OnResize(const WindowResizedEvent& event) {
    if (event.GetWindowId() == GetId()) {
        auto new_size = event.GetSize();
        width_ = new_size.first;
        height_ = new_size.second;
        Resized();
    }
}

}  // namespace zzgui

}  // namespace cozz
