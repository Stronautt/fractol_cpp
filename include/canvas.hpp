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

#ifndef FRACTOL_INCLUDE_CANVAS_HPP_
#define FRACTOL_INCLUDE_CANVAS_HPP_

#include <cstdint>
#include <functional>
#include <memory>

namespace cozz {

template <class PixelType, class Deleter = std::function<void(PixelType*)>>
class Canvas {
  public:
    using iterator = PixelType*;
    using const_iterator = const PixelType*;

    Canvas(uint64_t width, uint64_t height)
        : Canvas(width, height, new PixelType[width * height * sizeof(PixelType)], std::default_delete<PixelType[]>()) {
    }

    Canvas(uint64_t width, uint64_t height, PixelType* pixels, Deleter deleter = [](PixelType*) {})
        : width_(width),
          height_(height),
          pitch_(width_ * sizeof(PixelType)),
          pixels_(std::shared_ptr<PixelType[]>(pixels, deleter)) {}

    uint64_t GetWidth() const { return width_; }
    uint64_t GetHeight() const { return height_; }
    uint64_t GetPitch() const { return pitch_; }

    iterator begin() { return pixels_.get(); }
    const_iterator cbegin() const { return pixels_.get(); }

    iterator end() { return &pixels_[height_ * width_]; }
    const_iterator cend() const { return &pixels_[height_ * width_]; }

    PixelType& At(uint64_t x, uint64_t y) { return pixels_[y * width_ + x]; }

    PixelType* GetRawPixels() { return pixels_.get(); }

  private:
    uint64_t width_;
    uint64_t height_;
    uint64_t pitch_;
    std::shared_ptr<PixelType[]> pixels_;
};

}  // namespace cozz

#endif  // FRACTOL_INCLUDE_CANVAS_HPP_
