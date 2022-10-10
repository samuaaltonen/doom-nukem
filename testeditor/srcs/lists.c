/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 15:42:06 by htahvana          #+#    #+#             */
/*   Updated: 2022/10/10 11:37:17 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * Creates a new linked list to save vertices (x, y points) of a sector.
 */
t_vec2list	*new_vector_list(t_app *app)
{
	t_vec2list		*new;

	if (app->mouse_click.x < 0 || app->mouse_click.x > WIN_W
		|| app->mouse_click.y < 0 || app->mouse_click.y > WIN_H)
		return (NULL);
	new = (t_vec2list *)malloc(sizeof(t_vec2list));
	if (!new)
		return (NULL);
	new->point.x = app->mouse_click.x;
	new->point.y = app->mouse_click.y;
	new->next = NULL;
	return (new);
}

/**
 * Adds a new node to the end of vector2d linked list.
 */
int		add_to_vector_list(t_vec2list **list, t_vec2list *new)
{
	t_vec2list		*last;

	if (!new)
		return (-1);
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
int		del_vector_list(t_vec2list **list)
{
	t_vec2list		*current;
	t_vec2list		*next;

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