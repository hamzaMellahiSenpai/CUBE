/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 16:46:35 by hmellahi          #+#    #+#             */
/*   Updated: 2021/01/09 18:24:46 by hmellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	handle_sprite(int i)
{
	float		angle;
	t_sprite	sprite;

	g_world.sprites[i].distance = dist(g_world.sprites[i].pos,
	g_world.player.position);
	sprite = g_world.sprites[i];
	angle = atan2(sprite.pos.y - g_world.player.position.y,
	sprite.pos.x - g_world.player.position.x);
	while (angle - g_world.player.rotation.angle > M_PI)
		angle -= 2 * M_PI;
	while (angle - g_world.player.rotation.angle < -M_PI)
		angle += 2 * M_PI;
	sprite.size = ((g_screen.height > g_screen.width) ?
	g_screen.width : g_screen.height) / sprite.distance * BLOCK_SIZE;
	sprite.s_y = (g_screen.height - sprite.size) / 2 +
	g_world.player.offset;
	sprite.s_x = (angle - g_world.player.rotation.angle)
	* (g_screen.width / g_world.view_angle)
	+ (g_screen.width / 2 - sprite.size / 2);
	sprite.size *= 1.15;
	render_sprite(sprite);
}

void	update_player_pos(t_vector *step)
{
	float		n_p_rotation;
	float		player_speed;

	player_speed = g_world.player.speed;
	n_p_rotation = g_world.player.rotation.angle;
	if (g_world.player.rj != 0)
	{
		step->x = player_speed *
		cos(n_p_rotation - M_PI / 2) * g_world.player.rj;
		step->y = player_speed *
		sin(n_p_rotation - M_PI / 2) * g_world.player.rj;
	}
	else
	{
		step->x = player_speed * cos(n_p_rotation)
		* g_world.player.walk_direction;
		step->y = player_speed * sin(n_p_rotation)
		* g_world.player.walk_direction;
	}
}
