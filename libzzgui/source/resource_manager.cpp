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

#include "resource_manager.hpp"

#include "font_resource.hpp"

namespace cozz {

namespace zzgui {

std::shared_ptr<FontResource> ResourceManager::LoadFont(const std::string& name, const std::string& font_path,
                                                        uint16_t font_size) {
    auto font = std::make_shared<FontResource>(name, font_path, font_size);
    resources_.emplace(name, font);
    return font;
}

}  // namespace zzgui

}  // namespace cozz
