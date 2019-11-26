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

#include "canvas.hpp"

#include <algorithm>
#include <cassert>

namespace cozz {

namespace zzgui {

Canvas::PixelColor::PixelColor() : PixelColor(0, 0, 0, 0) {}

Canvas::PixelColor::PixelColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
    : std::tuple<uint8_t, uint8_t, uint8_t, uint8_t>(r, g, b, a),
      r(std::get<0>(*this)),
      g(std::get<1>(*this)),
      b(std::get<2>(*this)),
      a(std::get<3>(*this)) {}

Canvas::PixelColor& Canvas::PixelColor::operator=(const PixelColor& color) {
    std::tuple<uint8_t, uint8_t, uint8_t, uint8_t>::operator=(color);
    return *this;
}

Canvas::PixelFormat::PixelFormat()
    : bits_per_pixel(kMinBitsPerPixel),
      bytes_per_pixel(kMinBytesPerPixel),
      r_mask(0x30),
      g_mask(0x0C),
      b_mask(0x03),
      a_mask(0xC0),
      r_loss(0x0),
      g_loss(0x0),
      b_loss(0x0),
      a_loss(0x0),
      r_shift(0x4),
      g_shift(0x2),
      b_shift(0x0),
      a_shift(0x6) {}

Canvas::PixelFormat::PixelFormat(uint8_t bits_per_pixel, uint8_t bytes_per_pixel, uint32_t r_mask, uint32_t g_mask,
                                 uint32_t b_mask, uint32_t a_mask, uint8_t r_loss, uint8_t g_loss, uint8_t b_loss,
                                 uint8_t a_loss, uint8_t r_shift, uint8_t g_shift, uint8_t b_shift, uint8_t a_shift)
    : bits_per_pixel(std::clamp(bits_per_pixel, kMinBitsPerPixel, kMaxBitsPerPixel)),
      bytes_per_pixel(std::clamp(bytes_per_pixel, kMinBytesPerPixel, kMaxBytesPerPixel)),
      r_mask(r_mask),
      g_mask(g_mask),
      b_mask(b_mask),
      a_mask(a_mask),
      r_loss(r_loss),
      g_loss(g_loss),
      b_loss(b_loss),
      a_loss(a_loss),
      r_shift(r_shift),
      g_shift(g_shift),
      b_shift(b_shift),
      a_shift(a_shift) {}

Canvas::pixel_iterator::pixel_iterator(uint8_t* pos, const PixelFormat& pixel_format)
    : pos_(pos), pixel_format_(pixel_format) {}

bool Canvas::pixel_iterator::operator==(const Canvas::pixel_iterator& other) const { return pos_ == other.pos_; }

bool Canvas::pixel_iterator::operator!=(const Canvas::pixel_iterator& other) const { return pos_ != other.pos_; }

Canvas::pixel_iterator& Canvas::pixel_iterator::operator=(uint32_t value) {
    SetColor({TransformR32to8(value), TransformG32to8(value), TransformB32to8(value), TransformA32to8(value)});
    return *this;
}

Canvas::pixel_iterator& Canvas::pixel_iterator::operator*() { return *this; }

Canvas::pixel_iterator::operator uint32_t() const {
    uint32_t ret = 0;

    if (pos_) {
        std::copy_n(pos_, pixel_format_.bytes_per_pixel, reinterpret_cast<uint8_t*>(&ret));
    }
    return ret;
}

Canvas::pixel_iterator& Canvas::pixel_iterator::operator++() {
    pos_ += pixel_format_.bytes_per_pixel;
    return *this;
}

uint8_t Canvas::pixel_iterator::R() const {
    uint32_t pixel = *this;
    return TransformR32to8(pixel);
}

void Canvas::pixel_iterator::R(uint8_t channel) {
    uint32_t pixel = *this;
    *this = (pixel & (~pixel_format_.r_mask)) | TransformR8to32(channel);
}

uint8_t Canvas::pixel_iterator::G() const {
    uint32_t pixel = *this;
    return TransformG32to8(pixel);
}

void Canvas::pixel_iterator::G(uint8_t channel) {
    uint32_t pixel = *this;
    *this = (pixel & (~pixel_format_.g_mask)) | TransformG8to32(channel);
}

uint8_t Canvas::pixel_iterator::B() const {
    uint32_t pixel = *this;
    return TransformB32to8(pixel);
}

void Canvas::pixel_iterator::B(uint8_t channel) {
    uint32_t pixel = *this;
    *this = (pixel & (~pixel_format_.b_mask)) | TransformB8to32(channel);
}

uint8_t Canvas::pixel_iterator::A() const {
    uint32_t pixel = *this;
    return TransformA32to8(pixel);
}

void Canvas::pixel_iterator::A(uint8_t channel) {
    uint32_t pixel = *this;
    *this = (pixel & (~pixel_format_.a_mask)) | TransformA8to32(channel);
}

Canvas::PixelColor Canvas::pixel_iterator::GetColor() const {
    uint32_t pixel = *this;
    return {TransformR32to8(pixel), TransformG32to8(pixel), TransformB32to8(pixel), TransformA32to8(pixel)};
}

void Canvas::pixel_iterator::SetColor(const PixelColor& color) {
    if (pos_ && color.a) {
        uint32_t value =
            TransformR8to32(color.r) | TransformG8to32(color.g) | TransformB8to32(color.b) | TransformA8to32(color.a);
        std::copy_n(reinterpret_cast<uint8_t*>(&value), pixel_format_.bytes_per_pixel, pos_);
    }
}

inline uint32_t Canvas::pixel_iterator::TransformR8to32(uint8_t channel) const {
    return (channel >> pixel_format_.r_loss) << pixel_format_.r_shift;
}

inline uint32_t Canvas::pixel_iterator::TransformG8to32(uint8_t channel) const {
    return (channel >> pixel_format_.g_loss) << pixel_format_.g_shift;
}

inline uint32_t Canvas::pixel_iterator::TransformB8to32(uint8_t channel) const {
    return (channel >> pixel_format_.b_loss) << pixel_format_.b_shift;
}

inline uint32_t Canvas::pixel_iterator::TransformA8to32(uint8_t channel) const {
    return (channel >> pixel_format_.a_loss) << pixel_format_.a_shift & pixel_format_.a_mask;
}

inline uint8_t Canvas::pixel_iterator::TransformR32to8(uint32_t pixel) const {
    return ((pixel & pixel_format_.r_mask) >> pixel_format_.r_shift) << pixel_format_.r_loss;
}

inline uint8_t Canvas::pixel_iterator::TransformG32to8(uint32_t pixel) const {
    return ((pixel & pixel_format_.g_mask) >> pixel_format_.g_shift) << pixel_format_.g_loss;
}

inline uint8_t Canvas::pixel_iterator::TransformB32to8(uint32_t pixel) const {
    return ((pixel & pixel_format_.b_mask) >> pixel_format_.b_shift) << pixel_format_.b_loss;
}

inline uint8_t Canvas::pixel_iterator::TransformA32to8(uint32_t pixel) const {
    return ((pixel & pixel_format_.a_mask) >> pixel_format_.a_shift) << pixel_format_.a_loss;
}

Canvas::Canvas(uint64_t width, uint64_t height, const PixelFormat& pixel_format)
    : Canvas(width, height, new uint8_t[width * height * pixel_format.bytes_per_pixel], pixel_format,
             std::default_delete<uint8_t[]>()) {}

Canvas::Canvas(uint64_t width, uint64_t height, uint8_t* pixels, const PixelFormat& pixel_format,
               std::function<void(uint8_t*)> deleter)
    : width_(width),
      height_(height),
      pixel_format_(pixel_format),
      pitch_(width_ * pixel_format_.bytes_per_pixel),
      pixels_(std::shared_ptr<uint8_t>(pixels, deleter)) {}

uint64_t Canvas::GetWidth() const { return width_; }

uint64_t Canvas::GetHeight() const { return height_; }

uint64_t Canvas::GetPitch() const { return pitch_; }

const Canvas::PixelFormat& Canvas::GetPixelFormat() const { return pixel_format_; }

Canvas::pixel_iterator Canvas::begin() { return pixel_iterator(pixels_.get(), pixel_format_); }

Canvas::const_pixel_iterator Canvas::cbegin() const { return const_pixel_iterator(pixels_.get(), pixel_format_); }

Canvas::pixel_iterator Canvas::end() { return pixel_iterator(&pixels_.get()[height_ * pitch_], pixel_format_); }

Canvas::const_pixel_iterator Canvas::cend() const {
    return const_pixel_iterator(&pixels_.get()[height_ * pitch_], pixel_format_);
}

Canvas::pixel_iterator Canvas::At(uint64_t x, uint64_t y) {
    if (x < width_ && y < height_) {
        return pixel_iterator(GetRawPixels() + y * pitch_ + x * pixel_format_.bytes_per_pixel, pixel_format_);
    }
    return pixel_iterator(nullptr, pixel_format_);
}

Canvas::pixel_iterator Canvas::At(const Point& p) { return At(p.x, p.y); }

uint8_t* Canvas::GetRawPixels() const { return pixels_.get(); }

}  // namespace zzgui

}  // namespace cozz
