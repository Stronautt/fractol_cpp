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

#ifndef LIBZZGUI_INCLUDE_PAINTER_HPP_
#define LIBZZGUI_INCLUDE_PAINTER_HPP_

#include <memory>
#include <tuple>
#include <utility>

#include "canvas.hpp"

namespace cozz {

namespace zzgui {

class FontResource;
class ImageResource;

class Painter final {
  public:
    void Clear(std::shared_ptr<Canvas> canvas, const Canvas::PixelColor& color);

    void DrawLine(std::shared_ptr<Canvas> canvas, const Canvas::Point& a, const Canvas::Point& b,
                  const Canvas::PixelColor& color = {0, 0, 0}, uint16_t thickness = 1) const;

    void DrawCircle(std::shared_ptr<Canvas> canvas, const Canvas::Point& p, uint64_t radius,
                    const Canvas::PixelColor& color = {0, 0, 0}, uint16_t thickness = 1) const;

    void DrawFilledCircle(std::shared_ptr<Canvas> canvas, const Canvas::Point& p, uint64_t radius,
                          const Canvas::PixelColor& color = {0, 0, 0}) const;

    void DrawRect(std::shared_ptr<Canvas> canvas, const Canvas::Point& p, int64_t width, int64_t height,
                  const Canvas::PixelColor& color = {0, 0, 0}, uint16_t thickness = 1) const;

    void DrawFilledRect(std::shared_ptr<Canvas> canvas, const Canvas::Point& p, int64_t width, int64_t height,
                        const Canvas::PixelColor& color = {0, 0, 0}) const;

    void DrawText(std::shared_ptr<Canvas> canvas, const Canvas::Point& p, const std::string text,
                  std::shared_ptr<FontResource> font, const Canvas::PixelColor& color = {0xFF, 0xFF, 0xFF}) const;

    void DrawImage(std::shared_ptr<Canvas> canvas, const Canvas::Point& p, std::shared_ptr<ImageResource> img) const;

    void DrawImage(std::shared_ptr<Canvas> canvas, const Canvas::Point& p, std::shared_ptr<ImageResource> img,
                   int64_t width, int64_t height) const;
};

}  // namespace zzgui

}  // namespace cozz

#endif  // LIBZZGUI_INCLUDE_PAINTER_HPP_
