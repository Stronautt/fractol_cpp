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

#ifndef FRACTOL_INCLUDE_MODELS_PYTHAGORAS_TREE_FRACTAL_HPP_
#define FRACTOL_INCLUDE_MODELS_PYTHAGORAS_TREE_FRACTAL_HPP_

#include "model.hpp"

namespace cozz {

class PythagorasTreeFractalController;

namespace zzgui {

class Window;
class WidgetsManager;
class Label;

}  // namespace zzgui

class PythagorasTreeFractalModel : public zzgui::Model<PythagorasTreeFractalController> {
  public:
    PythagorasTreeFractalModel();

    virtual void Create() override;

    virtual void Update(float delta) override;

    void Grow(int32_t value);

    void IncSideLength(int32_t value);

    std::weak_ptr<zzgui::Window> GetWindow() const;

    std::weak_ptr<zzgui::WidgetsManager> GetWidgetsManager() const;

    uint32_t GetSideLength() const;

    uint32_t GetDepth() const;

  private:
    static constexpr uint32_t kMinSideLength = 5;
    static constexpr uint32_t kMaxSideLength = 150;

    static constexpr uint32_t kMinDepth = 1;
    static constexpr uint32_t kMaxDepth = 15;

    std::weak_ptr<zzgui::Window> window_;

    std::shared_ptr<zzgui::WidgetsManager> widgets_manager_;

    std::weak_ptr<zzgui::Label> fps_counter_;

    uint32_t side_length_;
    uint32_t depth_;
};

}  // namespace cozz

#endif  // FRACTOL_INCLUDE_MODELS_PYTHAGORAS_TREE_FRACTAL_HPP_
