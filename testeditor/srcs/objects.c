/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 15:53:42 by htahvana          #+#    #+#             */
/*   Updated: 2022/12/30 14:18:27 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

void	toggle_new_object(t_app *app, t_bool state)
{
	if (state)
	{
		app->object_new = FALSE;
		if (app->object_new && app->current_object)
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
 * Draws the object to the correct position.
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

void	render_objects(t_app *app)
{
	int	i;

	i = 0;
	if (app->object_count > 0)
		ft_printf("object count %i, latest pos x%f,y%f\n", app->object_count, app->objects[app->object_count - 1].position.x, app->objects[app->object_count - 1].position.y);
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

int	new_object(t_app *app)
{
	if (app->object_count == MAX_OBJECTS)
		exit_error("MAX OBJECTS reached\n");
	app->objects[app->object_count].var = 0.f;
	app->objects[app->object_count].position = app->mouse_track;
	app->objects[app->object_count].sector = app->active_sector;
	app->object_count++;
	return (1);
}
