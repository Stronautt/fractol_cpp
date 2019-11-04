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

#ifndef COMMON_H
#define COMMON_H

#pragma OPENCL EXTENSION cl_khr_fp64 : enable

#define MAX_ITERATIONS 256

typedef struct s_2d_point {
    double x;
    double y;
} t_2d_point;

typedef struct s_color_coefficient {
    float r;
    float g;
    float b;
} t_color_coefficient;

typedef struct s_parameters {
    unsigned short depth;
    double scale_coefficient;
    t_2d_point pivot;
    t_2d_point c;
    t_color_coefficient color_coefficients;
} t_parameters;

#endif
