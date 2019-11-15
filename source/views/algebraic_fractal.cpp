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

#include "views/algebraic_fractal.hpp"

#include "controllers/algebraic_fractal.hpp"
#include "models/algebraic_fractal.hpp"
#include "painter.hpp"
#include "resources/font_resource.hpp"
#include "resources_manager.hpp"
#include "widget.hpp"
#include "widgets/label.hpp"
#include "widgets_manager.hpp"
#include "window.hpp"

namespace cozz {

AlgebraicFractalView::AlgebraicFractalView(std::weak_ptr<AlgebraicFractalModel> model) : View(model) {}

void AlgebraicFractalView::Create() {
    auto model = GetModel().lock();
    Resized(model->GetWindow());
}

void AlgebraicFractalView::Render(float /*delta*/) {
    auto model = GetModel().lock();
    auto window = model->GetWindow().lock();
    auto canvas = window->GetCanvas().lock();

    const auto widgets_manager = model->GetWidgetsManager().lock();
    for (const auto& widget : widgets_manager->GetWidgets()) {
        widget.second->Draw(painter_);
    }
}

void AlgebraicFractalView::Resized(std::weak_ptr<zzgui::Window> window) {
    const auto window_ptr = window.lock();

    if (window_ptr) {
        painter_ = std::make_shared<zzgui::Painter>(window_ptr->GetCanvas());
    }
}

void AlgebraicFractalView::Show() {}

void AlgebraicFractalView::Pause() {}

void AlgebraicFractalView::Resume() {}

void AlgebraicFractalView::Hide() {}

}  // namespace cozz
