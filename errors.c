/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/24 09:51:10 by hmellahi          #+#    #+#             */
/*   Updated: 2020/10/29 05:37:19 by hmellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void		init_infos(void)
{
	g_infos_names[0] = "north_texture";
	g_infos_names[1] = "south_texture";
	g_infos_names[2] = "east_texture";
	g_infos_names[3] = "west_texture";
	g_infos_names[4] = "sprite_texture";
	g_infos_names[5] = "resolution";
	g_infos_names[6] = "floor_color";
	g_infos_names[7] = "ceil_color";
	g_infos_names[8] = "map";
	g_infos_names[9] = "player_position";
}

void		init_errors(void)
{
	g_messages[0] = "Invalid file name!";
	g_messages[1] = "Missing info";
	g_messages[2] = "Duplicate Texture";
	g_messages[3] = "Duplicate Color";
	g_messages[4] = "Duplicate Resolution";
	g_messages[5] = "Stop Idiot! You have reached the range of g_screen";
	g_messages[6] = "Invalid Map";
	g_messages[7] = "NO SUCH FILE OR DIRECTORY";
	g_messages[8] = "Allocation Failed";
	g_messages[9] = "PROCCESS_CANT_BE_CREATED";
	g_messages[10] = "INVALID_PATH";
	g_messages[11] = "INVALID_SPRITE_PLACEMENT";
	g_messages[12] = "INVALID_RESOLUTION";
	g_messages[13] = "DUPLICATE_PLAYER";
	g_messages[14] = "INVALID SPRITE ARGUMENT";
	g_messages[15] = "INVALID COLORS";
	g_messages[16] = "DUPLICATE_SPRITE";
	g_messages[17] = "CANNOT CREATE SUBPROCESS";
	g_messages[18] = "NOT VALID NUMBER OF ARGS";
	init_infos();
}

void		handle_error(int error_index, int status)
{
	t_string output;

	output = ft_strjoin("Error\n", g_messages[error_index], 2);
	write(1, output, ft_strlen(output));
	free_all(status);
}

void		handle_error2(t_string output, int status)
{
	write(1, output, ft_strlen(output));
	free_all(status);
}

void		check_for_file(t_string file_name)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		handle_error(INVALID_FILE_NAME, FAIL);
}
