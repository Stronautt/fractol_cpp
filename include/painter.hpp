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

#ifndef FRACTOL_INCLUDE_PAINTER_HPP_
#define FRACTOL_INCLUDE_PAINTER_HPP_

#include <memory>
#include <utility>
#include <tuple>

#include "canvas.hpp"

namespace cozz {

class Painter final {
  public:
    Painter(std::weak_ptr<Canvas> canvas);

    void DrawLine(const Canvas::Point& a, const Canvas::Point& b, const Canvas::PixelColor& color = {0, 0, 0}, uint16_t thickness = 1) const;

    void DrawCircle(const Canvas::Point& p, uint64_t radius, const Canvas::PixelColor& color = {0, 0, 0}, uint16_t thickness = 1) const;

    void DrawFilledCircle(const Canvas::Point& p, uint64_t radius, const Canvas::PixelColor& color = {0, 0, 0}) const;

    void DrawRect(const Canvas::Point& p, uint64_t width, uint64_t height, const Canvas::PixelColor& color = {0, 0, 0}, uint16_t thickness = 1) const;

    void DrawFilledRect(const Canvas::Point& p, uint64_t width, uint64_t height, const Canvas::PixelColor& color = {0, 0, 0}) const;

  private:
    std::weak_ptr<Canvas> canvas_;

    std::shared_ptr<Canvas> GetCanvas() const;
};

}  // namespace cozz

#endif  // FRACTOL_INCLUDE_PAINTER_HPP_
