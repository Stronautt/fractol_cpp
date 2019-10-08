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

#ifndef LIBZZGRAPH_INCLUDE_SDL_EVENT_HANDLER_HPP_
#define LIBZZGRAPH_INCLUDE_SDL_EVENT_HANDLER_HPP_

#include <functional>

#include "event_handler.hpp"
#include "key_map.hpp"

namespace cozz {

class SDLEventHandler final : public EventHandler {
  public:
    SDLEventHandler();

    virtual bool Poll() const override;
};

}  // namespace cozz

#endif  // LIBZZGRAPH_INCLUDE_SDL_EVENT_HANDLER_HPP_