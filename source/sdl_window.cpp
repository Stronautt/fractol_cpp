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

#include "sdl_window.hpp"

#include <SDL2/SDL.h>

#include "canvas.hpp"

namespace cozz {

SDLWindow::SDLWindow(std::string title, uint32_t width, uint32_t height)
    : SDLWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height) {}

SDLWindow::SDLWindow(std::string title, uint32_t x, uint32_t y, uint32_t width, uint32_t height)
    : Window(x, y, width, height),
      window_(SDL_CreateWindow(title.c_str(), x, y, width, height, 0), &SDL_DestroyWindow),
      window_surface_(SDL_GetWindowSurface(window_.get())),
      canvas_(std::make_unique<Canvas>(width, height, static_cast<uint8_t*>(window_surface_->pixels),
                                       window_surface_->format->BytesPerPixel)) {}

void SDLWindow::Update() { SDL_UpdateWindowSurface(window_.get()); }

uint32_t SDLWindow::GetID() const { return SDL_GetWindowID(window_.get()); }

void SDLWindow::Resize() {}

Canvas& SDLWindow::GetCanvas() { return *canvas_; }

}  // namespace cozz
