/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 08:29:20 by hmellahi          #+#    #+#             */
/*   Updated: 2020/10/30 21:44:13 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	update_sprites(void)
{
	int	i;

	i = -1;
	while (++i < g_world.sprites_count)
		g_world.sprites[i].distance = dist(g_world.sprites[i].pos,
		g_world.player.position);
	sort_sprites();
}

void	sort_sprites(void)
{
	int			i;
	int			j;
	t_sprite	tmp;
	t_sprite	*sprites;

	sprites = g_world.sprites;
	i = -1;
	while (i++ < g_world.sprites_count)
	{
		j = -1;
		while (j++ < g_world.sprites_count - 1)
		{
			if ((sprites[j]).distance < (sprites[j + 1]).distance)
			{
				tmp = sprites[j];
				sprites[j] = sprites[j + 1];
				sprites[j + 1] = tmp;
			}
		}
	}
}

int		get_pixel(t_sprite sprite, int i, int j)
{
	int pixel;
	int	y;
	int	x;

	pixel = 0;
	if (sprite.anim.is_play_on_awake)
	{
		pixel = sprite.img.data[sprite.img.width *
		(sprite.img.height * j / (int)sprite.size) +
		(sprite.img.width / sprite.anim.nofframes
		* i / (int)sprite.size) +
		(sprite.anim.currentframe * sprite.anim.fps / 10)
		* sprite.img.width / sprite.anim.nofframes];
	}
	else
	{
		y = sprite.img.height * j / (int)sprite.size;
		x = sprite.img.height * i / (int)sprite.size;
		if (x >= 0 && y >= 0 && x < sprite.img.width
		&& y < sprite.img.height)
			pixel = sprite.img.data[sprite.img.width * y + x];
	}
	return (pixel);
}

void	render_sprite(t_sprite sprite)
{
	unsigned int	pixel;
	int				i;
	int				j;

	i = -1;
	while (++i < sprite.size)
	{
		if (sprite.s_x + i < 0 || sprite.s_x + i > SWIDTH)
			continue;
		if (sprite.distance >= g_world.wall_rays[(int)sprite.s_x + i].distance)
			continue;
		j = -1;
		while (++j < ((sprite.size - 2) / 1))
		{
			if (sprite.s_y + j < 0 || sprite.s_y + j > SHEIGHT)
				continue;
			pixel = get_pixel(sprite, i, j);
			if (pixel != sprite.bc)
				put_pixel(new_vector(sprite.s_x + i, sprite.s_y + j),
				!BONUS ? pixel :
				shadow(pixel, sprite.distance));
		}
	}
}

void	show_sprites(void)
{
	int			i;
	float		angle;
	t_sprite	sprite;

	i = -1;
	while (++i < g_world.sprites_count)
		if (g_world.sprites[i].visible)
		{
			g_world.sprites[i].distance = dist(g_world.sprites[i].pos,
			g_world.player.position);
			sprite = g_world.sprites[i];
			angle = atan2(sprite.pos.y - PLAYERPOS.y,
			sprite.pos.x - PLAYERPOS.x);
			while (angle - PROTATIONANGLE > M_PI)
				angle -= 2 * M_PI;
			while (angle - PROTATIONANGLE < -M_PI)
				angle += 2 * M_PI;
			sprite.size = ((g_screen.height > g_screen.width) ?
			SWIDTH : SHEIGHT) / sprite.distance * BLOCK_SIZE;
			sprite.s_y = (SHEIGHT - sprite.size) / 2 + g_world.player.offset;
			sprite.s_x = (angle - PROTATIONANGLE) * (SWIDTH / VIEW_ANGLE)
			+ (SWIDTH / 2 - sprite.size / 2);
			sprite.size *= 1.15;
			render_sprite(sprite);
		}
}
