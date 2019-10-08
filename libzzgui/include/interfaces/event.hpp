/*
 * This file is part of LibZZgraph.

 * LibZZgraph is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * LibZZgraph is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with LibZZgraph. If not, see <https://www.gnu.org/licenses/>.
 *
 * Author: Pavlo Hrytsenko
*/

#ifndef LIBZZGRAPH_INCLUDE_INTERFACES_EVENT_HPP_
#define LIBZZGRAPH_INCLUDE_INTERFACES_EVENT_HPP_

#include <chrono>
#include <cstdint>
#include <stdexcept>

namespace cozz {

class event_error : public std::runtime_error {
    using std::runtime_error::runtime_error;
};

class Event {
  public:
    enum class Type : uint8_t {
        kWindowShown = 0x0,
        kWindowHidden,
        kWindowExposed,
        kWindowMoved,
        kWindowResized,
        kWindowMinimized,
        kWindowMaximized,
        kWindowRestored,
        kWindowEnter,
        kWindowLeave,
        kWindowFocusGained,
        kWindowFocusLost,
        kWindowClose,
        kWindowTakeFocus,
        kKeyboard,
        kMouseMotion,
        kMouseButton,
        kMouseWheel,
        kQuit,
    };

    virtual ~Event();

    virtual Type GetType() const final;

    virtual std::chrono::system_clock::time_point GetTimestamp() const final;

    virtual uint32_t GetWindowId() const final;

  protected:
    Event(Type type, uint32_t window_id);

    Type type_;
    std::chrono::system_clock::time_point timestamp_;
    uint32_t window_id_;
};

}  // namespace cozz

#endif  // LIBZZGRAPH_INCLUDE_INTERFACES_EVENT_HPP_
