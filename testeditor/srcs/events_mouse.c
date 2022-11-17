/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_mouse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 14:02:41 by htahvana          #+#    #+#             */
/*   Updated: 2022/11/17 17:32:43 by htahvana         ###   ########.fr       */
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
	if (check_mouse(screen_pos, (t_rect){20, 193, 10, 10})
		&& app->player.selected_armor > 0)
		app->player.selected_armor--;
	if (check_mouse(screen_pos, (t_rect){250, 193, 10, 10})
		&& app->player.selected_armor < (MAX_ARMOR - 1))
		app->player.selected_armor++;
	select_inventory(app, screen_pos);
	app->player.inventory.selected[5] = check_selected_inventory(app);
}

/**
 * if not in sector creation, select points
 * else add new points to list or starts a new list
 */
int	events_mouse_click(t_app *app, SDL_Event *event)
{
	t_vec2_lst	*tmp;

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
	else if (event->button.button == SDL_BUTTON_LEFT)
	{
		//if active sector has member sectors find them before linees
		if (!app->active_sector && app->mouse_track.x == app->player.position.x
			&& app->mouse_track.y == app->player.position.y)
			app->player_menu = 1;
		else if (app->active_sector)
		{
			if (app->active_sector->member_sectors[0] && find_child_sector(app))
				app->active_sector = find_child_sector(app);
			app->active = find_clicked_vector(app);
		}
		else if (app->player_edit)
		{
			app->mouse_click = app->mouse_track;
			app->player.sector = get_sector_id(app, click_sector(app));
			render_player(app);
			app->player_edit = FALSE;
		}
		else if (app->object_edit)
		{
			app->mouse_click = app->mouse_track;
			new_object(app);
			app->object_edit = FALSE;
		}
		else if (app->player_menu)
			player_menu_events(app);
		else
			app->active_sector = click_sector(app);
	}
	else
	{
		app->object_type = 0;
		app->active = NULL;
		app->player_menu = 0;
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
