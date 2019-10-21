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

#ifndef LIBZZGUI_INCLUDE_RESOURCE_MANAGER_HPP_
#define LIBZZGUI_INCLUDE_RESOURCE_MANAGER_HPP_

#include <map>
#include <memory>
#include <stdexcept>
#include <string>

namespace cozz {

namespace zzgui {

class Resource;
class FontResource;

class ResourceManager final {
  public:
    std::shared_ptr<FontResource> LoadFont(const std::string& name, const std::string& font_path, uint16_t font_size);

    template <class ResourceType>
    std::shared_ptr<ResourceType> Get(const std::string& name) const;

  private:
    std::map<std::string, std::shared_ptr<Resource>> resources_;
};

}  // namespace zzgui

}  // namespace cozz

#include "resource_manager.tpp"

#endif  // LIBZZGUI_INCLUDE_RESOURCE_MANAGER_HPP_
