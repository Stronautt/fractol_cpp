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

#ifndef LIBZZGRAPH_INCLUDE_SDL_WINDOW_HPP_
#define LIBZZGRAPH_INCLUDE_SDL_WINDOW_HPP_

#include "window.hpp"

#include <cstdint>
#include <functional>
#include <memory>
#include <string>

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

    virtual std::weak_ptr<Canvas> GetCanvas() override;

  protected:
    virtual void Moved() override;

    virtual void Resized() override;

  private:
    std::unique_ptr<SDL_Window, std::function<void(SDL_Window*)>> window_;
    SDL_Surface* window_surface_;
    std::shared_ptr<Canvas> canvas_;
};

}  // namespace cozz

#endif  // LIBZZGRAPH_INCLUDE_SDL_WINDOW_HPP_
