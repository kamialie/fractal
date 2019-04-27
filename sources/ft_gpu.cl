# define ABS(Value) ((Value) < 0 ? -(Value) : (Value))

int				ft_get_color(int start, int end, double percent);

int				ft_get_color(int start, int end, double percent)
{
	return ((int)((1 - percent) * start + percent * end));
}

int				ft_gradient(int z, int iter_limit, int up_color, int bot_color, int base_color);

int				ft_gradient(int z, int iter_limit, int up_color, int bot_color, int base_color)
{
	int		red;
	int		blue;
	int		green;
	double	percent;

	if (z < iter_limit / 3)
	{
		percent = z / (double)(iter_limit / 3);
		red = ft_get_color((base_color >> 16) & 0xFF, (up_color >> 16) & 0xFF, percent);
		green = ft_get_color((base_color >> 8) & 0xFF, (up_color >> 8) & 0xFF, percent);
		blue = ft_get_color(base_color & 0xFF, up_color & 0xFF, percent);
	}
	else if (z > (iter_limit * 2 / 3))
	{
		percent = (z * 2 / 3) / (double)(iter_limit * 2 / 3);
		red = ft_get_color((bot_color >> 16) & 0xFF, (0x0 >> 16) & 0xFF, percent);
		green = ft_get_color((bot_color >> 8) & 0xFF, (0x0 >> 8) & 0xFF, percent);
		blue = ft_get_color(bot_color & 0xFF, 0x0 & 0xFF, percent);
	}
	else
	{
		percent = z / (double)(iter_limit / 3);
		red = ft_get_color((up_color >> 16) & 0xFF, (bot_color >> 16) & 0xFF, percent);
		green = ft_get_color((up_color >> 8) & 0xFF, (bot_color >> 8) & 0xFF, percent);
		blue = ft_get_color(up_color & 0xFF, bot_color & 0xFF, percent);
	}
	return ((red << 16) | (green << 8) | blue);
}


__kernel void	gpu(double step,
								double real_min,
								double imag_min,
								double c_real,
								double c_imag,
								int win_width,
								int	map,
								int	iter_limit,
								int	color_base_1,
								int color_base_2,
								int color_base_3,
								__global int *img_data)
{
	int	z;
	double c_r;
	double c_i;
	double real;
	double imag;
	double tmp_real;

	int	id = get_global_id(0);
	int x = id % win_width;
	int	y = id / win_width;

	z = 0;
	c_r = x * step + real_min;
	c_i  = y * step + imag_min;
	real = c_r;
	imag = c_i;
	if (map == 0)
	{
		while (++z < iter_limit)
		{
			tmp_real = real;
			real = real * real - imag * imag + c_r;
			imag = 2 * tmp_real * imag + c_i;
			if (ABS(real + imag) > 4)
				break ;
		}
		if (z == iter_limit)
			img_data[id] = 0x0;
		else
			img_data[id] = ft_gradient(z, iter_limit, color_base_1, color_base_2, color_base_3);
	}
	else if (map == 1)
	{
		while (++z < iter_limit)
		{
			tmp_real = real;
			real = real * real - imag * imag + c_real;
			imag = 2 * tmp_real * imag + c_imag;
			if (ABS(real + imag) > 4)
				break ;
		}
		if (z == iter_limit)
			img_data[id] = 0xFFCC66;
		else
			img_data[id] = ft_gradient(z, iter_limit, color_base_1, color_base_2, color_base_3);
	}
	else if (map == 2)
	{
		while (++z < iter_limit)
		{
			tmp_real = real;
			real = fabs(real * real - imag * imag + c_r);
			imag = fabs(2 * tmp_real * imag + c_i);
			if (ABS(real + imag) > 4)
				break ;
		}
		if (z == iter_limit)
			img_data[id] = 0x0;
		else
			img_data[id] = ft_gradient(z, iter_limit, color_base_1, color_base_2, color_base_3);
	}
	else if (map == 3)
	{
		while (++z < iter_limit)
		{
			tmp_real = real;
			real = real * real - imag * imag + c_r;
			imag = -2 * tmp_real * imag + c_i;
			if (ABS(real + imag) > 4)
				break ;
		}
		if (z == iter_limit)
			img_data[id] = 0xFFCC66;
		else
			img_data[id] = ft_gradient(z, iter_limit, color_base_1, color_base_2, color_base_3);
	}
}
