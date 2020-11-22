/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_music.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 00:23:40 by hmellahi          #+#    #+#             */
/*   Updated: 2020/10/29 08:16:57 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		play_music(t_string path)
{
	pid_t	pid;

	pid = fork();
	if (g_world.bc_music_pid < 0)
		handle_error(SUBPROCESS, FAIL);
	else if (pid == 0)
		execlp("mpg123", "mpg123", "-q", path, 0);
	return (pid);
}

void	do_bonus_part(void)
{
	draw_hud();
	update_sprite_frames();
	draw_mini_map();
	if (g_world.player.lives == 0)
	{
		draw_img(new_img("game_over.xpm"));
		g_world.is_game_over = 1;
		g_world.only_exit = 1;
	}
}
