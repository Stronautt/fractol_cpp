/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelfract.cl                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 22:01:23 by pgritsen          #+#    #+#             */
/*   Updated: 2017/12/29 14:30:22 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma OPENCL EXTENSION cl_khr_fp64 : enable

#define MAX_ITERATIONS 256

typedef struct s_color_coefficient
{
    double r;
    double g;
    double b;
}              t_color_coefficient;

typedef struct s_parameters {
    double scale_coefficient;
    double pivot_x;
    double pivot_y;
    t_color_coefficient color_coefficients;
}             t_parameters;

static inline unsigned int  ft_smooth(double t, t_color_coefficient color_coefficients)
{
    int     r;
    int     g;
    int     b;

    r = color_coefficients.r * (1 - t) * t * t * t * 255;
    g = color_coefficients.g * (1 - t) * (1 - t) * t * t * 255;
    b = color_coefficients.b * (1 - t) * (1 - t) * (1 - t) * t * 255;
    return (r * 0x10000 + g * 0x100 + b);
}

__kernel void
fill_mandelfract(__global unsigned int *buff, t_parameters parameters)
{
    int             it = 0;
    int             x = get_global_id(0);
    int             y = get_global_id(1);
    unsigned long   width = get_global_size(0);
    unsigned long   height = get_global_size(1);
    double3         z = (double3) 0;
    double2         c;

    c = (double2)(parameters.pivot_x + (x - width / 2.0) * parameters.scale_coefficient,
        parameters.pivot_y + (y - height / 2.0) * parameters.scale_coefficient);
    while ((z.x * z.x + z.y * z.y) <= 4.0 && (++it < MAX_ITERATIONS))
    {
        z.z = z.x * z.x - z.y * z.y + c.x;
        z.y = 2 * z.x * z.y + c.y;
        z.x = z.z;
    }
    buff[y * width + x] = ft_smooth(it / (double)MAX_ITERATIONS, parameters.color_coefficients);
}
