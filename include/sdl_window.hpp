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

#ifndef FRACTOL_INCLUDE_SDL_WINDOW_HPP_
#define FRACTOL_INCLUDE_SDL_WINDOW_HPP_

#include "window.hpp"

#include <cstdint>
#include <memory>
#include <string>
#include <functional>

extern "C" typedef struct SDL_Surface SDL_Surface;
extern "C" typedef struct SDL_Window SDL_Window;

namespace cozz {

class Canvas;

class SDLWindow final : public Window {
  public:
    SDLWindow(std::string title, uint32_t width, uint32_t height);
    SDLWindow(std::string title, uint32_t x, uint32_t y, uint32_t width, uint32_t height);

    virtual void Update() override;

    virtual Window::ID GetId() const override;

    virtual Canvas& GetCanvas() override;

  protected:
    virtual void Moved() override;

    virtual void Resized() override;

  private:
    std::unique_ptr<SDL_Window, std::function<void(SDL_Window*)>> window_;
    SDL_Surface* window_surface_;
    std::unique_ptr<Canvas> canvas_;

    std::unique_ptr<Canvas> CanvasFromSurface(const SDL_Surface* surface);
};

}  // namespace cozz

#endif  // FRACTOL_INCLUDE_SDL_WINDOW_HPP_
