/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_source_file.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 14:44:50 by rgyles            #+#    #+#             */
/*   Updated: 2019/01/29 19:54:03 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

char	*ft_get_source_file(char *file_name)
{
	int		fd;
	int		ret;
	char	buf[BUFF_SIZE + 1];
	char	*source_str;

	fd = open(file_name, O_RDONLY);
	ret = read(fd, buf, BUFF_SIZE);
	buf[ret] = '\0';
	source_str = ft_strdup(buf);
	close(fd);
	return (source_str);
}
