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

#ifndef FRACTOL_INCLUDE_CONTROLLERS_ALGEBRAIC_FRACTAL_HPP_
#define FRACTOL_INCLUDE_CONTROLLERS_ALGEBRAIC_FRACTAL_HPP_

#include "controller.hpp"

#include <memory>

#include "event/window_event.hpp"
#include "models/algebraic_fractal.hpp"
#include "views/algebraic_fractal.hpp"

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

class AlgebraicFractalController final : public zzgui::Controller<AlgebraicFractalModel, AlgebraicFractalView>,
                                         public std::enable_shared_from_this<AlgebraicFractalController> {
  public:
    AlgebraicFractalController(const zzgui::Application& app, std::shared_ptr<clpp::Core> cl_core,
                               std::shared_ptr<AlgebraicFractalModel> model);

    virtual void Create() override;

    void Render(float delta) override;

    bool OnWindowClose(const zzgui::WindowCloseEvent& event);

    bool OnKeyboard(const zzgui::KeyboardEvent& event);

    bool OnMouseButton(const zzgui::MouseButtonEvent& event);

    bool OnMouseMotion(const zzgui::MouseMotionEvent& event);

    bool OnMouseWheel(const zzgui::MouseWheelEvent& event);

  private:
    const zzgui::Application& app_;

    std::shared_ptr<clpp::Core> cl_core_;

    bool drag_;
};

}  // namespace cozz

#endif  // FRACTOL_INCLUDE_CONTROLLERS_ALGEBRAIC_FRACTAL_HPP_
