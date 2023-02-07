/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 15:42:06 by htahvana          #+#    #+#             */
/*   Updated: 2023/02/07 15:59:24 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * @brief Creates a new linked list to save sector information.
 * 
 * @param point
 * @return t_vec2_lst
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
	new->decor = -1;
	new->next = NULL;
	new->decor_offset.x = 0.0;
	new->decor_offset.y = 0.0;
	return (new);
}

/**
 * @brief Adds a new node to the end of vector2d linked list. Returns NULL on
 * error. Returns pointer to added element on success
 * 
 * @param list
 * @param new
 * @return int
 */
t_vec2_lst	*put_to_vector_list(t_vec2_lst **list, t_vec2_lst *new)
{
	t_vec2_lst		*last;

	if (!new)
		return (NULL);
	new->next = NULL;
	if (!(*list))
	{
		*list = new;
		return (*list);
	}
	last = *list;
	while (last->next)
		last = last->next;
	last->next = new;
	return (last->next);
}

/**
 * @brief Deletes the whole vector2d linked list. Returns -1 upon error.
 * 
 * @param list
 * @return int
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
		if (current == *list)
			break ;
	}
	*list = NULL;
	return (0);
}
