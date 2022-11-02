/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 13:36:45 by htahvana          #+#    #+#             */
/*   Updated: 2022/11/01 14:29:08 by htahvana         ###   ########.fr       */
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
 * @brief Puts new sector into the app->sectors list
 * 	and returns the newly added sector
 * 
 * @param app 
 * @param new 
 * @return t_sector_lst* 
 */
t_sector_lst	*put_sector_lst(t_app *app, t_sector_lst* new)
{
	t_sector_lst *iter;

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

//WIP
void	sector_delone(t_sector_lst **sector, void (*del)(void*, size_t))
{
	(void)del;
	int i;

	i = 0;
	if((*sector)->parent_sector)
	{
		while ((*sector)->parent_sector->member_sectors[i] != *sector)
			i++;
		(*sector)->parent_sector->member_sectors[i] = NULL;
		while (++i < MAX_MEMBER_SECTORS && (*sector)->parent_sector->member_sectors[i])
		{
			(*sector)->parent_sector->member_sectors[i - 1] = (*sector)->parent_sector->member_sectors[i];
			(*sector)->parent_sector->member_sectors[i] = NULL;
		}
		(*sector)->parent_sector = NULL;
	}
	free(*sector);
	*sector = NULL;
}

/**
 * Pop out the selected sector from the sector list if the sector has no members, runs del on it and returns the popped sector.
 * 
 */
t_sector_lst *sector_pop(t_app *app, t_sector_lst **pop, void (*del)(void *, size_t))
{
	t_sector_lst *prev;
	t_sector_lst *head;

	if(!pop || !(*pop) || (*pop)->member_sectors[0] || !(app->sectors))
		return (NULL);
	prev = NULL;
	head = app->sectors;
	while(head->next && head != *pop)
	{
		prev = head;
		head = head->next;
	}
	if (head == *pop)
	{
		if(prev)
			prev->next = (*pop)->next;
		if(head == app->sectors)
			app->sectors = (*pop)->next;
		sector_delone(pop, del);
		app->active_sector = NULL;
		app->active = NULL;
		app->sectorcount--;
	}
	return (*pop);
}