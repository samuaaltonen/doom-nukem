/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 13:03:35 by htahvana          #+#    #+#             */
/*   Updated: 2023/01/04 14:50:13 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * Handles sector changes for the up arrow keypress.
*/
static void	edit_up_key_changes(t_app *app, double increment)
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

/**
 * Handles sector changes for the down arrow keypress.
*/
static void	edit_down_key_changes(t_app *app, double increment)
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
		edit_up_key_changes(app, increment);
	else if (key == SDLK_DOWN)
		edit_down_key_changes(app, increment);
	else if (key == SDLK_LEFT)
		edit_left_key_changes(app, key);
	else if (key == SDLK_RIGHT)
		edit_right_key_changes(app, key);
}
