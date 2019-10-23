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

#ifndef FRACTOL_INCLUDE_CONTROLLERS_MANDELFRACT_HPP_
#define FRACTOL_INCLUDE_CONTROLLERS_MANDELFRACT_HPP_

#include "controller.hpp"

#include "event/window_event.hpp"

namespace cozz {

class MandelfractModel;
class MandelfractView;

namespace zzgui {

class MouseWheelEvent;
class KeyboardEvent;

}  // namespace zzgui

class MandelfractController final : public zzgui::Controller<MandelfractModel, MandelfractView>,
                                    public std::enable_shared_from_this<MandelfractController> {
  public:
    MandelfractController();

    virtual void Create() override;

    void OnWindowClose(const zzgui::WindowCloseEvent& event);

    void OnKeyboard(const zzgui::KeyboardEvent& event);

    void OnMouseWheel(const zzgui::MouseWheelEvent& event);
};

}  // namespace cozz

#endif  // FRACTOL_INCLUDE_CONTROLLERS_MANDELFRACT_HPP_
