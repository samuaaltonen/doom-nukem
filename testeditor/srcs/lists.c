/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 15:42:06 by htahvana          #+#    #+#             */
/*   Updated: 2022/11/02 15:50:24 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * Creates a new linked list to save lines (x, y points) of a sector.
 */
t_vec2_lst	*new_vector_list(t_vector2 *point)
{
	t_vec2_lst		*new;

	new = (t_vec2_lst *)malloc(sizeof(t_vec2_lst));
	if (!new)
		return (NULL);
	new->point.x = point->x;
	new->point.y = point->y;
	new->tex = -1;
	new->type = -1;
	new->next = NULL;
	return (new);
}

/**
 * Adds a new node to the end of vector2d linked list.
 */
int	put_to_vector_list(t_vec2_lst **list, t_vec2_lst *new)
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
int	del_vector_list(t_vec2_lst **list)
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

/**
 * Reverses the vector2d linked list.
*/
void	reverse_vector_list(t_vec2_lst **head)
{
	t_vec2_lst	*prev;
	t_vec2_lst	*next;
	t_vec2_lst	*current;

	if (!(*head))
		return ;
	prev = NULL;
	next = NULL;
	current = *head;
	while (current)
	{
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	*head = prev;
}
