/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mouse_press.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 13:06:12 by rgyles            #+#    #+#             */
/*   Updated: 2019/01/30 13:15:12 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>

static void	ft_mouse_zoom(int x, int y, t_map *map, double zoom)
{
	double	dif_y;
	double	dif_x;

	dif_x = (1 - zoom) * (x * map->step + map->real_min);
	dif_y = (1 - zoom) * (y * map->step + map->imag_min);
	map->imag_min = map->imag_min * zoom + dif_y;
	map->imag_max = map->imag_max * zoom + dif_y;
	map->real_min = map->real_min * zoom + dif_x;
	map->real_max = map->real_max * zoom + dif_x;
	map->step *= zoom;
}

int			ft_mouse_movement(int x, int y, t_map *map)
{
	if (x <= 0 || x >= WIN_WIDTH || y <= 0 || y >= WIN_HEIGHT)
		return (0);
	if (map->mouse_click == 1)
	{
		map->c_real = x * (2.0 / WIN_WIDTH) - 1.0;
		map->c_imag = y * (2.0 / WIN_HEIGHT) - 1.0;
	}
	else if (map->mouse_click == 2)
	{
		x -= WIN_WIDTH_MID;
		y -= WIN_WIDTH_MID;
		map->imag_max = map->imag_max - (y - map->mouse_y) * map->step;
		map->imag_min = map->imag_min - (y - map->mouse_y) * map->step;
		map->real_max = map->real_max - (x - map->mouse_x) * map->step;
		map->real_min = map->real_min - (x - map->mouse_x) * map->step;
		map->mouse_x = x;
		map->mouse_y = y;
	}
	ft_create_image(map);
	return (0);
}

int			ft_mouse_release(int button, int x, int y, t_map *map)
{
	(void)x;
	(void)y;
	if (button == 1)
		map->mouse_click = 0;
	if (button == 2)
		map->mouse_click = 0;
	return (0);
}

int			ft_mouse_press(int button, int x, int y, t_map *map)
{
	if (button == 5)
		ft_mouse_zoom(x, y, map, 0.8);
	else if (button == 4)
		ft_mouse_zoom(x, y, map, 1.25);
	else if (button == 1)
	{
		if (map->map != 1)
			return (0);
		map->mouse_click = 1;
	}
	else if (button == 2)
	{
		map->mouse_x = x - WIN_WIDTH_MID;
		map->mouse_y = y - WIN_WIDTH_MID;
		map->mouse_click = 2;
	}
	ft_create_image(map);
	return (0);
}
