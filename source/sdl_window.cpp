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
    : Window(title, x, y, width, height),
      window_(SDL_CreateWindow(title.c_str(), x, y, width, height, SDL_WINDOW_RESIZABLE), &SDL_DestroyWindow),
      window_surface_(SDL_GetWindowSurface(window_.get())),
      canvas_(CanvasFromSurface(window_surface_)) {}

void SDLWindow::Update() { SDL_UpdateWindowSurface(window_.get()); }

Window::ID SDLWindow::GetId() const { return SDL_GetWindowID(window_.get()); }

Canvas& SDLWindow::GetCanvas() { return *canvas_; }

void SDLWindow::Moved() {}

void SDLWindow::Resized() {
    window_surface_ = SDL_GetWindowSurface(window_.get());
    canvas_ = CanvasFromSurface(window_surface_);
}

std::unique_ptr<Canvas> SDLWindow::CanvasFromSurface(const SDL_Surface* surface) {
    return std::make_unique<Canvas>(
        surface->w, surface->h, static_cast<uint8_t*>(surface->pixels),
        Canvas::PixelFormat(surface->format->BitsPerPixel, surface->format->BytesPerPixel, surface->format->Rmask,
                            surface->format->Gmask, surface->format->Bmask, surface->format->Amask,
                            surface->format->Rloss, surface->format->Gloss, surface->format->Bloss,
                            surface->format->Aloss, surface->format->Rshift, surface->format->Gshift,
                            surface->format->Bshift, surface->format->Ashift));
}

}  // namespace cozz
