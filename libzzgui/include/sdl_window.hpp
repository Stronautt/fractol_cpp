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

#ifndef LIBZZGUI_INCLUDE_SDL_WINDOW_HPP_
#define LIBZZGUI_INCLUDE_SDL_WINDOW_HPP_

#include "window.hpp"

#include <cstdint>
#include <functional>
#include <memory>
#include <string>

namespace cozz {

namespace zzgui {

class Canvas;

class SDLWindow final : public Window {
  public:
    SDLWindow(std::string title, uint32_t width, uint32_t height);
    SDLWindow(std::string title, uint32_t x, uint32_t y, uint32_t width, uint32_t height);

    virtual void Update() override;

    virtual void SetIcon(std::shared_ptr<ImageResource> icon) override;

    virtual void SetResizable(bool value) override;

    virtual void SetFullscreen(bool value) override;

    virtual void SetFullscreenDesktop(bool value) override;

    virtual Window::ID GetId() const override;

    virtual std::weak_ptr<Canvas> GetCanvas() override;

  protected:
    virtual void Moved() override;

    virtual void Resized() override;

  private:
    std::unique_ptr<void, std::function<void(void*)>> window_;
    void* window_surface_;
    std::shared_ptr<Canvas> canvas_;
};

}  // namespace zzgui

}  // namespace cozz

#endif  // LIBZZGUI_INCLUDE_SDL_WINDOW_HPP_
