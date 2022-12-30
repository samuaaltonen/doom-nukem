/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 13:03:35 by htahvana          #+#    #+#             */
/*   Updated: 2022/12/30 10:54:30 by ssulkuma         ###   ########.fr       */
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
	double	increment;

	increment = HEIGHT_INC;
	if (app->keystates & SHIFT_DOWN)
		increment = app->divider;
	if (key == SDLK_UP)
	{
		if (app->ceiling_edit && !app->slope_edit)
			app->active_sector->ceil_height += increment;
		if (app->floor_edit && !app->slope_edit)
			app->active_sector->floor_height += increment;
		if (!app->decor_edit && app->active && !app->floor_edit
			&& !app->ceiling_edit)
		{
			app->active->decor++;
			if (app->active->decor > MAX_DECOR)
			{
				app->active->decor = -1;
				del_all_decor_interactions(app);
			}
		}
		if (app->decor_edit && app->active && !app->floor_edit
			&& !app->ceiling_edit && app->active->decor != -1)
			app->active->decor_offset.y += app->divider;
		if (app->light_edit && app->active_sector->light < 8)
			app->active_sector->light++;
		if (app->slope_edit && app->ceiling_edit)
			app->active_sector->ceil_slope_height += increment;
		if (app->slope_edit && app->floor_edit)
			app->active_sector->floor_slope_height += increment;
		if (app->object_menu)
			app->current_object->var += app->divider;
	}
	else if (key == SDLK_DOWN)
	{
		if (app->ceiling_edit && !app->slope_edit)
			app->active_sector->ceil_height -= increment;
		if (app->floor_edit && !app->slope_edit)
			app->active_sector->floor_height -= increment;
		if (!app->decor_edit && app->active && !app->floor_edit
			&& !app->ceiling_edit)
		{
			app->active->decor--;
			if (app->active->decor == -1)
				del_all_decor_interactions(app);
			if (app->active->decor < -1)
				app->active->decor = MAX_DECOR;
		}
		if (app->decor_edit && app->active && !app->floor_edit
			&& !app->ceiling_edit && app->active->decor != -1)
			app->active->decor_offset.y -= app->divider;
		if (app->light_edit && app->active_sector->light > -8)
			app->active_sector->light--;
		if (app->slope_edit && app->ceiling_edit)
			app->active_sector->ceil_slope_height -= increment;
		if (app->slope_edit && app->floor_edit)
			app->active_sector->floor_slope_height -= increment;
		if (app->object_menu)
			app->current_object->var -= app->divider;
	}
	else if (key == SDLK_LEFT)
	{
		if (!app->decor_edit && app->active)
		{
			app->active->tex--;
			if (app->active->tex < 0)
				app->active->tex = MAX_TEX_COUNT - 1;
		}
		if (app->wall_edit && !app->active)
		{
			app->active_sector->wall_list->tex--;
			if (app->active_sector->wall_list->tex < 0)
				app->active_sector->wall_list->tex = MAX_TEX_COUNT - 1;
		}
		if (app->decor_edit && app->active && !app->floor_edit
			&& !app->ceiling_edit && app->active->decor != -1)
			app->active->decor_offset.x -= app->divider;
		if (app->ceiling_edit)
		{
			app->active_sector->ceil_tex--;
			if (app->active_sector->ceil_tex < 0)
				app->active_sector->ceil_tex = MAX_TEX_COUNT - 1;
		}
		if (app->floor_edit)
		{
			app->active_sector->floor_tex--;
			if (app->active_sector->floor_tex < 0)
				app->active_sector->floor_tex = MAX_TEX_COUNT - 1;
		}
		if (app->player_menu)
			change_item_amount(app, key);
		if (app->object_menu || app->object_new)
		{
			app->current_object->type--;
			if (app->current_object->type < 0)
				app->current_object->type = MAX_UNIQUE_OBJECTS - 1;
		}
	}
	else if (key == SDLK_RIGHT)
	{
		if (!app->decor_edit && app->active)
		{
			app->active->tex++;
			if (app->active->tex >= MAX_TEX_COUNT)
				app->active->tex = 0;
		}
		if (app->wall_edit && !app->active)
		{
			app->active_sector->wall_list->tex++;
			if (app->active_sector->wall_list->tex >= MAX_TEX_COUNT)
				app->active_sector->wall_list->tex = 0;
		}
		if (app->decor_edit && app->active && !app->floor_edit
			&& !app->ceiling_edit && app->active->decor != -1)
			app->active->decor_offset.x += app->divider;
		if (app->ceiling_edit)
		{
			app->active_sector->ceil_tex++;
			if (app->active_sector->ceil_tex >= MAX_TEX_COUNT)
				app->active_sector->ceil_tex = 0;
		}
		if (app->floor_edit)
		{
			app->active_sector->floor_tex++;
			if (app->active_sector->floor_tex >= MAX_TEX_COUNT)
				app->active_sector->floor_tex = 0;
		}
		if (app->player_menu)
			change_item_amount(app, key);
		if (app->object_menu || app->object_new)
		{
			app->current_object->type++;
			if (app->current_object->type >= MAX_UNIQUE_OBJECTS)
				app->current_object->type = 0;
		}
	}
}
