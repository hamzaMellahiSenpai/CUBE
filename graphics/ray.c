/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 15:33:22 by hmellahi          #+#    #+#             */
/*   Updated: 2021/01/09 17:47:52 by hmellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

t_ray		new_ray(float rayangle)
{
	t_ray	ray;

	ray.angle = norm_angle(rayangle);
	ray.distance = 0;
	ray.is_facing_right = ((ray.angle < (M_PI / 2)) ||
			(ray.angle > (1.5 * M_PI)));
	ray.is_facing_left = !ray.is_facing_right;
	ray.is_facing_down = (ray.angle >= 0 && ray.angle <= M_PI);
	ray.is_facing_up = !ray.is_facing_down;
	return (ray);
}

t_vector	get_horizontal_intersection(t_ray ray, int *hor_found)
{
	t_vector	a;
	t_vector	step;

	a.y = (int)(g_world.player.position.y / BLOCK_SIZE) * BLOCK_SIZE;
	a.y += ray.is_facing_down ? BLOCK_SIZE : -0.001;
	a.x = (a.y - g_world.player.position.y)
	/ tan(ray.angle) + g_world.player.position.x;
	step.y = BLOCK_SIZE;
	step.y *= ray.is_facing_up ? -1 : 1;
	step.x = BLOCK_SIZE / tan(ray.angle);
	step.x *= (ray.is_facing_left && step.x > 0) ? -1 : 1;
	step.x *= (ray.is_facing_right && step.x < 0) ? -1 : 1;
	while (!is_out_of_window(a))
	{
		if (wall_at(a))
		{
			*hor_found = 1;
			break ;
		}
		add_to_vector(&a, &step);
	}
	return (a);
}

t_vector	get_vertical_intersection(t_ray ray, int *ver_found)
{
	t_vector	b;
	t_vector	step;

	b.x = (int)(g_world.player.position.x / BLOCK_SIZE) * BLOCK_SIZE;
	b.x += ray.is_facing_right ? BLOCK_SIZE : -0.001;
	b.y = g_world.player.position.y + tan(ray.angle)
	* (b.x - g_world.player.position.x);
	step.x = BLOCK_SIZE;
	step.x *= ray.is_facing_left ? -1 : 1;
	step.y = BLOCK_SIZE * tan(ray.angle);
	step.y *= (ray.is_facing_up && step.y > 0) ? -1 : 1;
	step.y *= (ray.is_facing_down && step.y < 0) ? -1 : 1;
	while (!is_out_of_window(b))
	{
		if (wall_at(b))
		{
			*ver_found = 1;
			break ;
		}
		add_to_vector(&b, &step);
	}
	return (b);
}

void		line(float x0, float y0, float x1, float y1)
{
	float	steps;
	float	xinc;
	float	yinc;
	int		i;

	steps = fabsf(x1 - x0) > fabsf(y1 - y0) ? fabsf(x1 - x0) : fabsf(y1 - y0);
	xinc = (x1 - x0) / (float)steps;
	yinc = (y1 - y0) / (float)steps;
	i = -1;
	while (++i <= steps)
	{
		put_pixel(new_vector(x0, y0), 0xff0000);
		x0 += xinc;
		y0 += yinc;
	}
}

void		cast(t_ray *ray)
{
	t_vector	a;
	t_vector	b;
	float		hor_hit_dist;
	float		ver_hit_dist;

	ray->is_hor_hit = 1;
	ray->is_facing_right = (ray->angle < (M_PI / 2))
		|| (ray->angle > (1.5 * M_PI));
	ray->is_facing_left = !ray->is_facing_right;
	ray->is_facing_down = (ray->angle >= 0 && ray->angle <= M_PI);
	ray->is_facing_up = !ray->is_facing_down;
	ray->hor_found = 0;
	ray->ver_found = 0;
	a = get_horizontal_intersection(*ray, &ray->hor_found);
	b = get_vertical_intersection(*ray,
	&ray->ver_found);
	hor_hit_dist = ray->hor_found ? dist(a, g_world.player.position) : 900000;
	ver_hit_dist = ray->ver_found ? dist(b, g_world.player.position) : 900000;
	if (hor_hit_dist > ver_hit_dist)
	{
		ray->is_hor_hit = 0;
		a = b;
	}
	ray->distance = dist(a, g_world.player.position);
	ray->wall_hit = a;
}
