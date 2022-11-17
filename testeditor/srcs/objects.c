/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 15:53:42 by htahvana          #+#    #+#             */
/*   Updated: 2022/11/17 17:34:55 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

int	new_object(t_app *app)
{
	if(app->object_count == MAX_OBJECTS)
		exit_error("MAX OBJECTS reached\n");
	app->objects[app->object_count].type = app->object_type;

	if(app->object_type < 10)
		app->objects[app->object_count].hp = 1;
	else if(app->object_type == 11)
		app->objects[app->object_count].hp = 100;
	else
		app->objects[app->object_count].hp = -1;

	app->objects[app->object_count].position = app->mouse_click;
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
	if(keycode == SDLK_LEFT && app->object_type > 1)
		app->object_type--;
	if(keycode == SDLK_RIGHT && app->object_type < MAX_UNIQUE_OBJECTS)
		app->object_type++;
}
