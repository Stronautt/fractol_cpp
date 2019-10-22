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

template <class ResourceType>
std::shared_ptr<ResourceType> ResourcesManager::Get(const std::string& name) const {
    static_assert(std::is_convertible<ResourceType, Resource>::value);

    auto resource = resources_.find(name);
    if (resource != resources_.end()) {
        return std::dynamic_pointer_cast<ResourceType>(resource->second);
    } else {
        throw std::runtime_error("Uknown resource name: " + name);
    }
}

}  // namespace zzgui

}  // namespace cozz
