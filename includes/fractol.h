/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 10:16:40 by rgyles            #+#    #+#             */
/*   Updated: 2019/04/27 18:54:07 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <fcntl.h>
# include <math.h>
# include <OpenCl/cl.h>
# include "../libft/libft.h"
# include "../minilibx_macos/mlx.h"

# define WIN_WIDTH 1200
# define WIN_HEIGHT 1200
# define BUFF_SIZE 4096
# define WIN_WIDTH_MID WIN_WIDTH / 2
# define WIN_HEIGHT_MID WIN_HEIGHT / 2
# define ABS(Value) ((Value) < 0 ? -(Value) : (Value))

typedef struct	s_img
{
	void		*img_ptr;
	int			*img_data;
	int			bpp;
	int			size_line;
	int			endian;
}				t_img;

typedef struct	s_mlx
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_img		img;
}				t_mlx;

typedef struct	s_gpu
{
	cl_platform_id		platform;
	cl_device_id		device;
	cl_context			context;
	cl_command_queue	queue;
	cl_program			program;
	cl_kernel			kernel;
	cl_mem				img_data_buffer;
}				t_gpu;

typedef struct	s_map
{
	int			map;
	int			iter_limit;
	int			g_force;
	int			color_base_1;
	int			color_base_2;
	int			color_base_3;
	int			width;
	int			mouse_x;
	int			mouse_y;
	int			mouse_click;
	double		real_min;
	double		real_max;
	double		imag_min;
	double		imag_max;
	double		step;
	double		c_real;
	double		c_imag;
	t_mlx		mlx;
	t_gpu		gpu;
}				t_map;

void			ft_create_image(t_map *map);
int				ft_key_press(int key, t_map *map);
int				ft_mouse_press(int button, int x, int y, t_map *map);
int				ft_mouse_release(int button, int x, int y, t_map *map);
int				ft_mouse_movement(int x, int y, t_map *map);
char			*ft_get_source_file(char *file_name);
t_gpu			ft_gpu_init(char *source_file);
void			ft_mandelbrot(t_map *map);
void			ft_gpu(t_map *map);
void			ft_julia(t_map *map);
void			ft_tricorn(t_map *map);
void			ft_burning_ship(t_map *map);

#endif
