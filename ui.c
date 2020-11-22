/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 03:13:31 by hmellahi          #+#    #+#             */
/*   Updated: 2020/03/08 14:13:36 by hmellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void		text(char *str, int x, int y, int color)
{
	mlx_string_put(g_mlx, g_window, x, y, color, str);
}

float		deg_to_rad(int angle)
{
	return (angle * M_PI / 180);
}

void		background(int color)
{
	int i;
	int j;

	i = -1;
	while (++i < g_screen.height)
	{
		j = 0;
		while (j < g_screen.width)
			put_pixel(new_vector(j++, i), color);
	}
}

void		direct_line(int x, int start, int end, int color)
{
	while (++start <= end)
		put_pixel(new_vector(x, start), color);
}
