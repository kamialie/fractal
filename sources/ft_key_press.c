/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_press.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 13:03:55 by rgyles            #+#    #+#             */
/*   Updated: 2019/01/30 15:10:55 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	ft_move_key(int key, t_map *map)
{
	if (key == 126)
	{
		map->imag_max += map->step * 10;
		map->imag_min += map->step * 10;
	}
	else if (key == 125)
	{
		map->imag_max -= map->step * 10;
		map->imag_min -= map->step * 10;
	}
	else if (key == 123)
	{
		map->real_max += map->step * 10;
		map->real_min += map->step * 10;
	}
	else
	{
		map->real_max -= map->step * 10;
		map->real_min -= map->step * 10;
	}
}

static void	ft_init_values(t_map *map)
{
	map->imag_min = -2.5;
	map->imag_max = 2.5;
	map->real_min = -2.5;
	map->real_max = 2.5;
	map->c_real = 0.8;
	map->c_imag = 0.156;
	map->iter_limit = 100;
	map->step = (map->imag_max - map->imag_min) / WIN_WIDTH;
}

static void	ft_color_set(int key, t_map *map)
{
	if (key == 19)
	{
		map->color_base_1 = 0x0000FF;
		map->color_base_2 = 0x00FF00;
		map->color_base_3 = 0xFF0000;
	}
	else if (key == 20)
	{
		map->color_base_1 = 0xFF0000;
		map->color_base_2 = 0x00FF00;
		map->color_base_3 = 0x0000FF;
	}
	else if (key == 1)
	{
		map->color_base_1 = 0xFF0000;
		map->color_base_2 = 0xFFFF00;
		map->color_base_3 = 0x0;
	}
	else if (key == 46)
	{
		map->color_base_1 = 0x006700;
		map->color_base_2 = 0x00FF00;
		map->color_base_3 = 0x0;
	}
}

int			ft_key_press(int key, t_map *map)
{
	if (key == 53)
	{
		clReleaseMemObject(map->gpu.img_data_buffer);
		clReleaseKernel(map->gpu.kernel);
		clReleaseContext(map->gpu.context);
		exit(0);
	}
	if (key == 126 || key == 125 || key == 123 || key == 124)
		ft_move_key(key, map);
	else if (key == 18)
		ft_init_values(map);
	else if (key == 5)
		map->g_force = map->g_force / 1 ? 0 : 1;
	else if (key == 24)
		map->iter_limit += 10;
	else if (key == 27)
		map->iter_limit -= 10;
	else if (key == 19 || key == 20 || key == 1 || key == 46)
		ft_color_set(key, map);
	else
		return (0);
	ft_create_image(map);
	return (0);
}
