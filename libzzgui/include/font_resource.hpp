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

#ifndef LIBZZGUI_INCLUDE_FONT_RESOURCE_HPP_
#define LIBZZGUI_INCLUDE_FONT_RESOURCE_HPP_

#include "resource.hpp"

#include <memory>

extern "C" typedef struct _TTF_Font TTF_Font;

namespace cozz {

namespace zzgui {

class FontResource final : public Resource {
  public:
    FontResource(const std::string& name, const std::string& font_path, uint16_t font_size);

    std::shared_ptr<TTF_Font> GetFontData() const;

  private:
    std::shared_ptr<TTF_Font> font_;
};

}  // namespace zzgui

}  // namespace cozz

#endif  // LIBZZGUI_INCLUDE_FONT_RESOURCE_HPP_
