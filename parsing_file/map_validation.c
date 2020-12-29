/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 04:43:34 by hmellahi          #+#    #+#             */
/*   Updated: 2020/10/31 01:27:35 by hmellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	get_sprite_pos(int x, int y)
{
	static int z;

	if (!ft_strchr(BONUS ? "10NWSE D" :
	"10NWSE 2", g_world.map[y][x]))
		return (handle_error(INVALID_MAP, FAIL));
	if (BONUS || g_world.map[y][x] != '2')
		return ;
	if (z >= g_world.sprites_count)
	{
		g_world.sprites = (t_sprite*)realloc(g_world.sprites,
		sizeof(t_sprite) * (g_world.sprites_count * 4));
		g_world.sprites_count++;
	}
	g_world.sprites[z] = g_world.sprites[0];
	g_world.sprites[z].pos.x = x * BLOCK_SIZE + BLOCK_SIZE / 2;
	g_world.sprites[z].pos.y = y * BLOCK_SIZE + BLOCK_SIZE / 2;
	z++;
}

void	fill_map(t_string file_name, t_string line)
{
	int			j;
	int			i;
	int			fd;
	int			nbits;

	fd = open(file_name, O_RDONLY);
	j = 1;
	nbits = 1;
	while (nbits)
	{
		nbits = get_next_line(fd, &line);
		if (trim(line, " \t")[0] == '1' && ((i = -1) || 1))
		{
			while (++i < g_world.cols && i < ft_strlen(line))
			{
				get_player_pos(i, j, line[i]);
				g_world.map[j][i] = line[i];
				get_sprite_pos(i, j);
			}
			j++;
		}
		else
			check_for_info(line);
	}
	close(fd);
}

void	check_closed_map(void)
{
	int j;
	int i;

	j = 0;
	while (++j < g_world.rows)
	{
		i = 0;
		while (++i < g_world.cols)
			if (!ft_strchr("1 ", g_world.map[j][i]))
				if (g_world.map[j][i + 1] == ' ' ||
					g_world.map[j][i - 1] == ' ' ||
					g_world.map[j + 1][i] == ' ' ||
					g_world.map[j - 1][i] == ' ')
					return (handle_error(INVALID_MAP, FAIL));
	}
	if (!is_info_full())
		return (handle_error(MISSING_INFO, FAIL));
}

void	allocate_map(void)
{
	int i;
	int j;

	i = -1;
	g_world.map = (char**)sf_malloc((g_world.rows + 1)
	* sizeof(char*));
	g_world.sprites = (t_sprite*)sf_malloc(sizeof(t_sprite)
	* (g_world.sprites_count + 1));
	g_world.map[g_world.rows] = 0;
	while (++i < g_world.rows)
	{
		j = -1;
		g_world.map[i] = (char*)sf_malloc((g_world.cols + 1) * sizeof(char));
		g_world.map[i][g_world.cols] = 0;
		while (++j < g_world.cols)
			g_world.map[i][j] = ' ';
	}
}

void	get_rows_cols(t_string file_name)
{
	int			fd;
	t_string	line;
	t_string	tmp;
	int			nbits;
	int			map_end;

	fd = open(file_name, O_RDONLY);
	g_world.rows = 2;
	nbits = 1;
	map_end = 0;
	while (nbits)
	{
		nbits = get_next_line(fd, &line);
		tmp = trim(line, " \t");
		if (tmp[0] == 'S' && ft_strlen(line) > 2 && line[1] != 'O')
			g_world.sprites_count++;
		if (*tmp != '\0' && map_end == 1)
			return (handle_error(INVALID_MAP, FAIL));
		else if (*tmp == '1' && g_world.rows++)
			update_col_name(line);
		else if (*line == '\0' && g_infos[map] == 1 && map_end == 0)
			map_end = 1;
	}
	g_world.cols += 2;
	close(fd);
}
