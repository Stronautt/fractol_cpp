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

#ifndef FRACTOL_INCLUDE_INTERFACE_WINDOW_HPP_
#define FRACTOL_INCLUDE_INTERFACE_WINDOW_HPP_

#include <cstdint>

namespace cozz {

class Window {
  public:
    virtual ~Window();

    virtual void Update() = 0;

    virtual uint32_t GetID() const = 0;

    uint64_t GetWidth() const;

    uint64_t GetHeight() const;

    void Resize(uint64_t width, uint64_t height);

  protected:
    uint64_t x_;
    uint64_t y_;

    uint64_t width_;
    uint64_t height_;

    Window(uint64_t x, uint64_t y, uint64_t width, uint64_t height);

    virtual void Resize() = 0;
};

}  // namespace cozz

#endif  // FRACTOL_INCLUDE_INTERFACE_WINDOW_HPP_
