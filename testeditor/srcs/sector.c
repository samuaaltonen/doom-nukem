/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 13:36:45 by htahvana          #+#    #+#             */
/*   Updated: 2022/11/24 16:33:50 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * Creates a new linked list to save sectors.
 */
t_sector_lst	*new_sector_list(t_vec2_lst *wall_list)
{
	t_sector_lst	*new;
	t_vec2_lst		*tmp;

	new = (t_sector_lst *)ft_memalloc(sizeof(t_sector_lst));
	if (!new)
		return (NULL);
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
 * 	and returns the newly added sector
 * 
 * @param app 
 * @param new 
 * @return t_sector_lst* 
 */
t_sector_lst	*put_sector_lst(t_app *app, t_sector_lst *new)
{
	t_sector_lst	*iter;

	if (!new)
		exit_error("Editor: add_sector_lst failed!\n");
	if (app->sectors)
	{
		iter = app->sectors;
		while (iter->next)
			iter = iter->next;
		iter->next = new;
	}
	else
		app->sectors = new;
	app->sectorcount++;
	return (new);
}

//WIP
void	sector_delone(t_sector_lst **sector, void (*del)(void*, size_t))
{
	int		i;
	(void)del;

	i = 0;
	if ((*sector)->parent_sector)
	{
		while ((*sector)->parent_sector->member_sectors[i] != *sector)
			i++;
		(*sector)->parent_sector->member_sectors[i] = NULL;
		while (++i < MAX_MEMBER_SECTORS
			&& (*sector)->parent_sector->member_sectors[i])
		{
			(*sector)->parent_sector->member_sectors[i - 1]
				= (*sector)->parent_sector->member_sectors[i];
			(*sector)->parent_sector->member_sectors[i] = NULL;
		}
		(*sector)->parent_sector = NULL;
	}
	free(*sector);
	*sector = NULL;
}

/**
 * Pop out the selected sector from the sector list if the sector has no 
 * members, runs del on it and returns the popped sector.
 */
t_sector_lst	*sector_pop(t_app *app, t_sector_lst **pop,
									void (*del)(void *, size_t))
{
	t_sector_lst	*prev;
	t_sector_lst	*head;

	if (!pop || !(*pop) || (*pop)->member_sectors[0] || !(app->sectors))
		return (NULL);
	prev = NULL;
	head = app->sectors;
	while (head->next && head != *pop)
	{
		prev = head;
		head = head->next;
	}
	if (app->active_sector == app->player.sector)
	{
		app->player.sector = NULL;
		app->player_edit = TRUE;
	}
	del_sector_portals(app, get_sector_id(app, app->active_sector));
	if (head == *pop)
	{
		if (prev)
			prev->next = (*pop)->next;
		if (head == app->sectors)
			app->sectors = (*pop)->next;
		sector_delone(pop, del);
		app->active_sector = NULL;
		app->active = NULL;
		app->sectorcount--;
	}
	return (*pop);
}

/**
 * @brief Completes an ongoing sector
 * 
 * @param app 
 * @return t_bool 
 */
t_bool	complete_sector(t_app *app)
{
	t_sector_lst	*new;

	app->active_last->next = app->active;
	new = put_sector_lst(app, new_sector_list(app->active));
	app->active = NULL;
	app->active_last = NULL;
	app->list_ongoing = FALSE;
	app->list_creation = FALSE;
	new->parent_sector = app->active_sector;
	add_member_sector(new->parent_sector, new);
	change_walls_tex(new->wall_list, app->sectorcount);
	change_walls_type(app, new);
	return (0);
}
