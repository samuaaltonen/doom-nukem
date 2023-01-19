/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 14:12:05 by ssulkuma          #+#    #+#             */
/*   Updated: 2023/01/19 16:14:43 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * @brief Returns the index of the object given from the objects array.
 * Upon error, returns -1.
 * 
 * @param app
 * @param object
 * @return int
*/
int	get_object_id(t_app *app, t_object *object)
{
	int	i;

	i = 0;
	while (i < MAX_OBJECTS)
	{
		if (&app->objects[i] == object)
			return (i);
		i++;
	}
	return (-1);
}

/**
 * @brief Keydown event to change current object type.
 * 
 * @param app
 * @param keycode
*/
void	change_object_id(t_app *app, int keycode)
{
	if (keycode == SDLK_LEFT && app->current_object->type > 2)
		app->current_object->type--;
	if (keycode == SDLK_RIGHT && app->current_object->type < MAX_UNIQUE_OBJECTS)
		app->current_object->type++;
}

/**
 * @brief Checks if object is valid.
 * 
 * @param app
 * @return t_bool
*/
t_bool	valid_object(t_app *app)
{
	int	i;

	i = 0;
	while (i < MAX_OBJECTS && app->objects[i].type != 0)
	{
		if (app->active_sector == NULL)
			return (FALSE);
		if (ft_cmp_vec2(app->mouse_track, app->objects[i].position))
			return (FALSE);
		if (!inside_sector_check(app->active_sector, &(app->mouse_track)))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

/**
 * @brief Deletes an object and all the interaction it has.
 * 
 * @param app
 * @param id
*/
void	del_object(t_app *app, int id)
{
	int	i;

	i = 0;
	if (app->object_count > 0)
	{
		while (i < MAX_INTERACTIONS)
		{
			if (app->interactions[i].activation_object == &(app->objects[id]))
				delete_interaction(app, find_object_interaction(app, 0, 1));
			if (get_object_id(app, app->interactions[i].activation_object) > id
				&& app->interactions[i].activation_sector == NULL)
				app->interactions[i].activation_object--;
			i++;
		}
		while (id + 1 < MAX_OBJECTS && app->objects[id].type != 0)
		{
			app->objects[id] = app->objects[id + 1];
			id++;
		}
		app->object_count--;
	}
	app->object_menu = FALSE;
	app->current_object = NULL;
}

/**
 * @brief Deletes all objects in the active sector.
 * 
 * @param app
*/
void	del_all_objects_in_sector(t_app *app)
{
	int		id;

	id = app->object_count - 1;
	while (id >= 0)
	{
		if (app->objects[id].sector == app->active_sector)
		{
			app->current_object = &(app->objects[id]);
			app->current_interaction
				= &(app->interactions[find_object_interaction(app, 0, 1)]);
			del_object(app, id);
			app->current_object = NULL;
			app->current_interaction = NULL;
		}
		id--;
	}
}
