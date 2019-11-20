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

#ifndef LIBZZGUI_INCLUDE_INTERFACES_WIDGET_HPP_
#define LIBZZGUI_INCLUDE_INTERFACES_WIDGET_HPP_

#include <atomic>
#include <chrono>
#include <cstdint>
#include <functional>
#include <map>
#include <memory>
#include <tuple>
#include <utility>

#include "key_map.hpp"

namespace cozz {

namespace zzgui {

class Painter;
class Event;
class WindowLeaveEvent;
class MouseMotionEvent;
class MouseButtonEvent;

class Widget {
  public:
    virtual ~Widget();

    virtual void Draw(std::shared_ptr<Painter> painter) = 0;

    virtual void SetPosition(uint64_t x, uint64_t y);

    virtual void SetSize(uint64_t width, uint64_t height);

    void SetPadding(uint64_t padding);

    void SetPadding(uint64_t horizontal, uint64_t vertical);

    void SetPadding(uint64_t left, uint64_t right, uint64_t top, uint64_t bottom);

    std::pair<uint64_t, uint64_t> GetPosition() const;

    std::pair<uint64_t, uint64_t> GetSize() const;

    std::tuple<uint64_t, uint64_t, uint64_t, uint64_t> GetPadding() const;

    bool OnWindowLeave(const WindowLeaveEvent& event);

    bool OnMouseMotion(const MouseMotionEvent& event);

    bool OnMouseButton(const MouseButtonEvent& event);

    void OnClick(std::function<bool(const MouseButtonEvent&)> func);

    void PlaceRight(std::weak_ptr<Widget> widget, uint64_t offset_x = 0, uint64_t offset_y = 0);

    void PlaceLeft(std::weak_ptr<Widget> widget, uint64_t offset_x = 0, uint64_t offset_y = 0);

    void PlaceBottom(std::weak_ptr<Widget> widget, uint64_t offset_y = 0, uint64_t offset_x = 0);

    void PlaceUp(std::weak_ptr<Widget> widget, uint64_t offset_y = 0, uint64_t offset_x = 0);

  protected:
    uint64_t x_;
    uint64_t y_;

    uint64_t width_;
    uint64_t height_;

    uint64_t padding_left_;
    uint64_t padding_right_;
    uint64_t padding_top_;
    uint64_t padding_bottom_;

    std::map<KeyMap, const MouseButtonEvent> button_queue_;
    std::atomic<bool> hover_;

    std::function<bool(const MouseButtonEvent&)> click_callback_;

    Widget(uint64_t x, uint64_t y, uint64_t width, uint64_t height);

    virtual bool InBounds(uint64_t x, uint64_t y, const Event& event) = 0;

    virtual bool DoOnMouseButton(const MouseButtonEvent& event) = 0;
};

}  // namespace zzgui

}  // namespace cozz

#endif  // LIBZZGUI_INCLUDE_INTERFACES_WIDGET_HPP_
