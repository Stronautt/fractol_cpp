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

#include "views/mandelfract.hpp"

#include "controllers/mandelfract.hpp"
#include "model.hpp"
#include "models/mandelfract.hpp"
#include "painter.hpp"
#include "resources/font_resource.hpp"
#include "resources_manager.hpp"
#include "view.tpp"
#include "widget.hpp"
#include "widgets/label.hpp"
#include "widgets_manager.hpp"
#include "window.hpp"

namespace cozz {

MandelfractView::MandelfractView(std::weak_ptr<MandelfractModel> model) : View(model) {}

void MandelfractView::Create() {
    auto model = GetModel().lock();
    Resized(model->GetWindow());
}

void MandelfractView::Render(float /*delta*/) {
    auto model = GetModel().lock();
    auto window = model->GetWindow().lock();
    auto canvas = window->GetCanvas().lock();

    // canvas->Clear({0xFF, 0xFF, 0xFF});
    DrawFractal(canvas);
    for (const auto& widget : model->GetWidgetsManager().lock()->GetWidgets()) {
        widget->Draw(painter_);
    }
}

void MandelfractView::Resized(std::weak_ptr<zzgui::Window> window) {
    const auto window_ptr = window.lock();

    if (window_ptr) {
        painter_ = std::make_shared<zzgui::Painter>(window_ptr->GetCanvas());
    }
}

void MandelfractView::Show() {}

void MandelfractView::Pause() {}

void MandelfractView::Resume() {}

void MandelfractView::Hide() {}

/*
 static inline unsigned int ft_smooth(double it, double max_it)
{
    double  t;
    int     r;
    int     g;
    int     b;

    t = it / max_it;
    r = 9 * (1 - t) * t * t * t * 255;
    g = 15 * (1 - t) * (1 - t) * t * t * 255;
    b = 8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255;
    return (r * 0x10000 + g * 0x100 + b);
}

__kernel void
fill_mandelfract(__global int *buff, double pivot_x,
                double pivot_y, double dx, int height, int width)
{
    int             it = 0;
    int             x = get_global_id(0);
    int             y = get_global_id(1);
    double3         z = (double3) 0;
    double2         c;

    c = (double2)(pivot_x + (x - width / 2) * dx,
        pivot_y + (y - height / 2) * dx);
    while ((z.x * z.x + z.y * z.y) <= 4.0 && (++it < MAX_ITERATIONS))
    {
        z.z = z.x * z.x - z.y * z.y + c.x;
        z.y = 2 * z.x * z.y + c.y;
        z.x = z.z;
    }
    buff[y * width + x] = ft_smooth(it, MAX_ITERATIONS);
}
 */

zzgui::Canvas::PixelColor MandelfractView::GetSmoothColor(double t) const {
    zzgui::Canvas::PixelColor ret;

    ret.r = 9 * (1 - t) * t * t * t * 255;
    ret.g = 15 * (1 - t) * (1 - t) * t * t * 255;
    ret.b = 8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255;
    return ret;
}

void MandelfractView::DrawFractal(std::shared_ptr<zzgui::Canvas> canvas) const {
    if (!canvas) {
        return;
    }

    auto model = GetModel().lock();

    uint64_t width = canvas->GetWidth();
    uint64_t height = canvas->GetHeight();

    double zx, zy, zz;
    double cx, cy;

    auto offset = model->GetOffset();

    for (uint64_t x = 0; x < width; ++x) {
        for (uint64_t y = 0; y < height; ++y) {
            uint32_t it = 0;

            zx = 0;
            zy = 0;
            zz = 0;

            cx = offset.first + x * model->GetScaleCoeficient();
            cy = offset.second + y * model->GetScaleCoeficient();
            while ((zx * zx + zy * zy) <= 4.0 && (++it < 128)) {
                zz = zx * zx - zy * zy + cx;
                zy = 2.0 * zx * zy + cy;
                zx = zz;
            }
            canvas->At(x, y).SetColor(GetSmoothColor(it / 128.0));
        }
    }
}

}  // namespace cozz
