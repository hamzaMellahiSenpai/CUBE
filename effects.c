/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   effects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 02:12:08 by hmellahi          #+#    #+#             */
/*   Updated: 2020/10/30 03:18:38 by hmellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		shadow(int color, float distance)
{
	int		r;
	int		g;
	int		b;
	float	fact;

	fact = 256 / distance;
	b = (color & 0xff) * fact;
	b = b > (color & 0x0000ff) ? (color & 0xff) : b;
	color = color >> 8;
	g = (color & 0xff) * fact;
	g = g > (color & 0xff) ? (color & 0xff) : g;
	color = color >> 8;
	r = (color & 0xff) * fact;
	r = r > (color & 0xff) ? (color & 0xff) : r;
	return (rgb_to_int(r, g, b));
}

void	update_sprite_frames(void)
{
	int	i;

	i = -1;
	while (++i < g_world.numofsprites)
	{
		if (g_world.sprites[i].visible && g_world.sprites[i].anim.is_running)
		{
			g_world.sprites[i].anim.currentframe++;
			if (g_world.sprites[i].anim.currentframe ==
			g_world.sprites[i].anim.nofframes)
				g_world.sprites[i].anim.currentframe = 0;
		}
	}
}

int		look_for_sp(int x, int y)
{
	int i;

	i = -1;
	while (++i < g_world.numofsprites)
		if (g_world.sprites[i].pos_in_map.x == x &&
			g_world.sprites[i].pos_in_map.y == y)
			return (i);
	return (-1);
}

float	min(float a, float b)
{
	return (a < b ? a : b);
}

float	max(float a, float b)
{
	return (a < b ? a : b);
}
