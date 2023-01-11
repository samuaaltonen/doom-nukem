/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_menu.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 14:38:26 by ssulkuma          #+#    #+#             */
/*   Updated: 2023/01/11 13:51:13 by ssulkuma         ###   ########.fr       */
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
 * Changes mouse_down state to true when mouse button left is pressed down.
*/
int	events_mouse_drag(t_app *app)
{
	app->mouse_down = TRUE;
	return (0);
}

/**
 * Changes interaction's event id to 0 (no interaction). If wall/sector/object
 * had an interaction before, deletes the existing interaction.
*/
static void	no_interaction_check(t_app *app)
{
	int		id;
	int		interaction;

	if (app->current_interaction->event_id)
	{
		interaction = find_interaction(app);
		id = interaction;
		while (id < MAX_INTERACTIONS
			&& app->interactions[interaction].event_id != 0)
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

/**
 * Updates the target sector for the current interaction based on mouse click.
*/
static void	update_target_sector(t_app *app)
{
	app->current_interaction->target_sector = find_child_sector(app);
	if (!app->current_interaction->target_sector)
		app->current_interaction->target_sector = click_sector(app);
	if (!app->current_interaction->target_sector)
		app->current_interaction->target_sector = app->active_sector;
}

/**
 * Mouse click events in the interaction menu. If click is outside menu, changes
 * interaction's targer sector to the one clicked (if click's outside sector,
 * targer sector is active sector). Clicking interaction menu changes the
 * event id accordingly.
*/
void	interaction_menu_events(t_app *app, int start_y, t_point screen_pos)
{
	if (screen_pos.x > HELP_MENU_W)
		update_target_sector(app);
	if (check_mouse(screen_pos, (t_rect){90, start_y + 25, 113, 15}))
		no_interaction_check(app);
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
	if (check_mouse(screen_pos, (t_rect){204, start_y + 255, 60, 15})
		&& app->current_interaction->editable == -1)
			app->current_interaction->editable = 0;
	if (check_mouse(screen_pos, (t_rect){187, start_y + 273, 73, 16})
		&& app->current_interaction->editable > -1)
		app->current_interaction->editable = -1;
	if (check_mouse(screen_pos, (t_rect){85, start_y + 300, 150, 15}))
		link_interaction(app);
}
