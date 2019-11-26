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

#include "views/pythagoras_tree_fractal.hpp"

#include "controllers/pythagoras_tree_fractal.hpp"
#include "models/pythagoras_tree_fractal.hpp"
#include "painter.hpp"
#include "widgets_manager.hpp"
#include "window.hpp"

namespace cozz {

PythagorasTreeFractalView::PythagorasTreeFractalView(std::weak_ptr<PythagorasTreeFractalModel> model) : View(model) {}

void PythagorasTreeFractalView::Create() { painter_ = std::make_shared<zzgui::Painter>(); }

void PythagorasTreeFractalView::Render(float /*delta*/) {
    const auto model = GetModel().lock();
    const auto window = model->GetWindow().lock();
    const auto canvas = window->GetCanvas().lock();

    painter_->Clear(canvas, {0, 0, 0});
    DrawFractal(canvas,
                {static_cast<int64_t>(window->GetWidth() / 2 - model->GetSideLength() / 2),
                 static_cast<int64_t>(window->GetHeight() - 5)},
                {static_cast<int64_t>(window->GetWidth() / 2 + model->GetSideLength() / 2),
                 static_cast<int64_t>(window->GetHeight() - 5)},
                model->GetDepth());
    const auto widgets_manager = model->GetWidgetsManager().lock();
    for (const auto& widget : widgets_manager->GetWidgets()) {
        widget.second->Draw(painter_, canvas);
    }
}

namespace {
inline constexpr double lerp(double v0, double v1, double t) { return (1 - t) * v0 + t * v1; }
}  // namespace

void PythagorasTreeFractalView::DrawFractal(std::shared_ptr<zzgui::Canvas> canvas, zzgui::Canvas::Point a,
                                            zzgui::Canvas::Point b, int32_t depth) const {
    const auto model = GetModel().lock();
    zzgui::Canvas::Point c, d, e;

    c.x = b.x - (a.y - b.y);
    c.y = b.y - (b.x - a.x);

    d.x = a.x - (a.y - b.y);
    d.y = a.y - (b.x - a.x);

    e.x = d.x + (b.x - a.x - (a.y - b.y)) / 2;
    e.y = d.y - (b.x - a.x + a.y - b.y) / 2;

    if (depth > 0) {
        zzgui::Canvas::PixelColor color = {static_cast<uint8_t>(lerp(0, 0x8B, depth / (double)model->GetDepth())),
                                           static_cast<uint8_t>(lerp(0xFF, 0x45, depth / (double)model->GetDepth())),
                                           static_cast<uint8_t>(lerp(0, 0x13, depth / (double)model->GetDepth()))};

        painter_->DrawLine(canvas, a, b, color);
        painter_->DrawLine(canvas, c, b, color);
        painter_->DrawLine(canvas, c, d, color);
        painter_->DrawLine(canvas, a, d, color);

        DrawFractal(canvas, d, e, depth - 1);
        DrawFractal(canvas, e, c, depth - 1);
    }
}

void PythagorasTreeFractalView::Resized(std::weak_ptr<zzgui::Window> /*window*/) {}

void PythagorasTreeFractalView::Show() {}

void PythagorasTreeFractalView::Pause() {}

void PythagorasTreeFractalView::Resume() {}

void PythagorasTreeFractalView::Hide() {}

}  // namespace cozz
