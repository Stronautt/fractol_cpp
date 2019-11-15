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

unsigned int ft_smooth(double t, t_color_coefficient color_coefficients)
{
    int     r;
    int     g;
    int     b;

    r = color_coefficients.r * (1.0 - t) * t * t * t * 255.0;
    g = color_coefficients.g * (1.0 - t) * (1.0 - t) * t * t * 255.0;
    b = color_coefficients.b * (1.0 - t) * (1.0 - t) * (1.0 - t) * t * 255.0;
    return (0xFF000000 + r * 0x10000 + g * 0x100 + b);
}
