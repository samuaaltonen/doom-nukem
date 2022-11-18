/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 13:03:35 by htahvana          #+#    #+#             */
/*   Updated: 2022/11/18 16:53:36 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * @brief check if clicked point is already part of the same list
 * 
 * @param app 
 * @return t_bool 
 */
t_bool	valid_point(t_app *app)
{
	t_vec2_lst	*tmp;

	tmp = app->active;
	while (tmp)
	{
		if (tmp->point.x == app->mouse_track.x
			&& tmp->point.y == app->mouse_track.y)
			return (FALSE);
		if (tmp->next && ft_line_side((t_line)
				{tmp->point, tmp->next->point}, app->mouse_track))
			return (FALSE);
		tmp = tmp->next;
	}
	return (TRUE);
}

/**
 * Handles sector changes depending on active states and pressed keys
 * Up and Down for heights
 * Left and Right for textures
 * U and J for slope heights
 */
void	sector_edit(t_app *app, SDL_Keycode key)
{
	if (key == SDLK_UP)
	{
		if (app->ceiling_edit && !app->slope_edit)
			app->active_sector->ceil_height += HEIGHT_INC;
		if (app->floor_edit && !app->slope_edit)
			app->active_sector->floor_height += HEIGHT_INC;
		if (app->light_edit && app->active_sector->light < 8)
			app->active_sector->light++;
		if (app->slope_edit && app->ceiling_edit)
			app->active_sector->ceil_slope_height += HEIGHT_INC;
		if (app->slope_edit && app->floor_edit)
			app->active_sector->floor_slope_height += HEIGHT_INC;
		if (app->object_menu)
			app->objects[app->object_type].var += app->divider;
	}
	else if (key == SDLK_DOWN)
	{
		if (app->ceiling_edit && !app->slope_edit)
			app->active_sector->ceil_height -= HEIGHT_INC;
		if (app->floor_edit && !app->slope_edit)
			app->active_sector->floor_height -= HEIGHT_INC;
		if (app->light_edit && app->active_sector->light > -8)
			app->active_sector->light--;
		if (app->slope_edit && app->ceiling_edit)
			app->active_sector->ceil_slope_height -= HEIGHT_INC;
		if (app->slope_edit && app->floor_edit)
			app->active_sector->floor_slope_height -= HEIGHT_INC;
		if (app->object_menu)
			app->objects[app->object_type].var -= app->divider;
	}
	else if (key == SDLK_LEFT)
	{
		if (app->active && app->active->tex > 0)
			app->active->tex--;
		if (app->wall_edit && app->active_sector->wall_list->tex > 0
			&& !app->active)
			app->active_sector->wall_list->tex--;
		if (app->ceiling_edit && app->active_sector->ceil_tex > 0)
			app->active_sector->ceil_tex--;
		if (app->floor_edit && app->active_sector->floor_tex > 0)
			app->active_sector->floor_tex--;
		if (app->player.inventory.selected[5])
			change_item_amount(app, key);
		if (app->object_menu && app->objects[app->object_type].type < 1)
			app->objects[app->object_type].type--;
	}
	else if (key == SDLK_RIGHT)
	{
		if (app->active && app->active->tex < MAX_TEX_COUNT)
			app->active->tex++;
		if (app->wall_edit && app->active_sector->wall_list->tex < MAX_TEX_COUNT
			&& !app->active)
			app->active_sector->wall_list->tex++;
		if (app->ceiling_edit && app->active_sector->ceil_tex < MAX_TEX_COUNT)
			app->active_sector->ceil_tex++;
		if (app->floor_edit && app->active_sector->floor_tex < MAX_TEX_COUNT)
			app->active_sector->floor_tex++;
		if (app->player.inventory.selected[5])
			change_item_amount(app, key);
		if (app->object_menu && app->objects[app->object_type].type < MAX_UNIQUE_OBJECTS - 1)
			app->objects[app->object_type].type++;
	}
}
