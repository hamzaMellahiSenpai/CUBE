/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 16:33:35 by hmellahi          #+#    #+#             */
/*   Updated: 2020/10/30 08:52:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	destroy(int x, int y)
{
	g_world.map[y][x] = '0';
	g_world.sprites[look_for_sp(x, y)].visible = 0;
}

int		get_coin(int x, int y)
{
	play_music("assets/sounds/coin.mp3");
	destroy(x, y);
	g_world.player.coins++;
	return (1);
}

int		can_walk_on_object(t_vector coordinate)
{
	int		x;
	int		y;
	int		can_walk_on;

	can_walk_on = 1;
	x = coordinate.x / BLOCK_SIZE;
	y = coordinate.y / BLOCK_SIZE;
	if (g_world.map[y][x] == 'C')
		can_walk_on = get_coin(x, y);
	else if (g_world.map[y][x] == 'P')
		can_walk_on = 0;
	else if (g_world.map[y][x] == 'H')
	{
		destroy(x, y);
		g_world.player.lives = MIN(g_world.player.lives + 1,
		g_world.player.maxlives);
		can_walk_on = 1;
	}
	else if (g_world.map[y][x] == 'T')
	{
		destroy(x, y);
		g_world.player.lives -= 1;
		can_walk_on = 1;
	}
	return (can_walk_on);
}

void	update_player(void)
{
	t_vector	n_p_position;
	float		n_p_rotation;
	float		player_speed;
	t_vector	step;
	t_vector	collision;

	player_speed = g_world.player.speed;
	n_p_rotation = g_world.player.rotation.angle;
	step.x = player_speed * cos(n_p_rotation) * WALKDIRECTION;
	step.y = player_speed * sin(n_p_rotation) * WALKDIRECTION;
	n_p_position = add_vectors(PLAYERPOS, step);
	n_p_rotation = norm_angle(n_p_rotation + TURNDIRECTION * PROTATIONSPEED);
	g_world.player.rotation.angle = n_p_rotation;
	collision = add_vectors(PLAYERPOS, multi_vector_to_n(step, 3));
	if ((!BONUS && !wall_at(collision)) || is_secret_door(collision) ||
		(can_walk_on_object(n_p_position) && !wall_at(collision)))
		PLAYERPOS = n_p_position;
}

int		is_secret_door(t_vector coordinate)
{
	int		idx_x;
	int		idx_y;

	idx_x = coordinate.x / BLOCK_SIZE;
	idx_y = coordinate.y / BLOCK_SIZE;
	return (g_world.map[idx_y][idx_x] == 'D');
}
