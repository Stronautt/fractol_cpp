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

#ifndef LIBZZGUI_INCLUDE_WIDGETS_LABEL_HPP_
#define LIBZZGUI_INCLUDE_WIDGETS_LABEL_HPP_

#include <cstdint>
#include <memory>
#include <string>
#include <utility>

#include "widget.hpp"

namespace cozz {

namespace zzgui {

class FontResource;
class Painter;

class Label final : public Widget {
  public:
    Label(const std::string& text, std::shared_ptr<FontResource> font, uint64_t x, uint64_t y);

    virtual void Draw(std::shared_ptr<Painter> painter) override;

    void SetText(const std::string& text);

    const std::string& GetText() const;

    void SetFont(std::shared_ptr<FontResource> font);

    std::shared_ptr<FontResource> GetFont() const;

  private:
    std::string text_;
    std::shared_ptr<FontResource> font_;
};

}  // namespace zzgui

}  // namespace cozz

#endif  // LIBZZGUI_INCLUDE_WIDGETS_LABEL_HPP_
