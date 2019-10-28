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
#include "models/mandelfract.hpp"
#include "painter.hpp"
#include "resources/font_resource.hpp"
#include "resources_manager.hpp"
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

}  // namespace cozz
