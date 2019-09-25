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

#include "sdl_event_handler.hpp"

#include <SDL2/SDL.h>

#include "event/quit_event.hpp"

namespace cozz {

SDLEventHandler::SDLEventHandler() {
    if (!SDL_WasInit(SDL_INIT_EVENTS)) {
        SDL_Init(SDL_INIT_EVENTS);
    }
}

bool SDLEventHandler::Poll() const {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        switch (e.type) {
            case SDL_QUIT:
                TriggerCallbacks(QuitEvent());
                break;
            default:
                return false;
        }
    }
    return true;
}

}  // namespace cozz
