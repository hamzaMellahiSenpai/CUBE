/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/24 18:43:22 by hmellahi          #+#    #+#             */
/*   Updated: 2020/10/30 04:23:33 by hmellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <signal.h>

void	do_bonus_event(int key_code)
{
	if (key_code == K_P && g_is_keypressed >= 2)
		g_world.is_game_paused = g_world.is_game_paused ? 0 : 1;
	else if (key_code == K_M)
		g_world.show_mini_map = g_world.show_mini_map ? 0 : 1;
	else if (key_code == UP_ARROW)
		g_world.player.offset += 32;
	else if (key_code == DOWN_ARROW)
		g_world.player.offset -= 32;
}

int		key_pressed(int key_code, void *p)
{
	g_world.is_game_over = 0;
	g_is_keypressed++;
	(void)p;
	if (key_code == EXIT_KEY)
		free_all(UNCOMPLETED);
	else if (g_world.only_exit)
		return (0);
	else if (key_code == RIGHT_ARROW)
		g_world.player.turn_direction = 1;
	else if (key_code == LEFT_ARROW)
		g_world.player.turn_direction = -1;
	else if (key_code == K_W)
		g_world.player.walk_direction = 1;
	else if (key_code == K_S)
		g_world.player.walk_direction = -1;
	else if (key_code == K_A)
		g_world.player.rj = 1;
	else if (key_code == K_D)
		g_world.player.rj = -1;
	else if (BONUS)
		do_bonus_event(key_code);
	return (1);
}

int		key_released(int key_code, void *p)
{
	(void)p;
	if (key_code == RIGHT_ARROW || key_code == LEFT_ARROW)
		g_world.player.turn_direction = 0;
	else if (key_code == K_A || key_code == K_D)
		g_world.player.rj = 0;
	else if (key_code == K_W)
		g_world.player.walk_direction = 0;
	else if (key_code == K_S)
		g_world.player.walk_direction = 0;
	return (1);
}

int		mouse(int x, int y)
{
	if (!is_out_of_window(new_vector(x, y)))
	{
		if ((x >= SWIDTH - 30) && x < SWIDTH)
			TURNDIRECTION = 1;
		else if ((x <= 30) && x > 0)
			TURNDIRECTION = -1;
		else
			TURNDIRECTION = 0;
	}
	return (1);
}

int		exit_hook(void)
{
	free_all(UNCOMPLETED);
	return (0);
}
