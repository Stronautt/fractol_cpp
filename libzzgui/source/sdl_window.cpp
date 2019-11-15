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

#include "sdl_window.hpp"

#include <SDL2/SDL.h>

#include "canvas.hpp"
#include "resources/image_resource.hpp"
#include "sdl_utilities.hpp"

namespace cozz {

namespace zzgui {

SDLWindow::SDLWindow(std::string title, uint32_t width, uint32_t height)
    : SDLWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height) {
    if (!SDL_WasInit(SDL_INIT_VIDEO)) {
        SDL_Init(SDL_INIT_VIDEO);
    }
}

SDLWindow::SDLWindow(std::string title, uint32_t x, uint32_t y, uint32_t width, uint32_t height)
    : Window(title, !x ? SDL_WINDOWPOS_CENTERED : x, !y ? SDL_WINDOWPOS_CENTERED : y, width, height),
      window_(static_cast<void*>(SDL_CreateWindow(title.c_str(), x_, y_, width_, height_, 0)),
              reinterpret_cast<void (*)(void*)>(&SDL_DestroyWindow)),
      window_surface_(SDL_GetWindowSurface(static_cast<SDL_Window*>(window_.get()))),
      canvas_(sdl2::CanvasFromSurface(static_cast<SDL_Surface*>(window_surface_))) {}

void SDLWindow::Update() { SDL_UpdateWindowSurface(static_cast<SDL_Window*>(window_.get())); }

void SDLWindow::SetIcon(std::shared_ptr<ImageResource> icon) {
    SDL_SetWindowIcon(static_cast<SDL_Window*>(window_.get()), static_cast<SDL_Surface*>(icon->GetImgData().get()));
}

void SDLWindow::SetResizable(bool value) {
    SDL_SetWindowResizable(static_cast<SDL_Window*>(window_.get()), static_cast<SDL_bool>(value));
}

void SDLWindow::SetFullscreen(bool value) {
    SDL_SetWindowFullscreen(static_cast<SDL_Window*>(window_.get()), value ? SDL_WINDOW_FULLSCREEN : 0);
}

void SDLWindow::SetFullscreenDesktop(bool value) {
    SDL_SetWindowFullscreen(static_cast<SDL_Window*>(window_.get()), value ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0);
}

Window::ID SDLWindow::GetId() const { return SDL_GetWindowID(static_cast<SDL_Window*>(window_.get())); }

std::weak_ptr<Canvas> SDLWindow::GetCanvas() { return canvas_; }

bool SDLWindow::GetFullscreen() const {
    return SDL_GetWindowFlags(static_cast<SDL_Window*>(window_.get())) & SDL_WINDOW_FULLSCREEN;
}

bool SDLWindow::GetFullscreenDesktop() const {
    return SDL_GetWindowFlags(static_cast<SDL_Window*>(window_.get())) & SDL_WINDOW_FULLSCREEN_DESKTOP;
}

void SDLWindow::Moved() {}

void SDLWindow::Resized() {
    window_surface_ = SDL_GetWindowSurface(static_cast<SDL_Window*>(window_.get()));
    canvas_ = sdl2::CanvasFromSurface(static_cast<SDL_Surface*>(window_surface_));
}

}  // namespace zzgui

}  // namespace cozz
