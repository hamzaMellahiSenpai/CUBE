/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loading_assets.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/25 02:35:21 by marvin            #+#    #+#             */
/*   Updated: 2020/10/31 03:09:41 by hmellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

t_image	load_image(int i, t_string path, int type)
{
	check_for_file(path);
	if (type == TEXTURE)
	{
		g_textures[i].img = mlx_xpm_file_to_image(g_mlx, path,
		&g_textures[i].width, &g_textures[i].height);
		if (!g_textures[i].img)
			handle_error(INVALID_FILE_NAME, FAIL);
		g_textures[i].data = (int *)mlx_get_data_addr(g_textures[i].img,
		&g_textures[i].bits_per_pixel, &g_textures[i].bits_per_pixel,
		&g_textures[i].endian);
	}
	else if (type == SPRITE)
	{
		g_world.sprites[i].img.img = mlx_xpm_file_to_image(g_mlx, path,
		&g_world.sprites[i].img.width, &g_world.sprites[i].img.height);
		if (!g_world.sprites[i].img.img)
			handle_error(INVALID_FILE_NAME, FAIL);
		g_world.sprites[i].img.data = (int *)mlx_get_data_addr(
		g_world.sprites[i].img.img,
		&g_world.sprites[i].img.bits_per_pixel,
		&g_world.sprites[i].img.bits_per_pixel,
		&g_world.sprites[i].img.endian);
	}
	return (g_textures[i]);
}

void	load_texture(t_string line, int index)
{
	t_string path;

	if (g_infos[index])
		return (handle_error(DUPLICATE_TEXTURE, FAIL));
	if (ft_strlen(line) < 3)
		return (handle_error(INVALID_PATH, FAIL));
	path = trim(line + 2, " ");
	load_image(index, path, TEXTURE);
}

void	setup_bns_sprite(t_sprite *sp, char **tab2, char **tab)
{
	t_animation	anim;
	t_vector	pm;
	t_string	*x;

	sp->type = strlen(tab2[0]) == 2 ? tab2[0][1] : 'P';
	x = tab + 1;
	validate_args(&x, 6, INVALID_SPRITE_ARG);
	anim.is_play_on_awake = ft_atoi(tab[3]);
	anim.nofframes = ft_atoi(tab[4]);
	anim.fps = ft_atoi(tab[5]);
	anim.currentframe = 0;
	sp->anim = anim;
	sp->bc = ft_atoi(tab[6]);
	sp->pos_in_map = new_vector(ft_atoi(tab[1]), ft_atoi(tab[2]) + 1);
	pm = sp->pos_in_map;
	sp->pos = new_vector((pm.x + 0.5) * BLOCK_SIZE,
			(pm.y + 0.5) * BLOCK_SIZE);
}

void	setup_sprite(t_sprite *sprite)
{
	if (g_infos[sprite_texture]++)
		return (handle_error(DUPLICATE_SPRITE, FAIL));
	sprite->anim.is_play_on_awake = 0;
	sprite->type = '2';
	sprite->bc = 0;
}

void	load_sprite(t_string line)
{
	t_string	*tab;
	t_sprite	sprite;
	t_string	*tab2;
	t_string	path;

	tab = ft_split(line, '|');
	tab2 = ft_split(tab[0], ' ');
	if (ft_strlen(tab[0]) < 3)
		return (handle_error(INVALID_PATH, FAIL));
	path = BONUS ? trim(tab[0] + 2, " ") : trim(tab[0] + 1, " ");
	if (ft_strlen(tab2[0]) == 2 && (!BONUS || !ft_strchr("CHT", tab2[0][1])))
		return (handle_error(INVALID_SPRITE_ARG, FAIL));
	sprite.path = path;
	if (!BONUS)
		setup_sprite(&sprite);
	else
		setup_bns_sprite(&sprite, tab2, tab);
	sprite.visible = 1;
	g_world.numofsprites++;
	g_world.sprites[g_world.numofsprites - 1] = sprite;
	load_image(g_world.numofsprites - 1, sprite.path, SPRITE);
}
