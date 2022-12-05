/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_mouse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 14:02:41 by htahvana          #+#    #+#             */
/*   Updated: 2022/12/02 15:48:40 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * Left mouse click events when list creation is toggled on. Creates a
 * linked list from the clicked points, checking that their position is valid
 * and completes the drawn sector.
*/
static int	list_creation_events(t_app *app)
{
	t_vec2_lst	*tmp;

	if (!app->list_ongoing)
	{
		app->active = new_vector_list(&app->mouse_track);
		app->active_last = app->active;
		app->list_ongoing = TRUE;
	}
	else
	{
		if (app->mouse_track.x == app->active->point.x
			&& app->mouse_track.y == app->active->point.y)
			return (complete_sector(app));
		else if (valid_point(app))
		{
			tmp = new_vector_list(&app->mouse_track);
			put_to_vector_list(&app->active, tmp);
			app->active_last = tmp;
		}
	}
	return (0);
}

/**
 * Left mouse click events when there's an active sector. If player edit mode
 * is toggled on, places player on map. If object is clicked, selcts object
 * and changes menu to object menu. Clicking member sectors selects them as
 * active sector.
*/
static void	active_sector_events(t_app *app)
{
	if (app->player_edit)
	{
		app->player.position = app->mouse_track;
		app->player.direction = (t_vector2){0.f,1.f};
		app->player.sector = app->active_sector;
		app->player_edit = FALSE;
		check_player_position(app);
	}
	else if (select_object(app))
		app->object_menu = TRUE;
	else if (app->active_sector->member_sectors[0]
		&& find_child_sector(app))
		app->active_sector = find_child_sector(app);
	app->active = find_clicked_vector(app);
}

/**
 * All the events happening from left mouse click.
*/
static int	left_click_events(t_app *app, t_point screen_pos)
{
	if (app->list_creation)
		return (list_creation_events(app));
	else if (app->object_new)
	{
		if (valid_object(app))
			new_object(app);
		app->object_new = FALSE;
	}
	else if (app->player_menu)
		player_menu_events(app, screen_pos);
	else if (app->interaction_menu && app->current_interaction)
		interaction_menu_events(app, 40, screen_pos);
	else if (!app->active_sector && app->mouse_track.x == app->player.position.x
		&& app->mouse_track.y == app->player.position.y)
		app->player_menu = TRUE;
	else if (check_mouse(screen_pos, (t_rect){0, 0, HELP_MENU_W, WIN_H})
		&& !app->interaction_menu)
		activate_interaction_menu(app, screen_pos);
	else if (app->active_sector)
		active_sector_events(app);
	else
		app->active_sector = click_sector(app);
	return (0);
}

/**
 * All events happening from mouse button up.
 */
int	events_mouse_click(t_app *app, SDL_Event *event)
{
	t_point		screen_pos;

	app->mouse_down = FALSE;
	SDL_GetMouseState(&screen_pos.x, &screen_pos.y);
	if (event->button.button == SDL_BUTTON_LEFT)
		return (left_click_events(app, screen_pos));
	else
	{
		if (app->list_ongoing)
			cancel_list_creation(app);
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

/**
 * Changes mouse_down state to true when mouse button left is pressed down.
*/
int	events_mouse_drag(t_app *app)
{
	app->mouse_down = TRUE;
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
