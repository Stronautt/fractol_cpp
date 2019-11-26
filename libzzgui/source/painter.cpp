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

#include "painter.hpp"

#include <cmath>
#include <thread>

#include <SDL2/SDL_ttf.h>

#include "canvas.hpp"
#include "resources/font_resource.hpp"
#include "resources/image_resource.hpp"
#include "sdl_utilities.hpp"

namespace cozz {

namespace zzgui {

void Painter::Clear(std::shared_ptr<Canvas> canvas, const Canvas::PixelColor& color) {
    const auto surface = sdl2::SurfaceFromCanvas(canvas);

    uint32_t formated_color;
    Canvas::pixel_iterator(reinterpret_cast<uint8_t*>(&formated_color), canvas->GetPixelFormat()).SetColor(color);

    SDL_FillRect(surface.get(), NULL, formated_color);
}

void Painter::DrawLine(std::shared_ptr<Canvas> canvas, const Canvas::Point& a, const Canvas::Point& b,
                       const Canvas::PixelColor& color, uint16_t thickness) const {
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
            DrawFilledCircle(canvas, {a.x + (j >> 16), a.y + i}, thickness - 1, color);
        } else {
            DrawFilledCircle(canvas, {a.x + i, a.y + (j >> 16)}, thickness - 1, color);
        }
    }
}

void Painter::DrawCircle(std::shared_ptr<Canvas> canvas, const Canvas::Point& p, uint64_t radius,
                         const Canvas::PixelColor& color, uint16_t thickness) const {
    if (!thickness) {
        return;
    }

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

void Painter::DrawFilledCircle(std::shared_ptr<Canvas> canvas, const Canvas::Point& p, uint64_t radius,
                               const Canvas::PixelColor& color) const {
    DrawCircle(canvas, p, radius, color, radius + 1);
}

void Painter::DrawRect(std::shared_ptr<Canvas> canvas, const Canvas::Point& p, int64_t width, int64_t height,
                       const Canvas::PixelColor& color, uint16_t thickness) const {
    if (!width || !height || !thickness) {
        return;
    }

    int64_t x = p.x, y = p.y;
    do {
        DrawLine(canvas, {x, y}, {x + width, y}, color, 1);
        DrawLine(canvas, {x, y}, {x, y + height}, color, 1);

        DrawLine(canvas, {x, y + height}, {x + width, y + height}, color, 1);
        DrawLine(canvas, {x + width, y}, {x + width, y + height + 1}, color, 1);

        height -= 2;
        width -= 2;
        ++x;
        ++y;
    } while (--thickness);
}

void Painter::DrawFilledRect(std::shared_ptr<Canvas> canvas, const Canvas::Point& p, int64_t width, int64_t height,
                             const Canvas::PixelColor& color) const {
    const auto surface = sdl2::SurfaceFromCanvas(canvas);
    const SDL_Rect rect{static_cast<int>(p.x), static_cast<int>(p.y), static_cast<int>(width),
                        static_cast<int>(height)};

    if (color.a) {
        uint32_t formated_color;
        Canvas::pixel_iterator(reinterpret_cast<uint8_t*>(&formated_color), canvas->GetPixelFormat()).SetColor(color);

        SDL_FillRect(surface.get(), &rect, formated_color);
    }
}

void Painter::DrawText(std::shared_ptr<Canvas> canvas, const Canvas::Point& p, const std::string text,
                       std::shared_ptr<FontResource> font, const Canvas::PixelColor& color) const {
    if (!font) {
        return;
    }
    const auto surface = sdl2::SurfaceFromCanvas(canvas);

    auto font_surface = std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)>(
        TTF_RenderUTF8_Blended(static_cast<TTF_Font*>(font->GetFontData().get()), text.c_str(),
                               {color.r, color.g, color.b, color.a}),
        &SDL_FreeSurface);
    SDL_Rect destination{static_cast<int>(p.x), static_cast<int>(p.y), 0, 0};

    SDL_BlitSurface(font_surface.get(), nullptr, surface.get(), &destination);
}

void Painter::DrawImage(std::shared_ptr<Canvas> canvas, const Canvas::Point& p,
                        std::shared_ptr<ImageResource> img) const {
    if (!img) {
        return;
    }
    auto img_size = img->GetSize();
    DrawImage(canvas, p, img, img_size.first, img_size.second);
}

void Painter::DrawImage(std::shared_ptr<Canvas> canvas, const Canvas::Point& p, std::shared_ptr<ImageResource> img,
                        int64_t width, int64_t height) const {
    const auto surface = sdl2::SurfaceFromCanvas(canvas);

    SDL_Rect destination{static_cast<int>(p.x), static_cast<int>(p.y), static_cast<int>(width),
                         static_cast<int>(height)};

    SDL_BlitScaled(static_cast<SDL_Surface*>(img->GetImgData().get()), nullptr, surface.get(), &destination);
}

}  // namespace zzgui

}  // namespace cozz
