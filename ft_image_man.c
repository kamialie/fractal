/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_image_man.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 11:17:38 by rgyles            #+#    #+#             */
/*   Updated: 2019/01/30 15:06:48 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void		ft_set_instructions(t_map *map)
{
	mlx_string_put(map->mlx.mlx_ptr, map->mlx.win_ptr,
		20, 20, 0xFFFFFF, "zoom in/out:   scrol up/down");
	mlx_string_put(map->mlx.mlx_ptr, map->mlx.win_ptr,
		20, 40, 0xFFFFFF, "g_force:       g");
	mlx_string_put(map->mlx.mlx_ptr, map->mlx.win_ptr,
		20, 60, 0xFFFFFF, "matrix_theme:  m");
	mlx_string_put(map->mlx.mlx_ptr, map->mlx.win_ptr,
		20, 80, 0xFFFFFF, "saruman_theme: s");
	mlx_string_put(map->mlx.mlx_ptr, map->mlx.win_ptr,
		20, 100, 0xFFFFFF, "color_base:    2/3");
	mlx_string_put(map->mlx.mlx_ptr, map->mlx.win_ptr,
		400, 20, 0xFFFFFF,
		"move fractal around:    arrows or keep mouse right button pressed");
	mlx_string_put(map->mlx.mlx_ptr, map->mlx.win_ptr,
		400, 40, 0xFFFFFF,
		"change julia constants: keep mouse left button pressed");
	mlx_string_put(map->mlx.mlx_ptr, map->mlx.win_ptr,
		400, 60, 0xFFFFFF, "more/less iterations:   = / -");
	mlx_string_put(map->mlx.mlx_ptr, map->mlx.win_ptr,
		400, 80, 0xFFFFFF, "return default:         1");
}

void			ft_create_image(t_map *map)
{
	mlx_clear_window(map->mlx.mlx_ptr, map->mlx.win_ptr);
	if (map->g_force == 1)
		ft_gpu(map);
	else if (map->map == 0)
		ft_mandelbrot(map);
	else if (map->map == 1)
		ft_julia(map);
	else if (map->map == 2)
		ft_burning_ship(map);
	else if (map->map == 3)
		ft_tricorn(map);
	mlx_put_image_to_window(map->mlx.mlx_ptr,
		map->mlx.win_ptr, map->mlx.img.img_ptr, 0, 0);
	ft_set_instructions(map);
}
