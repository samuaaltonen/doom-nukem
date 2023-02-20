/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 13:36:45 by htahvana          #+#    #+#             */
/*   Updated: 2023/02/20 12:45:20 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * @brief Creates a new linked list to save sectors.
 * 
 * @param wall_list
 * @return t_sector_list*
 */
t_sector_list	*new_sector_list(t_wall_list *wall_list)
{
	t_sector_list	*new;
	t_wall_list		*tmp;

	new = (t_sector_list *)ft_memalloc(sizeof(t_sector_list));
	if (!new)
		exit_error(MSG_ERROR_ALLOC);
	tmp = wall_list->next;
	new->corner_count++;
	while (tmp != wall_list)
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
 * @brief Puts new sector into the app->sectors list
 * 	and returns the newly added sector.
 * 
 * @param app 
 * @param new 
 * @return t_sector_list* 
 */
t_sector_list	*put_sector_list(t_app *app, t_sector_list *new)
{
	t_sector_list	*iter;

	if (!new)
		exit_error(MSG_ERROR_ALLOC);
	if (app->sectors)
	{
		iter = app->sectors;
		while (iter->next)
			iter = iter->next;
		iter->next = new;
	}
	else
		app->sectors = new;
	if (app->sector_count < ((int)ft_lstlen(app->sectors)))
		app->sector_count++;
	if (app->sector_count >= MAX_SECTOR_COUNT)
		exit_error(MSG_ERROR_SECTOR_LIMIT);
	return (new);
}

/**
 * @brief Prepares the sector deletion by deleting all objects, interactions
 * and portals in that sector. If player is within the deleted sector, sets
 * the player sector to NULL and turns player edit on.
 * 
 * @param app
 * @param pop
*/
static void	prepare_del(t_app *app, t_sector_list **pop)
{
	if (app->active_sector == app->player.sector)
	{
		app->player.sector = NULL;
		app->player_edit = TRUE;
	}
	del_all_objects_in_sector(app);
	del_all_sector_interactions(app, pop);
	del_sector_portals(app, get_sector_id(app, app->active_sector));
}

/**
 * @brief Pop out the selected sector from the sector list if the sector has no 
 * members, runs del on it and returns the popped sector.
 * 
 * @param app
 * @param pop
 * @return t_sector_list*
 */
t_sector_list	*sector_pop(t_app *app, t_sector_list **pop)
{
	t_sector_list	*prev;
	t_sector_list	*head;

	if (!pop || !(*pop) || (*pop)->member_sectors[0] || !(app->sectors))
		return (NULL);
	prev = NULL;
	head = app->sectors;
	while (head->next && head != *pop)
	{
		prev = head;
		head = head->next;
	}
	prepare_del(app, pop);
	if (head == *pop)
	{
		if (prev)
			prev->next = (*pop)->next;
		if (head == app->sectors)
			app->sectors = (*pop)->next;
		sector_delone(pop);
		app->active_sector = NULL;
		app->active = NULL;
		app->sector_count--;
	}
	return (*pop);
}

/**
 * @brief Completes an ongoing sector.
 * 
 * @param app 
 * @return t_bool 
 */
t_bool	complete_sector(t_app *app)
{
	t_sector_list	*new;

	app->active_last->next = app->active;
	new = put_sector_list(app, new_sector_list(app->active));
	app->active = NULL;
	app->active_last = NULL;
	app->list_ongoing = FALSE;
	app->list_creation = FALSE;
	new->parent_sector = app->active_sector;
	add_member_sector(new->parent_sector, new);
	change_walls_type(app, new);
	change_walls_tex(new->wall_list, app->template.wall_tex);
	new->ceil_tex = app->template.ceil_tex;
	new->floor_tex = app->template.floor_tex;
	new->ceil_height = app->template.ceil_height;
	new->floor_height = app->template.floor_height;
	new->light = app->template.light;
	if (app->linking_mode)
		find_links(app, new);
	return (FALSE);
}
