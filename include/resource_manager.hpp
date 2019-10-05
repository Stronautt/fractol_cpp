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

#ifndef FRACTOL_INCLUDE_RESOURCE_MANAGER_HPP_
#define FRACTOL_INCLUDE_RESOURCE_MANAGER_HPP_

#include <map>
#include <memory>
#include <stdexcept>
#include <string>

namespace cozz {

class Resource;
class FontResource;

class ResourceManager final {
  public:
    std::shared_ptr<FontResource> LoadFont(const std::string& name, const std::string& font_path, uint16_t font_size);

    template <class ResourceType>
    std::shared_ptr<ResourceType> Get(const std::string& name) const {
        static_assert(std::is_convertible<ResourceType, Resource>::value);

        auto resource = resources_.find(name);
        if (resource != resources_.end()) {
            return std::dynamic_pointer_cast<ResourceType>(resource->second);
        } else {
            throw std::runtime_error("Uknown resource name: " + name);
        }
    }

  private:
    std::map<std::string, std::shared_ptr<Resource>> resources_;
};

}  // namespace cozz

#endif  // FRACTOL_INCLUDE_RESOURCE_MANAGER_HPP_
