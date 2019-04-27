/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gpu.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 19:32:26 by rgyles            #+#    #+#             */
/*   Updated: 2019/01/30 13:19:58 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	ft_set_kernel_args(t_map *map)
{
	clSetKernelArg(map->gpu.kernel, 0, sizeof(double), &map->step);
	clSetKernelArg(map->gpu.kernel, 1, sizeof(double), &map->real_min);
	clSetKernelArg(map->gpu.kernel, 2, sizeof(double), &map->imag_min);
	clSetKernelArg(map->gpu.kernel, 3, sizeof(double), &map->c_real);
	clSetKernelArg(map->gpu.kernel, 4, sizeof(double), &map->c_imag);
	clSetKernelArg(map->gpu.kernel, 5, sizeof(int), &map->width);
	clSetKernelArg(map->gpu.kernel, 6, sizeof(int), &map->map);
	clSetKernelArg(map->gpu.kernel, 7, sizeof(int), &map->iter_limit);
	clSetKernelArg(map->gpu.kernel, 8, sizeof(int), &map->color_base_1);
	clSetKernelArg(map->gpu.kernel, 9, sizeof(int), &map->color_base_2);
	clSetKernelArg(map->gpu.kernel, 10, sizeof(int), &map->color_base_3);
	clSetKernelArg(map->gpu.kernel, 11, sizeof(cl_mem),
			(void*)&(map->gpu.img_data_buffer));
}

void		ft_gpu(t_map *map)
{
	size_t		global_item_size;

	ft_set_kernel_args(map);
	global_item_size = WIN_WIDTH * WIN_HEIGHT;
	clEnqueueNDRangeKernel(map->gpu.queue, map->gpu.kernel, 1, NULL,
			&global_item_size, NULL, 0, NULL, NULL);
	clEnqueueReadBuffer(map->gpu.queue, map->gpu.img_data_buffer, CL_TRUE, 0,
			sizeof(int) * (map->width * map->width),
			map->mlx.img.img_data, 0, NULL, NULL);
}
