/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_menu.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 14:38:26 by ssulkuma          #+#    #+#             */
/*   Updated: 2022/12/20 13:42:44 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * Mouse click events in the player menu.
*/
void	player_menu_events(t_app *app, t_point	screen_pos)
{
	select_inventory(app, screen_pos);
	select_weapons(app, screen_pos);
}

/**
 * Mouse click events in the interaction menu. If click is outside menu, changes
 * interaction's targer sector to the one clicked (if click's outside sector,
 * targer sector is active sector). Clicking interaction menu changes the
 * event id accordingly. If wall/sector/object had an interaction before,
 * deletes the existing interaction.
*/
void	interaction_menu_events(t_app *app, int start_y, t_point screen_pos)
{
	int		id;
	int		i;

	if (app->current_interaction)
	{
		if (screen_pos.x > HELP_MENU_W)
		{
			app->current_interaction->target_sector = find_child_sector(app);
			if (!app->current_interaction->target_sector)
				app->current_interaction->target_sector = app->active_sector;
		}
		if (check_mouse(screen_pos, (t_rect){90, start_y + 25, 113, 15}))
		{
			if (app->current_interaction->event_id)
			{
				i = find_interaction(app);
				id = i;
				while (id < MAX_INTERACTIONS && app->interactions[i].event_id != 0)
				{
					if (&(app->interactions[id]) == app->current_interaction)
						delete_interaction(app, id);
					id++;
				}
				app->current_interaction = NULL;
				app->interaction_menu = FALSE;
			}
			else
				app->current_interaction->event_id = 0;
		}
		if (check_mouse(screen_pos, (t_rect){100, start_y + 40, 93, 15}))
			app->current_interaction->event_id = 1;
		if (check_mouse(screen_pos, (t_rect){90, start_y + 55, 110, 15}))
			app->current_interaction->event_id = 2;
		if (check_mouse(screen_pos, (t_rect){50, start_y + 70, 183, 15}))
			app->current_interaction->event_id = 3;
		if (check_mouse(screen_pos, (t_rect){125, start_y + 85, 40, 15}))
			app->current_interaction->event_id = 4;
		if (check_mouse(screen_pos, (t_rect){110, start_y + 100, 70, 15}))
			app->current_interaction->event_id = 5;
		if (check_mouse(screen_pos, (t_rect){125, start_y + 115, 40, 15}))
			app->current_interaction->event_id = 6;
		if (check_mouse(screen_pos, (t_rect){102, start_y + 130, 82, 15}))
			app->current_interaction->event_id = 7;
		if (check_mouse(screen_pos, (t_rect){85, start_y + 260, 150, 15}))
			link_interaction(app);
	}
}

/**
 * Mouse click event to activate interaction menu. Checks if click is within
 * the button and finds the right interaction from the array to make changes
 * to.
*/
void	activate_interaction_menu(t_app *app, t_point screen_pos)
{
	int		interaction_id;

	if (check_mouse(screen_pos, (t_rect){25, 210, 15, 15}) && app->object_menu)
	{
		if (!app->current_interaction)
			app->current_interaction = &app->interactions[find_object_interaction(app, app->interaction_count, 0)];
		interaction_id = find_object_interaction(app, find_interaction(app) - 1, 0);
		if (interaction_id < 0)
			return ;
		app->current_interaction = &app->interactions[interaction_id];
		return ;
	}
	if (check_mouse(screen_pos, (t_rect){255, 210, 15, 15}) && app->object_menu)
	{
		if (!app->current_interaction)
			app->current_interaction = &app->interactions[find_object_interaction(app, 0, 1)];
		interaction_id = find_object_interaction(app, find_interaction(app) + 1, 1);
		if (interaction_id < 0)
			return ;
		app->current_interaction = &app->interactions[interaction_id];
		return ;
	}
	if (check_mouse(screen_pos, (t_rect){25, 220, 15, 15}) && app->active)
	{
		if (!app->current_interaction)
			app->current_interaction = &app->interactions[find_decor_interaction(app, app->interaction_count, 0)];
		interaction_id = find_decor_interaction(app, find_interaction(app) - 1, 0);
		if (interaction_id < 0)
			return ;
		app->current_interaction = &app->interactions[interaction_id];
		return ;
	}
	if (check_mouse(screen_pos, (t_rect){255, 220, 15, 15}) && app->active)
	{
		if (!app->current_interaction)
			app->current_interaction = &app->interactions[find_decor_interaction(app, 0, 1)];
		interaction_id = find_decor_interaction(app, find_interaction(app) + 1, 1);
		if (interaction_id < 0)
			return ;
		app->current_interaction = &app->interactions[interaction_id];
		return ;
	}
	if (check_mouse(screen_pos, (t_rect){25, 600, 15, 15})
		&& app->active_sector && !app->active)
	{
		if (!app->current_interaction)
			app->current_interaction = &app->interactions[find_sector_interaction(app, app->interaction_count, 0)];
		interaction_id = find_sector_interaction(app, find_interaction(app) - 1, 0);
		if (interaction_id < 0)
			return ;
		app->current_interaction = &app->interactions[interaction_id];
		return ;
	}
	if (check_mouse(screen_pos, (t_rect){255, 600, 15, 15})
		&& app->active_sector && !app->active)
	{
		if (!app->current_interaction)
			app->current_interaction = &app->interactions[find_sector_interaction(app, 0, 1)];
		interaction_id = find_sector_interaction(app, find_interaction(app) + 1, 1);
		if (interaction_id < 0)
			return ;
		app->current_interaction = &app->interactions[interaction_id];
		return ;
	}
	if (!app->current_interaction && app->object_menu)
		interaction_id = find_object_interaction(app, 0, 1);
	else if (!app->current_interaction && app->active)
		interaction_id = find_decor_interaction(app, 0, 1);
	else if (!app->current_interaction && app->active_sector)
		interaction_id = find_sector_interaction(app, 0, 1);
	else
		interaction_id = find_interaction(app);
	if (interaction_id < 0)
		app->current_interaction = NULL;
	else
		app->current_interaction = &app->interactions[interaction_id];
	if ((check_mouse(screen_pos, (t_rect){42, 228, 190, 16}) && app->object_menu)
		|| (check_mouse(screen_pos, (t_rect){42, 238, 190, 16}) && app->active)
		|| (check_mouse(screen_pos, (t_rect){42, 618, 190, 16}) && app->active_sector))
	{
		if (!app->current_interaction)
			link_interaction(app);
		app->interaction_menu = TRUE;
		
	}
	if ((check_mouse(screen_pos, (t_rect){42, 248, 190, 16}) && app->object_menu)
		|| (check_mouse(screen_pos, (t_rect){42, 258, 200, 20}) && app->active)
		|| (check_mouse(screen_pos, (t_rect){42, 638, 190, 16}) && app->active_sector))
	{
		app->current_interaction = NULL;
		link_interaction(app);
		app->interaction_menu = TRUE;
	}
}
