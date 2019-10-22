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

#include "resources/image_resource.hpp"

#include <SDL2/SDL_image.h>

#include <stdexcept>

namespace cozz {

namespace zzgui {

ImageResource::ImageResource(const std::string& name, const std::string& img_path) : Resource(name) {
    int init_flags = IMG_INIT_JPG | IMG_INIT_PNG;
    if (!(IMG_Init(init_flags) & init_flags)) {
        throw std::runtime_error("Unable to init Image library: " + std::string(IMG_GetError()));
    }
    img_.reset(IMG_Load(img_path.c_str()), &SDL_FreeSurface);
    if (img_ == nullptr) {
        throw std::runtime_error("Unable to load image: " + std::string(IMG_GetError()));
    }
}

std::shared_ptr<void> ImageResource::GetImgData() const { return img_; }

std::pair<uint64_t, uint64_t> ImageResource::GetSize() const {
    auto surface = std::static_pointer_cast<SDL_Surface>(img_);

    return std::make_pair(surface->w, surface->h);
}

}  // namespace zzgui

}  // namespace cozz
