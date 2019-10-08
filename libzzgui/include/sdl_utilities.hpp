/*
 * This file is part of LibZZgraph.

 * LibZZgraph is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * LibZZgraph is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with LibZZgraph. If not, see <https://www.gnu.org/licenses/>.
 *
 * Author: Pavlo Hrytsenko
*/

#ifndef LIBZZGRAPH_INCLUDE_SDL_UTILITIES_HPP_
#define LIBZZGRAPH_INCLUDE_SDL_UTILITIES_HPP_

#include <memory>

extern "C" typedef struct SDL_Surface SDL_Surface;

namespace cozz {

class Canvas;

namespace sdl2 {

std::shared_ptr<Canvas> CanvasFromSurface(const SDL_Surface* surface);

SDL_Surface* SurfaceFromCanvas(std::shared_ptr<Canvas> canvas);

}  // namespace sdl2

}  // namespace cozz

#endif  // LIBZZGRAPH_INCLUDE_SDL_UTILITIES_HPP_
