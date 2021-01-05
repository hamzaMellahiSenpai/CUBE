/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 03:10:00 by hmellahi          #+#    #+#             */
/*   Updated: 2020/10/31 01:18:41 by hmellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	raycast_2d(int i, int j)
{
	int			col;
	t_ray		ray;
	t_vector	a;
	t_vector	b;

	col = -1;
	a = multi_vector_to_n(PLAYERPOS, MINIMAP_SCALE);
	while (++col < g_screen.width)
	{
		ray = g_world.wall_rays[col];
		b = multi_vector_to_n(ray.wall_hit, MINIMAP_SCALE);
		line(a.x, a.y, b.x, b.y);
	}
	i = -1;
	while (++i < g_world.rows - 1)
	{
		j = -1;
		while (++j < g_world.cols - 1)
			if (!ft_strchr("0SWEN12 ", g_world.map[i][j]))
				draw_square(i, j, BLOCK_SIZE * MINIMAP_SCALE, 0x008000);
	}
}

void	draw_mini_map(void)
{
	int	i;
	int	j;

	if (g_world.show_mini_map == 1)
		return ;
	i = -1;
	while (++i < g_world.rows - 1)
	{
		j = -1;
		while (++j < g_world.cols - 1)
		{
			if (ft_strchr("12", g_world.map[i][j]))
				draw_square(i, j, BLOCK_SIZE * MINIMAP_SCALE, 0xFFFFFF);
			else if (ft_strchr("0SWEN", g_world.map[i][j]))
				draw_square(i, j, BLOCK_SIZE * MINIMAP_SCALE, 0);
		}
	}
	raycast_2d(i, j);
}

int		wall_at(t_vector coordinate)
{
	int		idx_x;
	int		idx_y;

	idx_x = coordinate.x / BLOCK_SIZE;
	idx_y = coordinate.y / BLOCK_SIZE;
	if (ft_strchr("D 1", g_world.map[idx_y][idx_x]))
		return (1);
	return (0);
}

int		object_at(t_vector coordinate)
{
	int		idx_x;
	int		idx_y;

	idx_x = coordinate.x / BLOCK_SIZE;
	idx_y = coordinate.y / BLOCK_SIZE;
	if (ft_strchr("CTPH", g_world.map[idx_y][idx_x]))
		return (1);
	return (0);
}

int		is_out_of_window(t_vector a)
{
	int	height;
	int	width;

	height = g_world.rows * BLOCK_SIZE;
	width = g_world.cols * BLOCK_SIZE;
	if (a.x <= width && a.y <= height && a.x >= 0 && a.y >= 0)
		return (0);
	return (1);
}
