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

#include "resources_manager.hpp"

namespace cozz {

namespace zzgui {

std::shared_ptr<FontResource> ResourcesManager::LoadFont(const std::string& name, const std::string& font_path,
                                                         uint16_t font_size) {
    return Load<FontResource>(name, font_path, font_size);
}

std::shared_ptr<ImageResource> ResourcesManager::LoadImage(const std::string& name, const std::string& img_path) {
    return Load<ImageResource>(name, img_path);
}

}  // namespace zzgui

}  // namespace cozz
