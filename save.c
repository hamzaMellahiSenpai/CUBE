/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 02:31:44 by hmellahi          #+#    #+#             */
/*   Updated: 2020/10/27 00:33:24 by hmellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

extern int *g_p;

void	check_for_screenshoot(int ac, char **av)
{
	t_string	error;

	if (ac == 3)
	{
		if (ft_strcmp(av[2], "--save") == 0)
		{
			save_first_frame_in_bmp_file();
			free_all(UNCOMPLETED);
		}
		else
		{
			error = ft_strjoin("INVALID ARG ", av[2], 2);
			handle_error2(error, FAIL);
		}
	}
}

void	fill_header(unsigned char **header, int imagesize)
{
	u_int16_t bitcount;
	u_int32_t bisize;
	u_int32_t bfoffbits;
	u_int32_t filesize;
	u_int16_t biplanes;

	biplanes = 1;
	filesize = 54 + imagesize;
	bfoffbits = 54;
	bisize = 40;
	bitcount = 24;
	memset(*header, 0, 54);
	ft_memcpy(*header, "BM", 2);
	ft_memcpy(*header + 2, &filesize, 4);
	ft_memcpy(*header + 10, &bfoffbits, 4);
	ft_memcpy(*header + 14, &bisize, 4);
	ft_memcpy(*header + 18, &g_screen.width, 4);
	ft_memcpy(*header + 22, &g_screen.height, 4);
	ft_memcpy(*header + 26, &biplanes, 2);
	ft_memcpy(*header + 28, &bitcount, 2);
	ft_memcpy(*header + 34, &imagesize, 4);
}

void	fill_buf(unsigned char **buf, int width_in_bytes)
{
	int row;
	int col;
	int color;
	int i;
	int	j;

	row = g_screen.height;
	i = 0;
	while (--row > 0)
	{
		col = 0;
		j = 0;
		while (++col < g_screen.width)
		{
			color = g_p[(row * g_screen.width) + col];
			(*buf)[i * width_in_bytes + j * 3 + 0] = color & 0xff;
			(*buf)[i * width_in_bytes + j * 3 + 1] = ((color >> 8) & 0xff);
			(*buf)[i * width_in_bytes + j * 3 + 2] = ((color >> 16) & 0xff);
			j++;
		}
		i++;
	}
}

void	save_first_frame_in_bmp_file(void)
{
	int				width_in_bytes;
	u_int32_t		imagesize;
	unsigned char	*buf;
	int				fd;
	unsigned char	*header;

	width_in_bytes = ((g_screen.width * 24 + 31) / 32) * 4;
	imagesize = width_in_bytes * g_screen.height;
	header = (unsigned char *)sf_malloc((unsigned char)imagesize);
	fill_header(&header, imagesize);
	buf = sf_malloc(imagesize);
	fd = open("img.bmp", O_CREAT | O_RDWR, S_IWUSR | S_IRUSR);
	fill_buf(&buf, width_in_bytes);
	write(fd, header, 54);
	write(fd, buf, imagesize);
	close(fd);
}
