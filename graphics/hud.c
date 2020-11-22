/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 03:34:47 by hmellahi          #+#    #+#             */
/*   Updated: 2020/10/31 01:19:44 by hmellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	draw_lives_bar(void)
{
	t_image		lives_bar_img;

	lives_bar_img = g_world.hearts_img;
	lives_bar_img.size = new_vector(SWIDTH / 5, SHEIGHT / 7);
	lives_bar_img.y = SHEIGHT - lives_bar_img.size.y;
	lives_bar_img.endx = lives_bar_img.size.x * g_world.player.lives / 3;
	lives_bar_img.endy = SHEIGHT;
	g_world.lives_bar = lives_bar_img;
	draw_img(lives_bar_img);
}

int		create_coins(t_image *coin_img)
{
	t_vector		size;

	*coin_img = new_img("coin.xpm");
	coin_img->size = new_vector(SWIDTH, SHEIGHT / 7);
	size = coin_img->size;
	coin_img->y = 5;
	coin_img->x = SWIDTH - size.x / 24;
	coin_img->f = 47;
	coin_img->z = 4 * coin_img->width / 5 + 25;
	coin_img->endz = (4 * coin_img->width / 5 + 38);
	coin_img->endx = SWIDTH;
	coin_img->endy = size.y;
	coin_img->height -= 47;
	coin_img->size_in_screen = size.x / 24;
	return (size.x / 24);
}

int		create_coins_count(int c, int len_nbr, int offset_x, int coin_size)
{
	t_image		coins_count_img;

	coins_count_img = g_world.coins_count_img;
	coins_count_img.size = new_vector(SWIDTH / 4, SHEIGHT / 8);
	coins_count_img.y = 5;
	coins_count_img.x = SWIDTH - coins_count_img.size.x / 11 - coin_size
	+ offset_x - (len_nbr - 1) * coins_count_img.size.x / 11;
	coins_count_img.f = 0;
	coins_count_img.z = (float)coins_count_img.width / 11 * c;
	coins_count_img.endx = SWIDTH - coin_size + offset_x
	- (len_nbr - 1) * coins_count_img.size.x / 11;
	coins_count_img.endy = coins_count_img.size.y + 5;
	draw_img(coins_count_img);
	return (coins_count_img.size.x / 11);
}

void	draw_coins_count(void)
{
	t_string	coins;
	int			len;
	int			i;
	int			offset_x;
	int			coin_size;

	coin_size = g_world.coin.size_in_screen;
	coins = ft_itoa(g_world.player.coins);
	len = ft_strlen(coins);
	i = 0;
	offset_x = 0;
	while (i < len)
		offset_x += create_coins_count(coins[i++] - '0',
				len, offset_x, coin_size);
}

void	draw_hud(void)
{
	draw_lives_bar();
	draw_img(g_world.coin);
	draw_coins_count();
}
