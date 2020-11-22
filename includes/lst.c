/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 00:30:02 by hmellahi          #+#    #+#             */
/*   Updated: 2020/10/16 23:53:22 by hmellahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	push_back(t_lst **alst, t_lst *new)
{
	t_lst	*ptr;

	if (!*alst)
		return (push_front(alst, new));
	ptr = *alst;
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = new;
}

void	push_front(t_lst **head_ref, t_lst *new)
{
	new->next = *head_ref;
	*head_ref = new;
}

t_lst	*new_lst(void *content)
{
	t_lst	*newlist;

	if (!(newlist = malloc(sizeof(t_lst))))
		(handle_error(Allocation_Failed, FAIL));
	newlist->content = content;
	newlist->next = NULL;
	push_back(&g_world.adresses, newlist);
	return (newlist);
}

void	deletelist(t_lst **head_ref)
{
	t_lst	*current;
	t_lst	*next;

	current = *head_ref;
	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
	*head_ref = NULL;
}

t_pair	*make_pair(void *a, void *b)
{
	t_pair *pair;

	pair = sf_malloc(sizeof(t_pair));
	pair->a = a;
	pair->b = b;
	return (pair);
}
