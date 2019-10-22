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

#include "resources/font_resource.hpp"

#include <SDL2/SDL_ttf.h>

#include <stdexcept>

namespace cozz {

namespace zzgui {

FontResource::FontResource(const std::string& name, const std::string& font_path, uint16_t font_size) : Resource(name) {
    if (!TTF_WasInit() && TTF_Init() == -1) {
        throw std::runtime_error("Unable to init TTF library: " + std::string(TTF_GetError()));
    }
    font_.reset(TTF_OpenFont(font_path.c_str(), font_size), &TTF_CloseFont);
    if (font_ == nullptr) {
        throw std::runtime_error("Unable to load font: " + std::string(TTF_GetError()));
    }
}

std::shared_ptr<void> FontResource::GetFontData() const { return font_; }

std::pair<uint64_t, uint64_t> FontResource::CalcTextSize(const std::string& text) const {
    int widht;
    int height;

    if (TTF_SizeUTF8(static_cast<TTF_Font*>(font_.get()), text.c_str(), &widht, &height)) {
        throw std::runtime_error("Can't calc text size: " + std::string(TTF_GetError()));
    }
    return std::make_pair(widht, height);
}

}  // namespace zzgui

}  // namespace cozz
