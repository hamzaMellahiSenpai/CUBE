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

void	read_color(t_string line, int index, int space)
{
	t_string	*colors;

	if (g_infos[index]++ || strlen(line) < 2 || line[1] != ' ')
		return (handle_error(DUPLICATE_COLOR, FAIL));
	colors = ft_split(line + 1, ',');
	validate_args(&colors, 3, INVALID_COLORS);
	g_world.colors[space] = rgb_to_int(ft_atoi(colors[0]),
			ft_atoi(colors[1]), ft_atoi(colors[2]));
}
