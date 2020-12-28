/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 13:55:39 by hmellahi          #+#    #+#             */
/*   Updated: 2020/10/31 03:20:23 by hmellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	put_sprites_in_map(void)
{
	int			i;
	t_sprite	sp;
	int			x;
	int			y;

	i = -1;
	while (++i < g_world.numofsprites)
	{
		sp = g_world.sprites[i];
		x = sp.pos_in_map.x;
		y = sp.pos_in_map.y;
		if (x < (g_world.cols) && y < (g_world.rows)
		&& g_world.map[y][x] == '0')
			g_world.map[y][x] = sp.type;
		else
			return (handle_error(INVALID_SPRITE_PLACEMENT, FAIL));
	}
}

void	setrotationangle(void)
{
	if (PLAYERNAME == 'N')
		g_world.player.rotation.angle = -90;
	else if (PLAYERNAME == 'S')
		g_world.player.rotation.angle = 90;
	else if (PLAYERNAME == 'E')
		g_world.player.rotation.angle = 0;
}

void	get_player_pos(t_string line, int row)
{
	t_string	str;
	int			col;

	str = "NSWE";
	col = 0;
	while (*str)
	{
		if (ft_strchr(line, *str))
		{
			if (g_infos[player_position]++)
				return (handle_error(DUPLICATE_PLAYER, FAIL));
			else
			{
				while (*line++ != *str)
					col++;
				PLAYERPOS = new_vector(BLOCK_SIZE * col + BLOCK_SIZE / 2,
						BLOCK_SIZE * row + BLOCK_SIZE / 2);
				PLAYERNAME = *str;
				setrotationangle();
			}
		}
		str++;
	}
}

void	read_file(t_string file_name)
{
	char		*line;
	char		**tab;
	int			i;

	i = -1;
	while (++i < 10)
		g_infos[i] = 0;
	check_for_file(file_name);
	line = NULL;
	init_errors();
	tab = ft_split(file_name, '.');
	if (ft_strcmp(tab[tablen((void**)tab) - 1], "cub") != 0)
		handle_error(INVALID_FILE_NAME, FAIL);
	get_rows_cols(file_name);
	allocate_map();
	fill_map(file_name, line);
	check_closed_map();
	if (BONUS)
		put_sprites_in_map();
}

int		isnumber(t_string str)
{
	while (*str)
		if (!(ft_isdigit(*str++)))
			return (0);
	return (1);
}
