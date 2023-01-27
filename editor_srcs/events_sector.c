/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_sector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 15:49:10 by ssulkuma          #+#    #+#             */
/*   Updated: 2023/01/26 13:16:19 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * @brief Handles sector texture changes for the left arrow keypress.
 * 
 * @param app
*/
static void	edit_left_key_tex_changes(t_app *app)
{
	if (app->active_sector && app->wall_edit && !app->active)
	{
		app->active_sector->wall_list->tex--;
		if (app->active_sector->wall_list->tex < 0)
			app->active_sector->wall_list->tex = MAX_TEX_COUNT - 1;
	}
	if (app->active_sector && app->ceiling_edit)
	{
		app->active_sector->ceil_tex--;
		if (app->active_sector->ceil_tex < 0)
			app->active_sector->ceil_tex = MAX_TEX_COUNT - 1;
	}
	if (app->active_sector && app->floor_edit)
	{
		app->active_sector->floor_tex--;
		if (app->active_sector->floor_tex < 0)
			app->active_sector->floor_tex = MAX_TEX_COUNT - 1;
	}
}

/**
 * @brief Handles sector changes for the left arrow keypress.
 * 
 * @param app
 * @param keycode
*/
void	edit_left_key_changes(t_app *app, SDL_Keycode keycode)
{
	edit_left_key_tex_changes(app);
	if (app->active && app->decor_edit && !app->floor_edit
		&& !app->ceiling_edit && app->active->decor != -1)
		app->active->decor_offset.x -= app->divider;
	if (app->active && !app->decor_edit)
	{
		app->active->tex--;
		if (app->active->tex < 0)
			app->active->tex = MAX_TEX_COUNT - 1;
	}
	if (app->player_menu)
		change_item_amount(app, keycode);
	if (app->current_object && (app->object_menu || app->object_new))
	{
		app->current_object->type--;
		if (app->current_object->type <= 0)
			app->current_object->type = MAX_UNIQUE_OBJECTS;
	}
}

/**
 * @brief Handles sector texture changes for the right arrow keypress.
 * 
 * @param app
*/
static void	edit_right_key_tex_changes(t_app *app)
{
	if (app->active_sector && app->wall_edit && !app->active)
	{
		app->active_sector->wall_list->tex++;
		if (app->active_sector->wall_list->tex >= MAX_TEX_COUNT)
			app->active_sector->wall_list->tex = 0;
	}
	if (app->active_sector && app->ceiling_edit)
	{
		app->active_sector->ceil_tex++;
		if (app->active_sector->ceil_tex >= MAX_TEX_COUNT)
			app->active_sector->ceil_tex = 0;
	}
	if (app->active_sector && app->floor_edit)
	{
		app->active_sector->floor_tex++;
		if (app->active_sector->floor_tex >= MAX_TEX_COUNT)
			app->active_sector->floor_tex = 0;
	}
}

/**
 * @brief Handles sector changes for the right arrow keypress.
 * 
 * @param app
 * @param keycode
*/
void	edit_right_key_changes(t_app *app, SDL_Keycode keycode)
{
	edit_right_key_tex_changes(app);
	if (app->decor_edit && app->active && !app->floor_edit
		&& !app->ceiling_edit && app->active->decor != -1)
		app->active->decor_offset.x += app->divider;
	if (!app->decor_edit && app->active)
	{
		app->active->tex++;
		if (app->active->tex >= MAX_TEX_COUNT)
			app->active->tex = 0;
	}
	if (app->player_menu)
		change_item_amount(app, keycode);
	if (app->current_object && (app->object_menu || app->object_new))
	{
		app->current_object->type++;
		if (app->current_object->type > MAX_UNIQUE_OBJECTS)
			app->current_object->type = 1;
	}
}
