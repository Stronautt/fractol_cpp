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

#include "models/mandelfract.hpp"

#include "controllers/algebraic_fractal.hpp"
#include "views/algebraic_fractal.hpp"

namespace cozz {

MandelfractModel::MandelfractModel(std::shared_ptr<clpp::Core> cl_core)
    : AlgebraicFractalModel("Mandelbrot Fractal", cl_core, {512, 0.004, {-0.5, 0}, {0, 0}, {9, 15, 8.5}},
                            {"resources/shaders/mandelbrot.cl"}) {}

}  // namespace cozz
