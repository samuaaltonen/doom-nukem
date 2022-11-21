/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 17:21:39 by htahvana          #+#    #+#             */
/*   Updated: 2022/11/21 14:42:19 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

static t_bool	new_interaction(t_app *app)
{
	if (app->object_menu)
	{
		app->current_interaction->activation_id = app->current_object;
	}
	else if (app->active)
	{
		app->current_interaction->activation_sector = app->active_sector;
		app->current_interaction->activation_wall = app->active;
	}
	else if (app->active_sector)
	{
		app->current_interaction->activation_sector = app->active_sector;
	}
	else
		return (FALSE);
	app->current_object = NULL;
	app->object_menu = FALSE;
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
			else if (keycode == SDLK_LEFT && app->current_interaction->event_id > 1)
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
		if(app->active_sector)
			app->current_interaction->target_sector = app->active_sector;
		app->current_interaction = NULL;
		app->interaction_count++;
	}
}

void	delete_interaction(t_app *app, int id)
{
	if(app->interaction_count > 0)
	{
		while(id + 1 < MAX_INTERACTIONS && app->interactions[id].event_id != 0)
		{
			app->interactions[id] = app->interactions[id + 1];
			id++;
		}
		app->interaction_count--;
	}
}
