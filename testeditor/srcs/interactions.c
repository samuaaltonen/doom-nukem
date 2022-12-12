/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 17:21:39 by htahvana          #+#    #+#             */
/*   Updated: 2022/12/09 14:25:21 by ssulkuma         ###   ########.fr       */
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
		{
			ft_printf("{cyan}Linking interaction.{reset}\n");
			app->interaction_count++;
		}
		else
			ft_printf("{red}Interaction event is 0.{reset}\n");
	}
}

void	delete_interaction(t_app *app, int id)
{
	if (app->interaction_count > 0 && id > -1)
	{
		while (id < app->interaction_count)
		{
			app->interactions[id] = app->interactions[id + 1];
			id++;
		}
		app->interactions[id].event_id = 0;
		app->interactions[id].variable = 0;
		app->interactions[id].target_sector = NULL;
		app->interactions[id].activation_sector = NULL;
		app->interactions[id].activation_wall = NULL;
		app->interactions[id].activation_object = NULL;
		app->interaction_count--;
	}
}
