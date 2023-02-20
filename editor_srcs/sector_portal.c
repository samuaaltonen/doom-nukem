/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector_portal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 10:58:22 by ssulkuma          #+#    #+#             */
/*   Updated: 2023/02/20 15:48:29 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * @brief Checks that the wall you're trying to make a portal from, isn't
 * linking to the same sector the wall is in.
 * 
 * @param app
 * @return t_bool
*/
static t_bool	check_if_valid_link(t_app *app)
{
	t_wall_list	*temp;
	t_wall_list	*next;

	temp = app->active_sector->wall_list;
	while (temp)
	{
		if (temp == app->active_last)
			return (FALSE);
		if (temp->next == app->active_sector->wall_list)
			break ;
		next = temp->next;
		temp = next;
	}
	return (TRUE);
}

/**
 * @brief Handles the manual linking event to create a portal. Activate on the
 * currently selected wall, navigate to link target sector, activate again.
 * 
 * @param app
 */
void	link_wall_to_sector(t_app *app)
{
	if (app->list_ongoing || app->list_creation)
	{
		app->portal_selection = FALSE;
		app->active_last = NULL;
	}
	if (app->portal_selection && app->active_last && app->active
		&& app->active->type != -1)
	{
		app->active_last->type = -1;
		app->portal_selection = FALSE;
		app->active_last = NULL;
	}
	else if (app->portal_selection && app->active_sector && app->active_last)
	{
		app->active_last->type = get_sector_id(app, app->active_sector);
		if (!check_if_valid_link(app))
			app->active_last->type = -1;
		app->portal_selection = FALSE;
		app->active_last = NULL;
	}
	else if (!app->portal_selection && app->active)
	{
		app->portal_selection = TRUE;
		app->active_last = app->active;
	}
}

/**
 * @brief Removes all portals to the sector that was deleted.
 * 
 * @param app
 * @param deleted
*/
void	del_sector_portals(t_app *app, int deleted)
{
	t_sector_list	*sector;
	t_wall_list		*wall;

	sector = app->sectors;
	while (sector)
	{
		wall = sector->wall_list;
		while (wall)
		{
			if (wall->type == deleted && !sector->parent_sector)
				wall->type = -1;
			else if (wall->type == deleted && sector->parent_sector)
				wall->type = get_sector_id(app, sector->parent_sector);
			if (wall->type > deleted)
				wall->type--;
			wall = wall->next;
			if (wall == sector->wall_list)
				break ;
		}
		sector = sector->next;
	}
}
