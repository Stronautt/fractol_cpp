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

#ifndef FRACTOL_INCLUDE_VIEWS_PYTHAGORAS_TREE_FRACTAL_HPP_
#define FRACTOL_INCLUDE_VIEWS_PYTHAGORAS_TREE_FRACTAL_HPP_

#include "view.hpp"

#include <memory>

#include "canvas.hpp"

namespace cozz {

class PythagorasTreeFractalModel;
class PythagorasTreeFractalController;

namespace zzgui {

class Window;
class Painter;

}  // namespace zzgui

class PythagorasTreeFractalView final
    : public zzgui::View<PythagorasTreeFractalModel, PythagorasTreeFractalController> {
  public:
    PythagorasTreeFractalView(std::weak_ptr<PythagorasTreeFractalModel> model);

    virtual void Create() override;

    virtual void Render(float delta) override;

    virtual void Resized(std::weak_ptr<zzgui::Window> window) override;

    virtual void Show() override;

    virtual void Pause() override;

    virtual void Resume() override;

    virtual void Hide() override;

  private:
    std::shared_ptr<zzgui::Painter> painter_;

    void DrawFractal(std::shared_ptr<zzgui::Canvas> canvas, zzgui::Canvas::Point a, zzgui::Canvas::Point b,
                     int32_t depth) const;
};

}  // namespace cozz

#endif  // FRACTOL_INCLUDE_VIEWS_PYTHAGORAS_TREE_FRACTAL_HPP_
