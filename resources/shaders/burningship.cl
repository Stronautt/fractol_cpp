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

#include "common.h"

#include "utils.cl"

__kernel void
compute_fractal(__global unsigned int *buff, t_parameters parameters)
{
    int     it = 0;
    size_t  x = get_global_id(0);
    size_t  y = get_global_id(1);
    size_t  width = get_global_size(0);
    size_t  height = get_global_size(1);
    double3 z = (double3) 0;
    double2 c;

    c = (double2)(parameters.pivot.x + (x - width / 2.0) * parameters.scale_coefficient,
                  parameters.pivot.y + (y - height / 2.0) * parameters.scale_coefficient);
    while ((z.x * z.x + z.y * z.y) <= 4.0 && (++it < parameters.depth))
    {
        z.z = z.x * z.x - z.y * z.y + c.x;
        z.y = 2.0 * fabs(z.x * z.y) + c.y;
        z.x = z.z;
    }
    buff[y * width + x] = ft_smooth(it / (double)parameters.depth, parameters.color_coefficients);
}
