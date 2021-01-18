/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading_infos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/25 02:35:11 by marvin            #+#    #+#             */
/*   Updated: 2021/01/18 15:55:24 by hmellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	read_resolution(t_string line)
{
	t_string	*tab;

	if (g_infos[resolution]++)
		return (handle_error(DUPLICATE_RESOLUTION, FAIL));
	if (ft_strlen(line) < 2 || line[1] != ' ')
		return (handle_error(INVALID_RESOLUTION, FAIL));
	tab = ft_split(line + 2, ' ');
	tab = ft_split(line + 2, ' ');
	validate_args(&tab, 2, INVALID_RESOLUTION);
	g_screen.width = ft_atoi(tab[0]);
	g_screen.height = ft_atoi(tab[1]);
	printf("%d\n", g_screen.width);
	if (g_screen.width == 0 || g_screen.height == 0)
		return (handle_error(INVALID_RESOLUTION, FAIL));
	if (g_screen.width < 0 || g_screen.height < 0)
		return (handle_error2("resolution cant be negative", FAIL));
	if (g_screen.width > 2560)
		g_screen.width = 2560;
	if (g_screen.height > 1440)
		g_screen.height = 1440;
}

void	read_image(t_string line, int index)
{
	if (index <= 3)
		load_texture(line, index);
	else
		load_sprite(line);
	g_infos[index]++;
}

int		get_count(t_string str, char c)
{
	int		count;
	int		i;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

void	read_color(t_string line, int index, int space)
{
	t_string	*colors;
	int			g;
	int			b;
	int			r;
	int			i;

	if (g_infos[index]++)
		return (handle_error(DUPLICATE_COLOR, FAIL));
	if (strlen(line) < 2 || line[1] != ' ' || get_count(line, ',') != 2)
		return (handle_error(INVALID_COLORS, FAIL));
	colors = ft_split(line + 1, ',');
	validate_args(&colors, 3, INVALID_COLORS);
	i = -1;
	while (colors[++i])
		if (strlen(colors[0]) > 3 ||
		strlen(colors[1]) > 3 || strlen(colors[2]) > 3)
			return (handle_error2("color must be between 0 & 255 ;)", FAIL));
	r = ft_atoi(colors[0]);
	g = ft_atoi(colors[1]);
	b = ft_atoi(colors[2]);
	if (r > 255 || r < 0 || g > 255 || g < 0 || b > 255 || b < 0)
		return (handle_error(INVALID_COLORS, FAIL));
	g_world.colors[space] = rgb_to_int(r, g, b);
}

void	do_ur_thing(int *flag, t_string line, int i, int j)
{
	*flag = 1;
	while (++i < g_world.cols && i < ft_strlen(line))
	{
		get_player_pos(i, j, line[i]);
		g_world.map[j][i] = line[i];
		get_sprite_pos(i, j);
	}
}
