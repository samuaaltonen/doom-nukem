/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 15:53:42 by htahvana          #+#    #+#             */
/*   Updated: 2022/11/21 13:22:37 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"


void	toggle_new_object(t_app *app, t_bool state)
{
	if(state)
	{
		app->object_new = FALSE;
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

}

t_bool	valid_object(t_app *app)
{
	int	i;

	i = 0;
	while (i < MAX_OBJECTS && app->objects[i].type != 0)
	{
		if(ft_cmp_vec2(app->mouse_track, app->objects[i].position))
			return (FALSE);
		if(!inside_sector_check(app->active_sector, &(app->mouse_track)))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

t_bool	select_object(t_app *app)
{
	int	id;

	id = 0;

	while (id < MAX_OBJECTS && app->objects[id].type != 0)
	{
		if(app->mouse_track.x == app->objects[id].position.x
			&& app->mouse_track.y == app->objects[id].position.y)
		{
			app->current_object = &app->objects[id];
			return (TRUE);
		}
		id++;
	}
	return (FALSE);
	
}

int		get_object_id(t_app *app, t_object *object)
{
	int	i;

	i = 0;
	while (i < MAX_OBJECTS)
	{
		if(&app->objects[i] == object)
			return (i);
		i++;
	}
	return (-1);
}

/**
 * Draws the object to the correct position.
*/
void	draw_object_icon(t_app *app, t_vector2 world_pos, int id)
{
	t_point screen_pos;

	screen_pos = world_to_screen(app,world_pos);
	blit_surface(app->assets.sprite,&(t_rect){ICON_SIZE * id, 0, ICON_SIZE, ICON_SIZE},app->surface,&(t_rect){screen_pos.x,screen_pos.y,OBJECT_SCREEN_SIZE,OBJECT_SCREEN_SIZE});
}

void	render_objects(t_app *app)
{
	int i;

	i = 0;
	if(app->object_count > 0)
		ft_printf("object count %i, latest pos x%f,y%f\n", app->object_count, app->objects[app->object_count - 1].position.x,app->objects[app->object_count - 1].position.y );
	while (i < app->object_count)
	{
		if(app->objects[i].type == 0)
			return ;
		draw_object_icon(app, app->objects[i].position, app->objects[i].type);
		i++;
	}
}

int	new_object(t_app *app)
{
	if(app->object_count == MAX_OBJECTS)
		exit_error("MAX OBJECTS reached\n");
	app->objects[app->object_count].var = 0.f;
	app->objects[app->object_count].position = app->mouse_track;
	app->objects[app->object_count].sector = app->active_sector;
	app->object_count++;
	return (1);
}

void	del_object(t_app *app, int object_id)
{
	int	i;

	i = 0;
	if(app->object_count > 0)
	{
		while(i < MAX_INTERACTIONS && app->interactions[i].event_id != 0)
		{
			if(app->interactions[i].activation_sector == NULL)
				app->interactions[i].activation_id--;
			i++;
		}

		while(object_id + 1 < MAX_OBJECTS && app->objects[object_id].type != 0)
		{
			app->objects[object_id] = app->objects[object_id + 1];
			object_id++;
		}
		app->object_count--;
	}
}

void	change_object_id(t_app *app, int keycode)
{
	if(keycode == SDLK_LEFT && app->current_object->type > 1)
		app->current_object->type--;
	if(keycode == SDLK_RIGHT && app->current_object->type < MAX_UNIQUE_OBJECTS)
		app->current_object->type++;
}
