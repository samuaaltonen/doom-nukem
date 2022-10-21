/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 15:42:06 by htahvana          #+#    #+#             */
/*   Updated: 2022/10/21 13:20:33 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * Creates a new linked list to save vertices (x, y points) of a sector.
 */
t_vec2list	*new_vector_list(t_vector2 *point)
{
	t_vec2list		*new;

	new = (t_vec2list *)malloc(sizeof(t_vec2list));
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
int		put_to_vector_list(t_vec2list **list, t_vec2list *new)
{
	t_vec2list		*last;

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
 * @brief Puts new sector into the app->sectors list
 * 	and returns the newly added sector
 * 
 * @param app 
 * @param new 
 * @return t_sectorlist* 
 */
t_sectorlist	*put_sector_lst(t_app *app, t_sectorlist* new)
{
	t_sectorlist *iter;

	if(!new)
		exit_error("editor:add_sector_lst failed!\n");
	if(app->sectors)
	{
		iter = app->sectors;
		while (iter->next)
			iter = iter->next;
		iter->next = new;
	}
	else
		app->sectors = new;
	app->sectorcount++;
	return(new);
}

/**
 * Creates a new linked list to save sectors.
 */
t_sectorlist	*new_sector_list(t_vec2list *wall_list)
{
	t_sectorlist	*new;
	t_vec2list		*tmp;

	new = (t_sectorlist *)ft_memalloc(sizeof(t_sectorlist));
	if (!new)
		return (NULL);

	tmp = wall_list->next;
	new->corner_count++;
	while(tmp != wall_list)
	{
		new->corner_count++;
		tmp = tmp->next;
	}
	new->wall_list = wall_list;
	new->ceil_height = 1.0f;
	new->floor_tex_offset = -1;
	new->ceil_tex_offset = -1;
	new->next = NULL;
	return (new);
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