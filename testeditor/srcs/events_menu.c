/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_menu.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 14:38:26 by ssulkuma          #+#    #+#             */
/*   Updated: 2022/12/02 15:44:17 by ssulkuma         ###   ########.fr       */
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
	if (screen_pos.x > HELP_MENU_W)
	{
		app->current_interaction->target_sector = click_sector(app);
		if (!app->current_interaction->target_sector)
			app->current_interaction->target_sector = app->active_sector;
	}
	if (check_mouse(screen_pos, (t_rect){90, start_y + 25, 113, 15}))
	{
		if (app->current_interaction->event_id)
			delete_interaction(app, find_interaction(app));
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

/**
 * Mouse click event to activate interaction menu. Checks if click is within
 * the button and finds the right interaction from the array to make changes
 * to.
*/
void	activate_interaction_menu(t_app *app, t_point screen_pos)
{
	int		active;
	int		interaction_id;

	if (check_mouse(screen_pos, (t_rect){42, 238, 190, 16}) && app->active)
		active = 1;
	else if (check_mouse(screen_pos, (t_rect){42, 228, 190, 16})
		&& app->object_menu)
		active = 2;
	else if (check_mouse(screen_pos, (t_rect){42, 238, 190, 16})
		&& app->active_sector)
		active = 3;
	else
		return ;
	app->interaction_menu = TRUE;
	if (active == 1)
		interaction_id = find_decor_interaction(app);
	else if (active == 2)
		interaction_id = find_object_interaction(app);
	else
		interaction_id = 1; //find_sector_interaction(app);
	if (interaction_id != -1)
		app->current_interaction = &app->interactions[interaction_id];
	else
		link_interaction(app);
}
