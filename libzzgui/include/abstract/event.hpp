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

#ifndef LIBZZGUI_INCLUDE_INTERFACES_EVENT_HPP_
#define LIBZZGUI_INCLUDE_INTERFACES_EVENT_HPP_

#include <chrono>
#include <cstdint>
#include <stdexcept>

#include "window.hpp"

namespace cozz {

namespace zzgui {

class event_error : public std::runtime_error {
    using std::runtime_error::runtime_error;
};

class Event {
  public:
    enum class Type : uint8_t {
        kQuit = 0x0,
        kWindowClose,
        kWindowShown,
        kWindowExposed,
        kWindowHidden,
        kWindowMoved,
        kWindowResized,
        kWindowMinimized,
        kWindowMaximized,
        kWindowRestored,
        kWindowEnter,
        kWindowLeave,
        kWindowFocusGained,
        kWindowFocusLost,
        kWindowTakeFocus,
        kMouseMotion,
        kMouseButton,
        kMouseWheel,
        kKeyboard
    };

    virtual ~Event();

    virtual Type GetType() const final;

    virtual std::chrono::system_clock::time_point GetTimestamp() const final;

    virtual Window::ID GetWindowId() const final;

  protected:
    Event(Type type, Window::ID window_id);

    Type type_;
    std::chrono::system_clock::time_point timestamp_;
    Window::ID window_id_;
};

}  // namespace zzgui

}  // namespace cozz

#endif  // LIBZZGUI_INCLUDE_INTERFACES_EVENT_HPP_
