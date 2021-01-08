/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_sprite.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 16:46:35 by hmellahi          #+#    #+#             */
/*   Updated: 2021/01/08 16:46:43 by hmellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	handle_sprite(int i)
{
	float		angle;
	t_sprite	sprite;

	g_world.sprites[i].distance = dist(g_world.sprites[i].pos,
	g_world.player.position);
	sprite = g_world.sprites[i];
	angle = atan2(sprite.pos.y - g_world.player.position.y,
	sprite.pos.x - g_world.player.position.x);
	while (angle - g_world.player.rotation.angle > M_PI)
		angle -= 2 * M_PI;
	while (angle - g_world.player.rotation.angle < -M_PI)
		angle += 2 * M_PI;
	sprite.size = ((g_screen.height > g_screen.width) ?
	g_screen.width : g_screen.height) / sprite.distance * BLOCK_SIZE;
	sprite.s_y = (g_screen.height - sprite.size) / 2 +
	g_world.player.offset;
	sprite.s_x = (angle - g_world.player.rotation.angle)
	* (g_screen.width / g_world.view_angle)
	+ (g_screen.width / 2 - sprite.size / 2);
	sprite.size *= 1.15;
	render_sprite(sprite);
}
