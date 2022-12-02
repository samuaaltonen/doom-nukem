/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_mouse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 14:02:41 by htahvana          #+#    #+#             */
/*   Updated: 2022/12/01 16:31:48 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * Mouse click events in the player menu. Clicking on arrows next to icons
 * changes the selected weapon/armor.
*/
static void	player_menu_events(t_app *app)
{
	t_point	screen_pos;

	SDL_GetMouseState(&screen_pos.x, &screen_pos.y);
	if (check_mouse(screen_pos, (t_rect){20, 67, 10, 10})
		&& app->player.selected_weapon > 0)
		app->player.selected_weapon--;
	if (check_mouse(screen_pos, (t_rect){250, 67, 10, 10})
		&& app->player.selected_weapon < (MAX_WEAPONS - 1))
		app->player.selected_weapon++;
	select_inventory(app, screen_pos);
	select_weapons(app, screen_pos);
}

/**
 * Mouse click events in the interaction menu.
*/
static void	interaction_menu_events(t_app *app, int start_y, t_point screen_pos)
{
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
 * if not in sector creation, select points
 * else add new points to list or starts a new list
 */
int	events_mouse_click(t_app *app, SDL_Event *event)
{
	t_vec2_lst	*tmp;
	t_point		screen_pos;
	int			interaction_id;

	SDL_GetMouseState(&screen_pos.x, &screen_pos.y);
	app->mouse_down = 0;
	if (event->button.button == SDL_BUTTON_LEFT && !app->list_ongoing && app->list_creation)
	{
		app->active = new_vector_list(&app->mouse_track);
		app->active_last = app->active;
		app->list_ongoing = TRUE;
	}
	else if ((event->button.button == SDL_BUTTON_RIGHT
			|| event->button.button == SDL_BUTTON_MIDDLE) && app->list_ongoing)
		cancel_list_creation(app);
	else if (event->button.button == SDL_BUTTON_LEFT && app->list_ongoing)
	{
		if (app->mouse_track.x == app->active->point.x && app->mouse_track.y == app->active->point.y)
			return (complete_sector(app));
		else if (valid_point(app))
		{
			tmp = new_vector_list(&app->mouse_track);
			put_to_vector_list(&app->active, tmp);
			app->active_last = tmp;
		}
	}
	else if (event->button.button == SDL_BUTTON_LEFT && app->object_new)
	{
		if(valid_object(app))
		{
			new_object(app);
		}
		app->object_new = FALSE;
	}
	else if (event->button.button == SDL_BUTTON_LEFT && app->interaction_menu
		&& app->current_interaction && screen_pos.x > HELP_MENU_W)
	{
		app->current_interaction->target_sector = click_sector(app);
		if (!app->current_interaction->target_sector)
			app->current_interaction->target_sector = app->active_sector;
	}
	else if (event->button.button == SDL_BUTTON_LEFT && app->active
		&& check_mouse(screen_pos, (t_rect){0, 0, HELP_MENU_W, WIN_H})
		&& !app->interaction_menu)
	{
		if (check_mouse(screen_pos, (t_rect){42, 238, 190, 16}))
		{
			app->interaction_menu = TRUE;
			interaction_id = find_decor_interaction(app);
			if (interaction_id != -1)
				app->current_interaction = &app->interactions[interaction_id];
			else
				link_interaction(app);
		}
	}
	else if (event->button.button == SDL_BUTTON_LEFT)
	{
		//if active sector has member sectors find them before linees
		if (!app->active_sector && app->mouse_track.x == app->player.position.x
			&& app->mouse_track.y == app->player.position.y)
			app->player_menu = TRUE;
		else if (app->interaction_menu && app->current_interaction)
			interaction_menu_events(app, 40, screen_pos);
		else if (app->active_sector)
		{
			if (app->player_edit)
			{
				app->player.position = app->mouse_track;
				app->player.direction = (t_vector2){0.f,1.f};
				app->player.sector = app->active_sector;
				app->player_edit = FALSE;
				check_player_position(app);
			}
			else if(select_object(app))
			{
				app->object_menu = TRUE;
			}
			else if (app->active_sector->member_sectors[0] && find_child_sector(app))
				app->active_sector = find_child_sector(app);
			app->active = find_clicked_vector(app);
		}
		else if (app->player_menu)
			player_menu_events(app);
		else
			app->active_sector = click_sector(app);
	}
	else
	{
		if (app->interaction_menu)
				link_interaction(app);
		toggle_new_object(app, TRUE);
		app->active = NULL;
		app->player_menu = FALSE;
		app->object_menu = FALSE;
		if (app->active_sector)
			app->active_sector = app->active_sector->parent_sector;
		else
			app->active_sector = NULL;
	}
	return (0);
}

int	events_mouse_drag(t_app *app)
{
	app->mouse_down = 1;
	return (0);
}

/**
 * Cancels the ungoing list creation and deletes the incomplete sector list.
*/
void	cancel_list_creation(t_app *app)
{
	del_vector_list(&(app->active));
	app->active = NULL;
	app->active_last = NULL;
	app->list_ongoing = FALSE;
	app->list_creation = FALSE;
}

/**
 * converts mouse_pos to world space and snaps to grid
 */
void	snap_to_nearest(t_app *app, t_point *mouse_pos, t_vector2 *snap_pos, double divider)
{
	t_vector2	world_pos;
	double		tmp;

	world_pos.x = app->view_pos.x + (mouse_pos->x / (double)app->surface->w) * app->zoom_area.x;
	world_pos.y = app->view_pos.y + (mouse_pos->y / (double)app->surface->h) * app->zoom_area.y;
	snap_pos->x = world_pos.x;
	snap_pos->y = world_pos.y;
	tmp = fabs(fmod(world_pos.x, divider));
	if (tmp < (divider / 2))
	{
		if (world_pos.x < 0)
			snap_pos->x = world_pos.x + tmp;
		else
			snap_pos->x = world_pos.x - tmp;
	}
	else
	{
		if (world_pos.x < 0)
			snap_pos->x = world_pos.x - (divider - tmp);
		else
			snap_pos->x = world_pos.x + (divider - tmp);
	}
	tmp = fabs(fmod(world_pos.y, divider));
	if (tmp < (divider / 2))
	{
		if (world_pos.y < 0)
			snap_pos->y = world_pos.y + tmp;
		else
			snap_pos->y = world_pos.y - tmp;
	}
	else
	{
		if (world_pos.y < 0)
			snap_pos->y = world_pos.y - (divider - tmp);
		else
			snap_pos->y = world_pos.y + (divider - tmp);
	}
}
