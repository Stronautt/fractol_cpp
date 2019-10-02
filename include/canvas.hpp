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

#include <algorithm>
#include <cstdint>
#include <functional>
#include <memory>

namespace cozz {

class Canvas {
  public:
    static constexpr uint8_t kMinBytesPerPixel = 1;
    static constexpr uint8_t kMaxBytesPerPixel = 4;

    class iterator {
      public:
        iterator(uint8_t* pos, uint8_t bytes_per_pixel);

        bool operator==(const iterator& other) const;
        bool operator!=(const iterator& other) const;
        iterator& operator=(uint32_t value);
        iterator& operator*();
        operator uint32_t() const;
        iterator operator++();

      private:
        uint8_t* pos_;
        uint8_t bytes_per_pixel_;
    };
    using const_iterator = const iterator;

    Canvas(uint64_t width, uint64_t height, uint8_t bytes_per_pixel = kMinBytesPerPixel);

    Canvas(uint64_t width, uint64_t height, uint8_t* pixels, uint8_t bytes_per_pixel = kMinBytesPerPixel,
           std::function<void(uint8_t*)> deleter = [](uint8_t*) {});

    uint64_t GetWidth() const;
    uint64_t GetHeight() const;
    uint64_t GetPitch() const;
    uint8_t GetBytesPerPixel() const;

    iterator begin();
    const_iterator cbegin() const;

    iterator end();
    const_iterator cend() const;

    iterator At(uint64_t x, uint64_t y);

    uint8_t* GetRawPixels() const;

  private:
    // Size of the canvas
    uint64_t width_;
    uint64_t height_;

    // Parameters which belongs to the pixel format
    uint8_t bytes_per_pixel_;
    uint64_t pitch_;

    // Pixels array
    std::shared_ptr<uint8_t[]> pixels_;
};

}  // namespace cozz

#endif  // FRACTOL_INCLUDE_CANVAS_HPP_
