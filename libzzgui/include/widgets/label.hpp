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

#include "canvas.hpp"
#include "widget.hpp"

namespace cozz {

namespace zzgui {

class FontResource;
class Painter;

class Label : public Widget {
  public:
    Label(const std::string& text, std::shared_ptr<FontResource> font, uint64_t x, uint64_t y);

    virtual void Draw(std::shared_ptr<Painter> painter) override;

    void SetText(const std::string& text);

    void SetFont(std::shared_ptr<FontResource> font);

    void SetBorderThickness(uint16_t thickness);

    void SetBorderColor(const Canvas::PixelColor& border_color);

    void SetBackgroundColor(const Canvas::PixelColor& background_color);

    void SetForegroundColor(const Canvas::PixelColor& foreground_color);

    const std::string& GetText() const;

    std::shared_ptr<FontResource> GetFont() const;

    uint16_t GetBorderThickness() const;

    const Canvas::PixelColor& GetBorderColor() const;

    const Canvas::PixelColor& GetBackgroundColor() const;

    const Canvas::PixelColor& GetForegroundColor() const;

    virtual void DoOnMouseButton(const MouseButtonEvent& event) override;

  protected:
    std::string text_;
    std::shared_ptr<FontResource> font_;

    uint16_t border_thickness_;

    Canvas::PixelColor border_color_;
    Canvas::PixelColor background_color_;
    Canvas::PixelColor foreground_color_;
};

}  // namespace zzgui

}  // namespace cozz

#endif  // LIBZZGUI_INCLUDE_WIDGETS_LABEL_HPP_
