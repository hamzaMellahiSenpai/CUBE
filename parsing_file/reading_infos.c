/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading_infos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/25 02:35:11 by marvin            #+#    #+#             */
/*   Updated: 2020/10/31 01:18:06 by hmellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	read_resolution(t_string line)
{
	t_string	*tab;

	if (g_infos[resolution]++)
		return (handle_error(DUPLICATE_RESOLUTION, FAIL));
	tab = ft_split(line + 1, ' ');
	validate_args(&tab, 2, INVALID_RESOLUTION);
	g_screen.width = ft_atoi(tab[0]);
	g_screen.height = ft_atoi(tab[1]);
	if (g_screen.width < 100 || g_screen.height < 100)
		return (handle_error(INVALID_RESOLUTION, FAIL));
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

	if (g_infos[index]++)
		return (handle_error(DUPLICATE_COLOR, FAIL));
	if (strlen(line) < 2 || line[1] != ' ' || get_count(line, ',') != 2)
		return (handle_error(INVALID_COLORS, FAIL));
	colors = ft_split(line + 1, ',');
	validate_args(&colors, 3, INVALID_COLORS);
	r = ft_atoi(colors[0]);
	g = ft_atoi(colors[1]);
	b = ft_atoi(colors[2]);
	if (r > 255 || r < 0 || g > 255 || g < 0 || b > 255 || b < 0)
		return (handle_error(INVALID_COLORS, FAIL));
	g_world.colors[space] = rgb_to_int(r, g, b);
}
