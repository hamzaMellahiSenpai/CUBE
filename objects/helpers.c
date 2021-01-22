/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 16:46:35 by hmellahi          #+#    #+#             */
/*   Updated: 2021/01/22 16:46:39 by hmellahi         ###   ########.fr       */
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
	sprite.size = g_screen.width / sprite.distance * BLOCK_SIZE;
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

int		norm_res(t_string num, int i)
{
	while (*num == '0')
		num++;
	if (ft_strlen(num) > 4)
		return (i == 0 ? 2560 : 1440);
	else
		return (ft_atoi(num));
}

int		norm_color(t_string num)
{
	while (*num == '0')
		num++;
	if (ft_strlen(num) > 3)
		(handle_error2("color must be between 0 & 255 ;)", FAIL));
	else
		return (ft_atoi(num));
	return (0);
}
