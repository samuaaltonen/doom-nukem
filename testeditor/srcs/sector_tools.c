/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 13:53:18 by htahvana          #+#    #+#             */
/*   Updated: 2022/10/25 10:45:52 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * @brief Get the sector id of the sector parameter
 * 
 * @param app 
 * @param sector 
 * @return int 
 */
int		get_sector_id(t_app *app, t_sector_lst *sector)
{
	t_sector_lst	*tmp;
	int				i;

	i = 0;
	if(!sector)
		return (-1);
	tmp = app->sectors;
	while(tmp != sector)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

/**
 * returns the clicked sector, by checking if 
 */
t_sector_lst *click_sector(t_app *app)
{
	t_sector_lst *tmp;

	tmp = app->sectors;
	while(tmp)
	{
		if(inside_sector_check(app, tmp))
		{
			while (tmp->parent_sector)
			{
				tmp = tmp->parent_sector;
			}
			return (tmp);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

/**
 * Handles the manual linking event using active wall and active sector
 * 
 * activate on a selected wall, navigate to link target sector, activate again
 */
void link_wall_to_sector(t_app *app)
{

	if(app->list_ongoing || app->list_creation)
	{
		app->portal_selection = FALSE; 
		app->active_last = NULL;
	}
		//add check the wall is not in itself
	if(app->portal_selection && app->active_sector && app->active_last)
	{
		app->active_last->type = get_sector_id(app, app->active_sector);
		app->portal_selection = FALSE;
		app->active_last = NULL;
	}
	else if(!app->portal_selection && app->active)
	{
		app->portal_selection = TRUE;
		app->active_last = app->active;
	}
}

/**
 * Returns true if the click is inside a convex sector, checking the point side to all walls
 */
int	inside_sector_check(t_app *app, t_sector_lst *sector)
{
	t_vec2_lst *tmp;

	tmp = sector->wall_list;
	while (tmp)
	{
		if(ft_line_side((t_line){tmp->point, tmp->next->point}, app->mouse_click))
			return (0);
		tmp = tmp->next;
		if(tmp == sector->wall_list)
			break;
	}

	return(1);
}

/**
 * @brief Finds which member sector in active sector was clicked
 * 
 * @param app 
 * @return t_sector_lst* 
 */
t_sector_lst	*find_child_sector(t_app *app)
{
	int				i;
	t_sector_lst	*tmp;

	i = 0;
	while(i < MAX_MEMBER_SECTORS && app->active_sector->member_sectors[i])
	{
		tmp = app->active_sector->member_sectors[i];
		if(inside_sector_check(app, tmp))
			return (tmp);
		i++;
	}
	return (NULL);
}

static void	add_member_sector(t_sector_lst *parent, t_sector_lst *child)
{
	int i;

	i = 0;
	if(parent && child)
	{
		while (parent->member_sectors[i])
			i++;
		if(i >= MAX_MEMBER_SECTORS)
			exit_error("Trying to add too many members\n");
		parent->member_sectors[i] = child;
	}
}

/**
 * @brief Completes an ongoing sector
 * 
 * @param app 
 * @return t_bool 
 */
t_bool	complete_sector(t_app *app)
{
	t_sector_lst *new;

	app->active_last->next = app->active;
	new = put_sector_lst(app,new_sector_list(app->active));
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