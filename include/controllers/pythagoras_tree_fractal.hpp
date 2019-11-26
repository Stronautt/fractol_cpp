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

#ifndef FRACTOL_INCLUDE_CONTROLLERS_PYTHAGORAS_TREE_FRACTAL_HPP_
#define FRACTOL_INCLUDE_CONTROLLERS_PYTHAGORAS_TREE_FRACTAL_HPP_

#include "controller.hpp"

#include <memory>

#include "event/window_event.hpp"
#include "models/pythagoras_tree_fractal.hpp"
#include "views/pythagoras_tree_fractal.hpp"

namespace cozz {

namespace zzgui {

class Application;
class KeyboardEvent;
class MouseButtonEvent;
class MouseMotionEvent;
class MouseWheelEvent;

}  // namespace zzgui

namespace clpp {

class Core;

}  // namespace clpp

class PythagorasTreeFractalController final
    : public zzgui::Controller<PythagorasTreeFractalModel, PythagorasTreeFractalView> {
  public:
    PythagorasTreeFractalController(std::shared_ptr<PythagorasTreeFractalModel> model);

    virtual void Create() override;

    bool OnWindowClose(const zzgui::WindowCloseEvent& event);
};

}  // namespace cozz

#endif  // FRACTOL_INCLUDE_CONTROLLERS_PYTHAGORAS_TREE_FRACTAL_HPP_
