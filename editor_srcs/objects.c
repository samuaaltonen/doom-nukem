/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 15:53:42 by htahvana          #+#    #+#             */
/*   Updated: 2023/01/18 15:02:32 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * @brief Toggles the object_new state between true and false, updating the
 * current object along it.
 * 
 * @param app
 * @param state
*/
void	toggle_new_object(t_app *app, t_bool state)
{
	if (state)
	{
		app->object_new = FALSE;
		app->current_object = NULL;
	}
	else
	{
		app->object_new = TRUE;
		app->current_object = &app->objects[app->object_count];
		app->current_object->type = 1;
	}
	app->object_menu = FALSE;
	app->current_interaction = NULL;
}

/**
 * @brief Checks if mouse position matches to any of the object positions and
 * sets the selected object to current object.
 * 
 * @param app
 * @return t_bool
*/
t_bool	select_object(t_app *app)
{
	int	id;

	id = 0;
	while (id < MAX_OBJECTS && app->objects[id].type != 0)
	{
		if (app->mouse_track.x == app->objects[id].position.x
			&& app->mouse_track.y == app->objects[id].position.y)
		{
			app->current_object = &app->objects[id];
			return (TRUE);
		}
		id++;
	}
	return (FALSE);
}

/**
 * @brief Draws the object to the correct position.
 * 
 * @param app
 * @param world_pos
 * @param id
*/
void	draw_object_icon(t_app *app, t_vector2 world_pos, int id)
{
	t_point	screen_pos;

	screen_pos = world_to_screen(app, world_pos);
	blit_surface(app->assets.objects, &(t_rect){0, TEX_SIZE * (id - 1),
		TEX_SIZE, TEX_SIZE}, app->surface, &(t_rect){screen_pos.x
		- OBJECT_SCREEN_SIZE / 2, screen_pos.y - OBJECT_SCREEN_SIZE / 2,
		OBJECT_SCREEN_SIZE, OBJECT_SCREEN_SIZE});
}

/**
 * @brief Renders the objects and if the object has an interaction, the 
 * colored square behind it.
 * 
 * @param app
*/
void	render_objects(t_app *app)
{
	int	i;

	i = 0;
	while (i < app->object_count)
	{
		if (app->objects[i].type == 0)
			return ;
		if (interaction_object_check(app, i))
			render_point(app, app->objects[i].position, 9, INTERACTION);
		draw_object_icon(app, app->objects[i].position, app->objects[i].type);
		i++;
	}
}

/**
 * @brief Creates a new object, sets its variables accordingly and saves
 * it to the object array.
 * 
 * @param app
 * @return int
*/
int	new_object(t_app *app)
{
	if (app->object_count == MAX_OBJECTS)
		exit_error("MAX OBJECTS reached\n");
	app->objects[app->object_count].var = 0.f;
	app->objects[app->object_count].position = app->mouse_track;
	app->objects[app->object_count].sector = app->active_sector;
	app->object_count++;
	return (TRUE);
}