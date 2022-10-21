/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 15:42:06 by htahvana          #+#    #+#             */
/*   Updated: 2022/10/21 13:43:29 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * Creates a new linked list to save vertices (x, y points) of a sector.
 */
t_vec2_lst	*new_vector_list(t_vector2 *point)
{
	t_vec2_lst		*new;

	new = (t_vec2_lst *)malloc(sizeof(t_vec2_lst));
	if (!new)
		return (NULL);
	new->point.x = point->x;
	new->point.y = point->y;
	new->wall_texture = -1;
	new->wall_type = -1;
	new->next = NULL;
	return (new);
}

/**
 * Adds a new node to the end of vector2d linked list.
 */
int		put_to_vector_list(t_vec2_lst **list, t_vec2_lst *new)
{
	t_vec2_lst		*last;

	if (!new)
		return (-1);
	new->next = NULL;
	if (!(*list))
	{
		*list = new;
		return (0);
	}
	last = *list;
	while (last->next)
		last = last->next;
	last->next = new;
	return (0);
}

/**
 * Deletes the whole vector2d linked list.
 */
int		del_vector_list(t_vec2_lst **list)
{
	t_vec2_lst		*current;
	t_vec2_lst		*next;

	if (!(*list))
		return (-1);
	current = *list;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
	*list = NULL;
	return (0);
}