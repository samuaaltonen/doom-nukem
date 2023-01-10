/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 17:21:39 by htahvana          #+#    #+#             */
/*   Updated: 2023/01/10 17:24:56 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

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
	return (TRUE);
}

void	interaction_edit(t_app *app, SDL_Keycode keycode)
{
	if (app->current_interaction)
	{
		if (keycode == SDLK_UP)
			app->current_interaction->variable += app->divider;
		else if (keycode == SDLK_DOWN)
			app->current_interaction->variable -= app->divider;
		else if (keycode == SDLK_LEFT && app->link_interaction
			&& app->current_interaction->editable > 0)
		{
			app->current_interaction->editable--;
			while (app->interactions[(int)app->current_interaction->editable].event_id == 0 && app->current_interaction->editable > 1)
				app->current_interaction->editable--;
		}
		else if (keycode == SDLK_RIGHT && app->link_interaction
			&& app->current_interaction->editable < MAX_INTERACTIONS)
		{
			app->current_interaction->editable++;
			while (app->interactions[(int)app->current_interaction->editable].event_id == 0 && app->current_interaction->editable < MAX_INTERACTIONS)
				app->current_interaction->editable++;
		}
		if (app->var_edit)
		{
			if (keycode == SDLK_UP)
				app->current_interaction->editable += app->divider;
			else if (keycode == SDLK_DOWN)
				app->current_interaction->editable -= app->divider;
		}
	}
}

void	link_interaction(t_app *app)
{
	int	i;

	if (app->current_interaction == NULL
		&& app->interaction_count < MAX_INTERACTIONS)
	{
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
	else if (app->current_interaction)
	{
		app->current_interaction = NULL;
		app->interaction_menu = FALSE;
		app->link_interaction = FALSE;
		if (app->interactions[app->interaction_count].event_id != 0)
			app->interaction_count++;
	}
}

void	delete_interaction(t_app *app, int id)
{
	if (id < 0 || id >= MAX_INTERACTIONS)
		return ;
	app->interaction_count--;
	app->interactions[id].event_id = 0;
	app->interactions[id].variable = 0;
	app->interactions[id].target_sector = NULL;
	app->interactions[id].activation_sector = NULL;
	app->interactions[id].activation_wall = NULL;
	app->interactions[id].activation_object = NULL;
}
