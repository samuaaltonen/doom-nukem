/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 15:53:42 by htahvana          #+#    #+#             */
/*   Updated: 2023/02/22 12:41:41 by saaltone         ###   ########.fr       */
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
		if (app->current_object && !app->object_menu)
			app->current_object->type = 0;
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
		if (ft_vector_compare(app->mouse_track, app->objects[id].position))
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
	int		size;

	size = 6 / app->zoom_range;
	screen_pos = world_to_screen(app, world_pos);
	blit_surface(app->assets.objects, &(t_rect){0, TEX_SIZE * (id - 1),
		TEX_SIZE, TEX_SIZE}, app->surface, &(t_rect){screen_pos.x
		- (OBJECT_SCREEN_SIZE * size) / 2, screen_pos.y - (OBJECT_SCREEN_SIZE
			* size) / 2, OBJECT_SCREEN_SIZE * size, OBJECT_SCREEN_SIZE * size});
}

/**
 * @brief Renders the objects and if the object has an interaction, the 
 * colored square behind it.
 * 
 * @param app
*/
void	render_objects(t_app *app)
{
	int		i;
	int		size;

	size = 6 / app->zoom_range;
	i = 0;
	while (i < app->object_count)
	{
		if (app->objects[i].type == 0)
			return ;
		if (interaction_object_check(app, i))
			render_point(app, app->objects[i].position, 9 * size, INTERACTION);
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
	app->objects[app->object_count].var = 0.f;
	app->objects[app->object_count].position = app->mouse_track;
	app->objects[app->object_count].sector = app->active_sector;
	app->object_count++;
	app->current_object = NULL;
	if (app->object_count >= MAX_OBJECTS)
		exit_error(MSG_ERROR_OBJECT_LIMIT);
	return (TRUE);
}
