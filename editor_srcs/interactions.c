/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 17:21:39 by htahvana          #+#    #+#             */
/*   Updated: 2023/02/20 14:00:27 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * @brief Creates a new interaction on either the sector, wall decor or object.
 * 
 * @param app
 * @return t_bool
*/
static t_bool	new_interaction(t_app *app)
{
	if (app->object_menu)
		app->current_interaction->activation_object = app->current_object;
	else if (app->active)
	{
		if (app->active->decor == -1)
			return (FALSE);
		app->current_interaction->activation_sector = app->active_sector;
		app->current_interaction->activation_wall = app->active;
	}
	else if (app->active_sector)
	{
		app->current_interaction->activation_sector = app->active_sector;
		app->current_interaction->activation_wall = NULL;
	}
	else
		return (FALSE);
	app->current_interaction->target_sector = app->active_sector;
	if (app->active_sector->parent_sector)
		app->current_interaction->target_sector
			= app->active_sector->parent_sector;
	app->current_interaction->interaction_link = -1;
	return (TRUE);
}

/**
 * @brief Key events to change the interaction variable and interaction link.
 * 
 * @param app
 * @param keycode
*/
void	interaction_edit(t_app *app, SDL_Keycode keycode)
{
	int	id;

	if (!app->current_interaction)
		return ;
	id = app->current_interaction->interaction_link;
	if (keycode == SDLK_UP)
		app->current_interaction->variable += app->divider;
	else if (keycode == SDLK_DOWN)
		app->current_interaction->variable -= app->divider;
	else if (keycode == SDLK_LEFT
		&& get_current_interaction_count(app, id) > 1)
	{
		id--;
		while (app->interactions[id].event_id == 0 && id > 0)
			id--;
		app->current_interaction->interaction_link = id;
	}
	else if (keycode == SDLK_RIGHT
		&& get_current_interaction_count(app, id) < app->interaction_count)
	{
		id++;
		while (app->interactions[id].event_id == 0 && id < MAX_INTERACTIONS)
			id++;
		app->current_interaction->interaction_link = id;
	}
}

/**
 * @brief Finds the next free spot in the interaction array and creates a new
 * interaction to that index.
 * 
 * @param app
*/
static void	no_current_interaction(t_app *app)
{
	int		i;

	i = 0;
	while (i < MAX_INTERACTIONS)
	{
		if (!app->interactions[i].event_id)
		{
			app->current_interaction = &app->interactions[i];
			break ;
		}
		i++;
	}
	if (!app->current_interaction)
	{
		app->interaction_menu = FALSE;
		return ;
	}
	if (!new_interaction(app))
		app->current_interaction = NULL;
}

/**
 * @brief If there's no current interaction, creates a new one. If there is a
 * current interaction, saves it to the next free spot in the interaction array.
 * 
 * @param app
*/
void	link_interaction(t_app *app)
{
	if (app->current_interaction == NULL
		&& app->interaction_count < MAX_INTERACTIONS)
		no_current_interaction(app);
	else if (app->current_interaction)
	{
		if (!app->current_interaction->event_id)
			delete_interaction(app, find_interaction(app));
		app->interaction_count = get_interaction_count(app);
		app->current_interaction = NULL;
		app->interaction_menu = FALSE;
	}
}

/**
 * @brief Deletes the interaction on the index you give it and removes the links
 * to that interaction as well.
 * 
 * @param app
 * @param id
*/
void	delete_interaction(t_app *app, int id)
{
	int		i;

	if (id < 0 || id >= MAX_INTERACTIONS)
		return ;
	app->interaction_count--;
	app->interactions[id].event_id = 0;
	app->interactions[id].variable = 0;
	app->interactions[id].interaction_link = -1;
	app->interactions[id].target_sector = NULL;
	app->interactions[id].activation_sector = NULL;
	app->interactions[id].activation_wall = NULL;
	app->interactions[id].activation_object = NULL;
	app->interactions[id].requires_key = FALSE;
	i = 0;
	while (i < MAX_INTERACTIONS)
	{
		if (app->interactions[i].interaction_link == id)
			app->interactions[i].interaction_link = -1;
		i++;
	}
}
