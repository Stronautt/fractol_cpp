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

#ifndef FRACTOL_INCLUDE_MODELS_ALGEBRAIC_FRACTAL_HPP_
#define FRACTOL_INCLUDE_MODELS_ALGEBRAIC_FRACTAL_HPP_

#include "model.hpp"

#include <memory>
#include <vector>

#include "event_handler.hpp"

namespace cozz {

class AlgebraicFractalController;

namespace zzgui {

class Window;
class MouseMotionEvent;
class WidgetsManager;
class Label;

}  // namespace zzgui

namespace clpp {

class Core;
class Shader;
class Platform;

}  // namespace clpp

class AlgebraicFractalModel : public zzgui::Model<AlgebraicFractalController> {
  public:
    struct Parameters {
        struct s_2d_point {
            double x;
            double y;
        };
        struct s_color_coefficients {
            float r;
            float g;
            float b;
        };

        uint16_t depth;
        double scale_coefficient;
        s_2d_point pivot;
        s_2d_point c;
        s_color_coefficients color_coefficients;
    };

    ~AlgebraicFractalModel();

    virtual void Create() override;

    virtual void Update(float delta) override;

    void IncScaleCoeficient(double value);

    void Drag(double x_dir, double y_dir);

    void Move(double mult_x, double mult_y);

    void Zoom(bool in);

    void Zoom(uint64_t x, uint64_t y, bool in);

    void IncDepth(uint16_t value);

    void RandomizeColor();

    void FollowMouse(uint64_t x, uint64_t y);

    void ToogleMouseFollowing();

    std::weak_ptr<zzgui::Window> GetWindow() const;

    std::weak_ptr<zzgui::WidgetsManager> GetWidgetsManager() const;

  protected:
    AlgebraicFractalModel(const std::string& name, std::shared_ptr<clpp::Core> cl_core,
                          std::shared_ptr<clpp::Platform> cl_platform, Parameters parameters,
                          const std::vector<std::string>& source_paths);

  private:
    constexpr static double kAmplification = 32.0;

    std::string name_;

    std::shared_ptr<clpp::Core> cl_core_;

    std::shared_ptr<clpp::Platform> cl_platform_;

    Parameters parameters_;

    const std::vector<std::string> source_paths_;

    std::shared_ptr<clpp::Shader> cl_shader_;

    std::weak_ptr<zzgui::Window> window_;

    std::shared_ptr<zzgui::WidgetsManager> widgets_manager_;

    struct {
        std::weak_ptr<zzgui::Label> depth;
        std::weak_ptr<zzgui::Label> scale_coefficient;
        std::weak_ptr<zzgui::Label> pivot;
        std::weak_ptr<zzgui::Label> dynamic_coefficients;
    } fractal_info_;

    std::weak_ptr<zzgui::Label> fps_counter_;

    std::list<zzgui::EventHandler::HandlerID> registered_callbacks_;

    bool follow_mouse_;
};

}  // namespace cozz

#endif  // FRACTOL_INCLUDE_MODELS_ALGEBRAIC_FRACTAL_HPP_
