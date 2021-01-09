/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 03:18:48 by hmellahi          #+#    #+#             */
/*   Updated: 2021/01/09 18:16:54 by hmellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	pick_texture(t_image *texture, t_ray ray)
{
	if (ray.is_hor_hit)
	{
		if (sin(ray.angle) > 0)
			*texture = g_textures[north_texture];
		else
			*texture = g_textures[south_texture];
	}
	else
	{
		if (cos(ray.angle) > 0)
			*texture = g_textures[east_texture];
		else
			*texture = g_textures[west_texture];
	}
}

void	render_walls(void)
{
	float		wall_height;
	float		sky_height;
	t_image		texture;
	int			col;
	t_ray		ray;

	col = -1;
	while (++col < g_screen.width)
	{
		ray = g_world.wall_rays[col];
		ray.distance = ray.distance *
		cos(ray.angle - g_world.player.rotation.angle);
		wall_height = (BLOCK_SIZE / ray.distance) *
		(g_screen.width / 2) / tan(g_world.view_angle / 2);
		sky_height = g_world.player.offset +
		(g_screen.height - (float)wall_height) / 2;
		direct_line(col, 0, sky_height, g_world.colors[skybox]);
		direct_line(col, wall_height + sky_height,
		g_screen.height, g_world.colors[ground]);
		pick_texture(&texture, ray);
		render_texture(texture, wall_height, col,
		ray);
	}
}

void	render_texture(t_image texture, int wall_height, int col, t_ray ray)
{
	float	f;
	float	limit;
	float	y;
	int		pixel;

	limit = wall_height + (g_screen.height - wall_height)
	/ 2 + g_world.player.offset;
	y = (g_screen.height - (float)wall_height) / 2 + g_world.player.offset;
	texture.stepy = (float)texture.height / (float)wall_height;
	texture.x = ray.is_hor_hit ? fmod(ray.wall_hit.x, BLOCK_SIZE)
	* texture.width / BLOCK_SIZE : fmod(ray.wall_hit.y, BLOCK_SIZE);
	// y = max(y, 0);
	// limit = min(limit, g_screen.height);
	f = 0;
	while (y < (limit))
	{
		if ((int)texture.x < texture.width && (int)f < texture.height
		&& (int)texture.x >= 0 && (int)f >= 0)
		{
			pixel = texture.data[((int)(f) *
			texture.width + (int)texture.x)];
			put_pixel(new_vector(col, y), BONUS ?
			shadow(pixel, ray.distance) : pixel);
		}
		f += texture.stepy;
		y++;
	}
}

float	dist(t_vector a, t_vector b)
{
	return (sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y)));
}
