/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gpu_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 18:47:29 by rgyles            #+#    #+#             */
/*   Updated: 2019/01/30 14:46:10 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>

t_gpu	ft_gpu_init(char *source_file)
{
	t_gpu		gpu;

	clGetPlatformIDs(1, &(gpu.platform), NULL);
	clGetDeviceIDs(gpu.platform, CL_DEVICE_TYPE_GPU, 1, &(gpu.device), NULL);
	gpu.context = clCreateContext(NULL, 1, &(gpu.device), NULL, NULL, NULL);
	gpu.queue = clCreateCommandQueue(gpu.context, gpu.device, 0, NULL);
	gpu.img_data_buffer = clCreateBuffer(gpu.context, CL_MEM_WRITE_ONLY,
			sizeof(int) * (WIN_WIDTH * WIN_WIDTH), NULL, NULL);
	gpu.program = clCreateProgramWithSource(gpu.context, 1,
			(const char **)&source_file, NULL, NULL);
	clBuildProgram(gpu.program, 0, NULL, NULL, NULL, NULL);
	gpu.kernel = clCreateKernel(gpu.program, "gpu", NULL);
	free(source_file);
	return (gpu);
}
