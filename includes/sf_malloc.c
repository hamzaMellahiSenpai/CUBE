/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sf_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 22:16:31 by hmellahi          #+#    #+#             */
/*   Updated: 2020/10/31 01:26:49 by hmellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	*sf_malloc(size_t size)
{
	void	*ptr;

	if (!(ptr = malloc(size)))
		(handle_error(Allocation_Failed, FAIL));
	new_lst(ptr);
	return (ptr);
}

void	free_all(int status)
{
	if (g_world.is_bc_music_played)
		system(ft_strjoin("kill ", ft_itoa(g_world.bc_music_pid), 2));
	deletelist(&g_world.adresses);
	exit(status);
}

void	*sf_realloc(void *ptr, size_t size)
{
	if (!(ptr = realloc(ptr, size)))
		(handle_error(Allocation_Failed, FAIL));
	new_lst(ptr);
	return (ptr);
}

void	draw_square(float row, float col, float grid_size, float color)
{
	float y;
	float max_y;
	float max_x;
	float x;

	max_x = col * grid_size + grid_size;
	max_y = row * grid_size + grid_size;
	y = row * grid_size;
	while (y < max_y)
	{
		x = grid_size * col;
		while (x < max_x)
			put_pixel(new_vector(x++, y), color);
		y++;
	}
}

void	draw_img(t_image img)
{
	float	f;
	float	y;
	float	z;
	float	x;
	int		color;

	img.stepy = (float)img.height / (float)img.size.y;
	img.stepx = (float)img.width / (float)img.size.x;
	y = img.y - 1;
	f = img.f;
	while (++y < img.endy)
	{
		x = img.x - 1;
		z = img.z;
		while (++x < img.endx)
		{
			if ((img.endz != 0 && z >= img.endz))
				break ;
			color = img.data[(int)f * img.width + (int)z];
			if (color != 0)
				put_pixel(new_vector(x, y), color);
			z += img.stepx;
		}
		f += img.stepy;
	}
}
