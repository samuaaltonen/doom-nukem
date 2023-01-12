/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 17:21:39 by htahvana          #+#    #+#             */
/*   Updated: 2023/01/12 14:32:15 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * Creates a new interaction on either the sector, wall decor or object.
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
	app->current_interaction->editable = -1;
	return (TRUE);
}

/**
 * Key events to change the interaction variable and editable.
*/
void	interaction_edit(t_app *app, SDL_Keycode keycode)
{
	int	id;

	if (!app->current_interaction)
		return ;
	id = (int)app->current_interaction->editable;
	if (keycode == SDLK_UP)
		app->current_interaction->variable += app->divider;
	else if (keycode == SDLK_DOWN)
		app->current_interaction->variable -= app->divider;
	else if (keycode == SDLK_LEFT && app->current_interaction->editable > 0.0)
	{
		app->current_interaction->editable -= 1.0;
		while (app->interactions[id].event_id == 0
			&& app->current_interaction->editable > 1.0)
			app->current_interaction->editable -= 1.0;
	}
	else if (keycode == SDLK_RIGHT
		&& get_current_interaction_count(app, id) < app->interaction_count)
	{
		id++;
		while (app->interactions[id].event_id == 0 && id < MAX_INTERACTIONS)
			id++;
		app->current_interaction->editable = (double)id;
	}
}

/**
 * Finds the next free spot in the interaction array and creates a new
 * interaction to that index.
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
 * If there's no current interaction, creates a new one. If there is a current
 * interaction, saves it to the next free spot in the interaction array.
*/
void	link_interaction(t_app *app)
{
	if (app->current_interaction == NULL
		&& app->interaction_count < MAX_INTERACTIONS)
		no_current_interaction(app);
	else if (app->current_interaction)
	{
		app->current_interaction = NULL;
		app->interaction_menu = FALSE;
		if (app->interactions[app->interaction_count].event_id != 0)
			app->interaction_count++;
	}
}

/**
 * Deletes the interaction on the index you give it and removes the links to
 * that interaction as well.
*/
void	delete_interaction(t_app *app, int id)
{
	int		i;

	if (id < 0 || id >= MAX_INTERACTIONS)
		return ;
	app->interaction_count--;
	app->interactions[id].event_id = 0;
	app->interactions[id].variable = 0;
	app->interactions[id].editable = -1;
	app->interactions[id].target_sector = NULL;
	app->interactions[id].activation_sector = NULL;
	app->interactions[id].activation_wall = NULL;
	app->interactions[id].activation_object = NULL;
	i = 0;
	while (i < MAX_INTERACTIONS)
	{
		if ((int)app->interactions[i].editable == id)
			app->interactions[i].editable = -1;
		i++;
	}
}
