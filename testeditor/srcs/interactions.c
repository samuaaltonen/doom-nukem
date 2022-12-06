/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 17:21:39 by htahvana          #+#    #+#             */
/*   Updated: 2022/12/06 14:45:01 by ssulkuma         ###   ########.fr       */
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
		app->current_interaction->activation_sector = app->active_sector;
	else
		return (FALSE);
	app->current_interaction->target_sector = app->active_sector;
	if (app->active_sector->parent_sector)
		app->current_interaction->target_sector = app->active_sector->parent_sector;
	return(TRUE);
}

void	interaction_edit(t_app *app, SDL_Keycode keycode)
{
	if(app->current_interaction)
	{
			if (keycode == SDLK_UP)
			{
				app->current_interaction->variable += app->divider;
			}
			else if (keycode == SDLK_DOWN)
			{
				app->current_interaction->variable -= app->divider;

			}
			else if (keycode == SDLK_LEFT && app->current_interaction->event_id > 0)
			{
				app->current_interaction->event_id--;
			}
			else if (keycode == SDLK_RIGHT && app->current_interaction->event_id < 7)
			{
				app->current_interaction->event_id++;
			}
	}
}

void	link_interaction(t_app *app)
{
	if(app->current_interaction == NULL && app->interaction_count < MAX_INTERACTIONS)
	{
		app->current_interaction = &app->interactions[app->interaction_count];
		if(!new_interaction(app))
		{
			app->current_interaction = NULL;
		}
	}
	else if(app->current_interaction)
	{
		app->current_interaction = NULL;
		app->interaction_menu = FALSE;
		if (app->interactions[app->interaction_count].event_id != 0)
			app->interaction_count++;
	}
}

void	delete_interaction(t_app *app, int id)
{
	if(app->interaction_count > 0)
	{
		if (id < app->interaction_count - 1)
		{
			app->interactions[id] = app->interactions[app->interaction_count - 1];
		}
		app->interactions[app->interaction_count - 1].event_id = 0;
		app->interaction_count--;
	}
}
