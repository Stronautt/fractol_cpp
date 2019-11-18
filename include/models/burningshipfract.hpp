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

#ifndef FRACTOL_INCLUDE_MODELS_BURNINGSHIPFRACT_HPP_
#define FRACTOL_INCLUDE_MODELS_BURNINGSHIPFRACT_HPP_

#include "models/algebraic_fractal.hpp"

namespace cozz {

class BurningshipfractModel final : public AlgebraicFractalModel {
  public:
    BurningshipfractModel(std::shared_ptr<clpp::Core> cl_core, std::shared_ptr<const clpp::Platform> cl_platform,
                          std::shared_ptr<const clpp::Device> cl_device);
};

}  // namespace cozz

#endif  // FRACTOL_INCLUDE_MODELS_BURNINGSHIPFRACT_HPP_
