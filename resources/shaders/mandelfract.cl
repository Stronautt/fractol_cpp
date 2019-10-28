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

static inline unsigned int	ft_smooth(double it, double max_it)
{
	double	t;
	int		r;
	int		g;
	int		b;

	t = it / max_it;
	r = 9 * (1 - t) * t * t * t * 255;
	g = 15 * (1 - t) * (1 - t) * t * t * 255;
	b = 8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255;
	return (r * 0x10000 + g * 0x100 + b);
}

__kernel void
fill_mandelfract(__global int *buff, double pivot_x,
				double pivot_y, double dx, int width, int height)
{
	int				it = 0;
	int				x = get_global_id(0);
	int				y = get_global_id(1);
	double3			z = (double3) 0;
	double2			c;

	c = (double2)(pivot_x + (x - width / 2) * dx,
		pivot_y + (y - height / 2) * dx);
	while ((z.x * z.x + z.y * z.y) <= 4.0 && (++it < MAX_ITERATIONS))
	{
		z.z = z.x * z.x - z.y * z.y + c.x;
		z.y = 2 * z.x * z.y + c.y;
		z.x = z.z;
	}
	buff[y * width + x] = ft_smooth(it, MAX_ITERATIONS);
}
