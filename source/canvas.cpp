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

#include "canvas.hpp"

namespace cozz {

Canvas::iterator::iterator(uint8_t* pos, uint8_t bytes_per_pixel)
    : pos_(pos), bytes_per_pixel_(std::clamp(bytes_per_pixel, Canvas::kMinBytesPerPixel, Canvas::kMaxBytesPerPixel)) {}

bool Canvas::iterator::operator==(const Canvas::iterator& other) const { return pos_ == other.pos_; }

bool Canvas::iterator::operator!=(const Canvas::iterator& other) const { return pos_ != other.pos_; }

Canvas::iterator& Canvas::iterator::operator=(uint32_t value) {
    std::copy_n(reinterpret_cast<uint8_t*>(&value), sizeof(value), pos_);
    return *this;
}

Canvas::iterator& Canvas::iterator::operator*() { return *this; }

Canvas::iterator::operator uint32_t() const {
    uint32_t ret = 0;

    std::copy_n(pos_, bytes_per_pixel_, reinterpret_cast<uint8_t*>(&ret));
    return ret;
}

Canvas::iterator Canvas::iterator::operator++() { pos_ += bytes_per_pixel_; }

Canvas::Canvas(uint64_t width, uint64_t height, uint8_t bytes_per_pixel)
    : Canvas(width, height, new uint8_t[width * height * bytes_per_pixel], bytes_per_pixel,
             std::default_delete<uint8_t[]>()) {}

Canvas::Canvas(uint64_t width, uint64_t height, uint8_t* pixels, uint8_t bytes_per_pixel,
               std::function<void(uint8_t*)> deleter)
    : width_(width),
      height_(height),
      bytes_per_pixel_(std::clamp(bytes_per_pixel, Canvas::kMinBytesPerPixel, Canvas::kMaxBytesPerPixel)),
      pitch_(width_ * bytes_per_pixel_),
      pixels_(std::shared_ptr<uint8_t[]>(pixels, deleter)) {}

uint64_t Canvas::GetWidth() const { return width_; }

uint64_t Canvas::GetHeight() const { return height_; }

uint64_t Canvas::GetPitch() const { return pitch_; }

uint8_t Canvas::GetBytesPerPixel() const { return bytes_per_pixel_; }

Canvas::iterator Canvas::begin() { return iterator(pixels_.get(), bytes_per_pixel_); }

Canvas::const_iterator Canvas::cbegin() const { return const_iterator(pixels_.get(), bytes_per_pixel_); }

Canvas::iterator Canvas::end() { return iterator(&pixels_[height_ * pitch_], bytes_per_pixel_); }

Canvas::const_iterator Canvas::cend() const { return const_iterator(&pixels_[height_ * pitch_], bytes_per_pixel_); }

Canvas::iterator Canvas::At(uint64_t x, uint64_t y) {
    return iterator(GetRawPixels() + y * pitch_ + x * bytes_per_pixel_, bytes_per_pixel_);
}

uint8_t* Canvas::GetRawPixels() const { return pixels_.get(); }

}  // namespace cozz
