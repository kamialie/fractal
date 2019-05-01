/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 10:12:05 by rgyles            #+#    #+#             */
/*   Updated: 2019/05/01 13:03:37 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static t_mlx	ft_init_mlx(void)
{
	t_mlx	mlx;

	mlx.mlx_ptr = mlx_init();
	mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "fractol");
	mlx.img.img_ptr = mlx_new_image(mlx.mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	mlx.img.img_data = (int *)mlx_get_data_addr(mlx.img.img_ptr,
		&mlx.img.bpp, &mlx.img.size_line, &mlx.img.endian);
	return (mlx);
}

static t_map	*ft_init_map(void)
{
	t_map *map;

	map = (t_map *)malloc(sizeof(*map));
	map->width = 1200;
	map->iter_limit = 100;
	map->g_force = 0;
	map->color_base_1 = 0xFF0000;
	map->color_base_2 = 0x00FF00;
	map->color_base_3 = 0x0000FF;
	map->mouse_x = 0;
	map->mouse_y = 0;
	map->mouse_click = 0;
	map->imag_min = -2.5;
	map->imag_max = 2.5;
	map->real_min = -2.5;
	map->real_max = 2.5;
	map->c_real = 0.8;
	map->c_imag = 0.156;
	map->step = (map->imag_max - map->imag_min) / WIN_WIDTH;
	map->mlx = ft_init_mlx();
	map->gpu = ft_gpu_init(ft_get_source_file("sources/ft_gpu.cl"));
	return (map);
}

static void		ft_allocator(char *input, t_map *map)
{
	if (ft_strcmp("mandelbrot", input) == 0)
		map->map = 0;
	else if (ft_strcmp("julia", input) == 0)
		map->map = 1;
	else if (ft_strcmp("burning_ship", input) == 0)
		map->map = 2;
	else if (ft_strcmp("tricorn", input) == 0)
		map->map = 3;
	else
	{
		ft_putstr("usage: ./fractal [mandelbrot/julia/burning_ship/tricorn]\n");
		exit(0);
	}
}

int				main(int args, char *argv[])
{
	t_map	*map;

	if (args != 2)
		ft_putstr("usage: ./fractal [mandelbrot/julia/burning_ship/tricorn]\n");
	else
	{
		map = ft_init_map();
		ft_allocator(argv[1], map);
		ft_create_image(map);
		mlx_hook(map->mlx.win_ptr, 2, 0, &ft_key_press, map);
		mlx_hook(map->mlx.win_ptr, 4, 0, &ft_mouse_press, map);
		mlx_hook(map->mlx.win_ptr, 5, 0, &ft_mouse_release, map);
		mlx_hook(map->mlx.win_ptr, 6, 0, &ft_mouse_movement, map);
		mlx_loop(map->mlx.mlx_ptr);
	}
	return (0);
}
