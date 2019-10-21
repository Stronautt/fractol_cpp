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
#include <list>
#include <memory>
#include <tuple>
#include <utility>

#include "key_map.hpp"

namespace cozz {

namespace zzgui {

class Painter;
class MouseMotionEvent;
class MouseButtonEvent;

class Widget {
  public:
    virtual ~Widget();

    virtual void Draw(std::shared_ptr<Painter> painter) = 0;

    void SetPosition(uint64_t x, uint64_t y);

    void SetSize(uint64_t width, uint64_t height);

    void SetPadding(uint64_t left, uint64_t right, uint64_t top, uint64_t bottom);

    std::pair<uint64_t, uint64_t> GetPosition() const;

    std::pair<uint64_t, uint64_t> GetSize() const;

    std::tuple<uint64_t, uint64_t, uint64_t, uint64_t> GetPadding() const;

    void OnMouseMotion(const MouseMotionEvent& event);

    void OnMouseButton(const MouseButtonEvent& event);

    void OnClick(std::function<void(const MouseButtonEvent&)> func);

  protected:
    uint64_t x_;
    uint64_t y_;

    uint64_t width_;
    uint64_t height_;

    uint64_t padding_left_;
    uint64_t padding_right_;
    uint64_t padding_top_;
    uint64_t padding_bottom_;

    std::list<KeyMap> button_queue_;
    std::atomic<bool> hover_;

    std::function<void(const MouseButtonEvent&)> click_callback_;

    Widget(uint64_t x, uint64_t y, uint64_t width, uint64_t height);

    bool InBounds(uint64_t x, uint64_t y);

    virtual void DoOnMouseButton(const MouseButtonEvent& event) = 0;
};

}  // namespace zzgui

}  // namespace cozz

#endif  // LIBZZGUI_INCLUDE_INTERFACES_WIDGET_HPP_
