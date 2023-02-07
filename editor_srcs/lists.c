/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 15:42:06 by htahvana          #+#    #+#             */
/*   Updated: 2023/02/07 18:30:38 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * @brief Creates a new linked list to save sector information.
 * 
 * @param point
 * @return t_wall_list
 */
t_wall_list	*new_vector_list(t_vector2 *point)
{
	t_wall_list		*new;

	new = (t_wall_list *)malloc(sizeof(t_wall_list));
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
t_wall_list	*put_to_vector_list(t_wall_list **list, t_wall_list *new)
{
	t_wall_list		*last;

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
 * @brief Cancels the ungoing list creation and deletes the incomplete
 * sectorlist.
 * 
 * @param app
*/
void	cancel_list_creation(t_app *app)
{
	del_vector_list(&(app->active));
	app->active = NULL;
	app->active_last = NULL;
	app->active_sector = NULL;
	app->list_ongoing = FALSE;
	app->list_creation = FALSE;
}

/**
 * @brief Deletes the whole vector2d linked list. Returns -1 upon error.
 * 
 * @param list
 * @return int
 */
int	del_vector_list(t_wall_list **list)
{
	t_wall_list		*current;
	t_wall_list		*next;

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
