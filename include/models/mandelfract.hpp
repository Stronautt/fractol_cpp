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

#ifndef FRACTOL_INCLUDE_MODELS_MANDELFRACT_HPP_
#define FRACTOL_INCLUDE_MODELS_MANDELFRACT_HPP_

#include "model.hpp"

#include <memory>
#include <vector>

#include "event_handler.hpp"

namespace cozz {

class MandelfractController;

namespace zzgui {

class Window;
class WidgetsManager;
class Label;

}  // namespace zzgui

class MandelfractModel final : public zzgui::Model<MandelfractController> {
  public:
    ~MandelfractModel();

    virtual void Create() override;

    virtual void Update(float delta) override;

    void SetScaleCoeficient(double value);

    void IncScaleCoeficient(double value);

    void SetOffset(double offset_x, double offset_y);

    void Shift(double offset_x, double offset_y);

    std::weak_ptr<zzgui::Window> GetWindow() const;

    std::weak_ptr<zzgui::WidgetsManager> GetWidgetsManager() const;

    double GetScaleCoeficient() const;

    std::pair<double, double> GetOffset() const;

  private:
    std::weak_ptr<zzgui::Window> window_;

    std::shared_ptr<zzgui::WidgetsManager> widgets_manager_;

    std::shared_ptr<zzgui::Label> fps_counter_;

    std::list<zzgui::EventHandler::HandlerID> registered_callbacks_;

    double scale_coefficient_;
    std::pair<double, double> offset_;
};

}  // namespace cozz

#endif  // FRACTOL_INCLUDE_MODELS_MANDELFRACT_HPP_
