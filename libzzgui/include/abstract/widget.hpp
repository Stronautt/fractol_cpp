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
class Canvas;
class Event;
class WindowLeaveEvent;
class MouseMotionEvent;
class MouseButtonEvent;

class Widget {
  public:
    virtual ~Widget();

    virtual void Draw(std::shared_ptr<Painter> painter, std::shared_ptr<Canvas> canvas) = 0;

    virtual void SetPosition(int64_t x, int64_t y);

    virtual void SetSize(int64_t width, int64_t height);

    void SetPadding(int64_t padding);

    void SetPadding(int64_t horizontal, int64_t vertical);

    void SetPadding(int64_t left, int64_t right, int64_t top, int64_t bottom);

    std::pair<int64_t, int64_t> GetPosition() const;

    std::pair<int64_t, int64_t> GetSize() const;

    std::tuple<int64_t, int64_t, int64_t, int64_t> GetPadding() const;

    bool OnWindowLeave(const WindowLeaveEvent& event);

    bool OnMouseMotion(const MouseMotionEvent& event);

    bool OnMouseButton(const MouseButtonEvent& event);

    void OnClick(std::function<bool(const MouseButtonEvent&)> func);

    void PlaceRight(std::weak_ptr<Widget> widget, int64_t offset_x = 0, int64_t offset_y = 0);

    void PlaceLeft(std::weak_ptr<Widget> widget, int64_t offset_x = 0, int64_t offset_y = 0);

    void PlaceBottom(std::weak_ptr<Widget> widget, int64_t offset_y = 0, int64_t offset_x = 0);

    void PlaceUp(std::weak_ptr<Widget> widget, int64_t offset_y = 0, int64_t offset_x = 0);

  protected:
    int64_t x_;
    int64_t y_;

    int64_t width_;
    int64_t height_;

    int64_t padding_left_;
    int64_t padding_right_;
    int64_t padding_top_;
    int64_t padding_bottom_;

    std::map<KeyMap, const MouseButtonEvent> button_queue_;
    std::atomic<bool> hover_;

    std::function<bool(const MouseButtonEvent&)> click_callback_;

    Widget(int64_t x, int64_t y, int64_t width, int64_t height);

    virtual bool InBounds(int64_t x, int64_t y, const Event& event) = 0;

    virtual bool DoOnMouseButton(const MouseButtonEvent& event) = 0;
};

}  // namespace zzgui

}  // namespace cozz

#endif  // LIBZZGUI_INCLUDE_INTERFACES_WIDGET_HPP_
