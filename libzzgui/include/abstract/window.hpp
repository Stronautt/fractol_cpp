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

#ifndef LIBZZGUI_INCLUDE_INTERFACES_WINDOW_HPP_
#define LIBZZGUI_INCLUDE_INTERFACES_WINDOW_HPP_

#include <cstdint>
#include <functional>
#include <limits>
#include <memory>
#include <string>
#include <utility>

namespace cozz {

namespace zzgui {

class ImageResource;
class Canvas;
class EventHandler;
class WindowCloseEvent;
class WindowMovedEvent;
class WindowResizedEvent;

class Window {
  public:
    enum ID : uint32_t {
        kUnknown = std::numeric_limits<uint32_t>::max(),
    };

    virtual ~Window();

    virtual void Update() = 0;

    virtual void SetIcon(std::shared_ptr<ImageResource> icon) = 0;

    virtual void SetResizable(bool value) = 0;

    virtual void SetFullscreen(bool value) = 0;

    virtual void SetFullscreenDesktop(bool value) = 0;

    virtual ID GetId() const = 0;

    virtual std::weak_ptr<Canvas> GetCanvas() = 0;

    std::string GetTitle() const;

    std::pair<int64_t, int64_t> GetPosition() const;

    uint64_t GetWidth() const;

    uint64_t GetHeight() const;

    virtual bool GetFullscreen() const = 0;

    virtual bool GetFullscreenDesktop() const = 0;

    void Close(std::shared_ptr<EventHandler> event_handler);

    bool OnClose(const WindowCloseEvent& event);

    void IfClosed(std::function<void(const WindowCloseEvent&)> callback);

    bool OnMove(const WindowMovedEvent& event);

    bool OnResize(const WindowResizedEvent& event);

    void IfResized(std::function<void(const WindowResizedEvent&)> callback);

  protected:
    std::string title_;

    uint64_t x_;
    uint64_t y_;

    uint64_t width_;
    uint64_t height_;

    std::function<void(const WindowCloseEvent&)> on_close_callback_;
    std::function<void(const WindowResizedEvent&)> on_resize_callback_;

    Window(std::string title, uint64_t x, uint64_t y, uint64_t width, uint64_t height);

    virtual void Moved() = 0;

    virtual void Resized() = 0;
};

}  // namespace zzgui

}  // namespace cozz

#endif  // LIBZZGUI_INCLUDE_INTERFACES_WINDOW_HPP_
