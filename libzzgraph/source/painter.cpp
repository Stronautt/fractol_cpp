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

#include "painter.hpp"

#include <cmath>

#include <SDL2/SDL_ttf.h>

#include "canvas.hpp"
#include "font_resource.hpp"
#include "sdl_utilities.hpp"

namespace cozz {

Painter::Painter(std::weak_ptr<Canvas> canvas) : canvas_(canvas) {}

void Painter::ResetCanvas(std::weak_ptr<Canvas> canvas) { canvas_ = canvas; }

void Painter::DrawLine(const Canvas::Point& a, const Canvas::Point& b, const Canvas::PixelColor& color,
                       uint16_t thickness) const {
    auto canvas = GetCanvas();

    int64_t short_length = b.y - a.y;
    int64_t long_length = b.x - a.x;

    bool y_longer = false;
    if (std::abs(short_length) > std::abs(long_length)) {
        std::swap(short_length, long_length);
        y_longer = true;
    }

    int64_t end_value = long_length;
    int64_t step_i = long_length < 0 ? -1 : 1;

    long_length = std::abs(long_length);

    int64_t step_j = !long_length ? 0 : (short_length << 16) / long_length;
    for (int64_t i = 0, j = 0; i != end_value; i += step_i, j += step_j) {
        if (y_longer) {
            DrawFilledCircle({a.x + (j >> 16), a.y + i}, thickness - 1, color);
        } else {
            DrawFilledCircle({a.x + i, a.y + (j >> 16)}, thickness - 1, color);
        }
    }
}

void Painter::DrawCircle(const Canvas::Point& p, uint64_t radius, const Canvas::PixelColor& color,
                         uint16_t thickness) const {
    if (!thickness) {
        return;
    }

    auto canvas = GetCanvas();

    if (!radius) {
        canvas->At(p).SetColor(color);
        return;
    }

    do {
        int64_t x = radius - thickness + 1;
        int64_t y = 0;
        int64_t error = 0;

        while (x >= y) {
            canvas->At(p.x + x, p.y + y).SetColor(color);
            canvas->At(p.x + y, p.y + x).SetColor(color);
            canvas->At(p.x - y, p.y + x).SetColor(color);
            canvas->At(p.x - x, p.y + y).SetColor(color);
            canvas->At(p.x - x, p.y - y).SetColor(color);
            canvas->At(p.x - y, p.y - x).SetColor(color);
            canvas->At(p.x + y, p.y - x).SetColor(color);
            canvas->At(p.x + x, p.y - y).SetColor(color);

            if (error <= 0) {
                y += 1;
                error += 2 * y + 1;
            } else {
                x -= 1;
                error -= 2 * x + 1;
            }
        }
    } while (--thickness);
}

void Painter::DrawFilledCircle(const Canvas::Point& p, uint64_t radius, const Canvas::PixelColor& color) const {
    DrawCircle(p, radius, color, radius + 1);
}

void Painter::DrawRect(const Canvas::Point& p, uint64_t width, uint64_t height, const Canvas::PixelColor& color,
                       uint16_t thickness) const {
    if (!width || !height || !thickness) {
        return;
    }

    uint64_t x = p.x, y = p.y;
    do {
        DrawLine({x, y}, {x + width, y}, color, 1);
        DrawLine({x, y}, {x, y + height}, color, 1);

        DrawLine({x, y + height}, {x + width, y + height}, color, 1);
        DrawLine({x + width, y}, {x + width, y + height + 1}, color, 1);

        height -= 2;
        width -= 2;
        ++x;
        ++y;
    } while (--thickness);
}

void Painter::DrawFilledRect(const Canvas::Point& p, uint64_t width, uint64_t height,
                             const Canvas::PixelColor& color) const {
    DrawRect(p, width, height, color, std::min(width, height) / 2.0 + 1);
}

void Painter::DrawText(const Canvas::Point& p, const std::string text, std::shared_ptr<FontResource> font,
                       const Canvas::PixelColor& color) {
    auto font_surface = std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)>(
        TTF_RenderUTF8_Blended(font->GetFontData().get(), text.c_str(), {color.r, color.g, color.b, color.a}),
        &SDL_FreeSurface);
    auto surface = std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)>(sdl2::SurfaceFromCanvas(canvas_.lock()),
                                                                            &SDL_FreeSurface);
    SDL_Rect destination{static_cast<int>(p.x), static_cast<int>(p.y), 0, 0};
    SDL_BlitSurface(font_surface.get(), nullptr, surface.get(), &destination);
}

std::shared_ptr<Canvas> Painter::GetCanvas() const {
    if (canvas_.expired()) {
        throw std::runtime_error("Canvas is expired");
    }
    return canvas_.lock();
}

}  // namespace cozz
