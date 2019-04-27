/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mandelbrot.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 11:05:20 by rgyles            #+#    #+#             */
/*   Updated: 2019/01/30 13:59:21 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int		ft_get_z(double init_real, double init_imag, t_map *map)
{
	int		z;
	double	real;
	double	tmp_real;
	double	imag;

	z = -1;
	real = init_real;
	imag = init_imag;
	while (++z < map->iter_limit)
	{
		tmp_real = real;
		real = real * real - imag * imag + init_real;
		imag = 2 * tmp_real * imag + init_imag;
		if (ABS(real + imag) > 4)
			break ;
	}
	return (z);
}

void			ft_mandelbrot(t_map *map)
{
	int		x;
	int		y;
	int		z;
	double	i;
	double	r;

	x = -1;
	r = map->real_min;
	while (++x < WIN_WIDTH)
	{
		y = -1;
		i = map->imag_min;
		while (++y < WIN_HEIGHT)
		{
			z = ft_get_z(r, i, map);
			if (z == map->iter_limit)
				map->mlx.img.img_data[x + y * WIN_WIDTH] = 0x0;
			else
				map->mlx.img.img_data[x + y * WIN_WIDTH] = 0xF00000 >> z;
			i += map->step;
		}
		r += map->step;
	}
	return ;
}
