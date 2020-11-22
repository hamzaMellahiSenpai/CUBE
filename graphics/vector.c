/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 16:33:48 by hmellahi          #+#    #+#             */
/*   Updated: 2020/10/17 11:48:46 by hmellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

t_vector		new_vector(float x, float y)
{
	t_vector vector;

	vector.x = x;
	vector.y = y;
	return (vector);
}

t_vector		add_vectors(t_vector a, t_vector b)
{
	return (new_vector(a.x + b.x, a.y + b.y));
}

t_vector		multi_vectors(t_vector a, t_vector b)
{
	return (new_vector(a.x * b.x, a.y * b.y));
}

t_vector		multi_vector_to_n(t_vector a, float b)
{
	return (new_vector(a.x * b, a.y * b));
}

void			add_to_vector(t_vector *a, t_vector *b)
{
	a->x += b->x;
	a->y += b->y;
}
