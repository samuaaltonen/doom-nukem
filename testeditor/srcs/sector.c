/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 13:36:45 by htahvana          #+#    #+#             */
/*   Updated: 2022/10/21 13:41:46 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * Creates a new linked list to save sectors.
 */
t_sector_lst	*new_sector_list(t_vec2list *wall_list)
{
	t_sector_lst	*new;
	t_vec2list		*tmp;

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

