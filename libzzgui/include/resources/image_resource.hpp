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

#ifndef LIBZZGUI_INCLUDE_IMAGE_RESOURCE_HPP_
#define LIBZZGUI_INCLUDE_IMAGE_RESOURCE_HPP_

#include "resource.hpp"

#include <memory>
#include <utility>

namespace cozz {

namespace zzgui {

class ImageResource final : public Resource {
  public:
    ImageResource(const std::string& name, const std::string& img_path);

    std::shared_ptr<void> GetImgData() const;

    std::pair<uint64_t, uint64_t> GetSize() const;

  private:
    std::shared_ptr<void> img_;
};

}  // namespace zzgui

}  // namespace cozz

#endif  // LIBZZGUI_INCLUDE_IMAGE_RESOURCE_HPP_
