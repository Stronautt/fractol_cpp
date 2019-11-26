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

#ifndef LIBZZGUI_INCLUDE_CANVAS_HPP_
#define LIBZZGUI_INCLUDE_CANVAS_HPP_

#include <algorithm>
#include <cstdint>
#include <functional>
#include <memory>
#include <tuple>

namespace cozz {

namespace zzgui {

class Canvas final {
  public:
    struct Point {
        int64_t x;
        int64_t y;
    };

    class PixelColor : public std::tuple<uint8_t, uint8_t, uint8_t, uint8_t> {
      public:
        PixelColor();
        PixelColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 0xFF);

        PixelColor& operator=(const PixelColor& color);

        uint8_t& r;
        uint8_t& g;
        uint8_t& b;
        uint8_t& a;
    };

    struct PixelFormat final {
        static constexpr uint8_t kMinBytesPerPixel = 1;
        static constexpr uint8_t kMinBitsPerPixel = kMinBytesPerPixel * 8;

        static constexpr uint8_t kMaxBytesPerPixel = 4;
        static constexpr uint8_t kMaxBitsPerPixel = kMaxBytesPerPixel * 8;

        PixelFormat();

        PixelFormat(uint8_t bits_per_pixel, uint8_t bytes_per_pixel, uint32_t r_mask, uint32_t g_mask, uint32_t b_mask,
                    uint32_t a_mask, uint8_t r_loss, uint8_t g_loss, uint8_t b_loss, uint8_t a_loss, uint8_t r_shift,
                    uint8_t g_shift, uint8_t b_shift, uint8_t a_shift);

        uint8_t bits_per_pixel;
        uint8_t bytes_per_pixel;

        uint32_t r_mask;
        uint32_t g_mask;
        uint32_t b_mask;
        uint32_t a_mask;

        uint8_t r_loss;
        uint8_t g_loss;
        uint8_t b_loss;
        uint8_t a_loss;

        uint8_t r_shift;
        uint8_t g_shift;
        uint8_t b_shift;
        uint8_t a_shift;
    };

    class pixel_iterator final {
      public:
        pixel_iterator(uint8_t* pos, const PixelFormat& format);

        bool operator==(const pixel_iterator& other) const;
        bool operator!=(const pixel_iterator& other) const;
        pixel_iterator& operator=(uint32_t value);
        pixel_iterator& operator*();
        operator uint32_t() const;
        pixel_iterator& operator++();

        uint8_t R() const;
        void R(uint8_t channel);

        uint8_t G() const;
        void G(uint8_t channel);

        uint8_t B() const;
        void B(uint8_t channel);

        uint8_t A() const;
        void A(uint8_t channel);

        PixelColor GetColor() const;
        void SetColor(const PixelColor& color);

      private:
        uint8_t* pos_;
        const PixelFormat& pixel_format_;

        uint32_t TransformR8to32(uint8_t channel) const;
        uint32_t TransformG8to32(uint8_t channel) const;
        uint32_t TransformB8to32(uint8_t channel) const;
        uint32_t TransformA8to32(uint8_t channel) const;

        uint8_t TransformR32to8(uint32_t pixel) const;
        uint8_t TransformG32to8(uint32_t pixel) const;
        uint8_t TransformB32to8(uint32_t pixel) const;
        uint8_t TransformA32to8(uint32_t pixel) const;
    };
    using const_pixel_iterator = const pixel_iterator;

    Canvas(uint64_t width, uint64_t height, const PixelFormat& pixel_format = PixelFormat());

    Canvas(uint64_t width, uint64_t height, uint8_t* pixels, const PixelFormat& pixel_format = PixelFormat(),
           std::function<void(uint8_t*)> deleter = [](uint8_t*) {});

    uint64_t GetWidth() const;
    uint64_t GetHeight() const;
    uint64_t GetPitch() const;
    const Canvas::PixelFormat& GetPixelFormat() const;

    pixel_iterator begin();
    const_pixel_iterator cbegin() const;

    pixel_iterator end();
    const_pixel_iterator cend() const;

    pixel_iterator At(uint64_t x, uint64_t y);

    pixel_iterator At(const Point& p);

    uint8_t* GetRawPixels() const;

  private:
    // Size of the canvas
    uint64_t width_;
    uint64_t height_;

    // Parameters which belongs to the pixel format
    PixelFormat pixel_format_;
    uint64_t pitch_;

    // Pixels array
    std::shared_ptr<uint8_t> pixels_;
};

}  // namespace zzgui

}  // namespace cozz

#endif  // LIBZZGUI_INCLUDE_CANVAS_HPP_
