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

#include "sdl_utilities.hpp"

#include <SDL2/SDL.h>

#include "canvas.hpp"

namespace cozz {

namespace zzgui {

namespace sdl2 {

std::shared_ptr<Canvas> CanvasFromSurface(const SDL_Surface* surface) {
    if (!surface) {
        return nullptr;
    }
    return std::make_shared<Canvas>(
        surface->w, surface->h, static_cast<uint8_t*>(surface->pixels),
        Canvas::PixelFormat(surface->format->BitsPerPixel, surface->format->BytesPerPixel, surface->format->Rmask,
                            surface->format->Gmask, surface->format->Bmask, surface->format->Amask,
                            surface->format->Rloss, surface->format->Gloss, surface->format->Bloss,
                            surface->format->Aloss, surface->format->Rshift, surface->format->Gshift,
                            surface->format->Bshift, surface->format->Ashift));
}

SDL_Surface* SurfaceFromCanvas(std::shared_ptr<Canvas> canvas) {
    if (!canvas) {
        return nullptr;
    }
    auto pixel_format = canvas->GetPixelFormat();
    return SDL_CreateRGBSurfaceFrom(canvas->GetRawPixels(), canvas->GetWidth(), canvas->GetHeight(),
                                    pixel_format.bits_per_pixel, canvas->GetPitch(), pixel_format.r_mask,
                                    pixel_format.g_mask, pixel_format.b_mask, pixel_format.a_mask);
}

}  // namespace sdl2

}  // namespace zzgui

}  // namespace cozz
