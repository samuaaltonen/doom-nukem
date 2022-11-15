/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 14:36:52 by htahvana          #+#    #+#             */
/*   Updated: 2022/11/15 10:59:28 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * Tracks mouse position and saves the snapped location to t_app
 */
int	events_mouse_track(t_app *app)
{
	t_point	current_pos;

	SDL_GetMouseState(&current_pos.x, &current_pos.y);
	snap_to_nearest(app, &current_pos, &app->mouse_track, app->divider);
	if (app->mouse_down && current_pos.y > 280 && current_pos.y < 300
		&& current_pos.x > 40 && current_pos.x <= 240 && app->player_menu)
			app->player.health = current_pos.x - 40;
	return (0);
}

/**
 * @brief Finds which point in active sector was clicked
 * 
 * @param app 
 * @return t_vec2_lst* 
 */
t_vec2_lst	*find_clicked_vector(t_app *app)
{
	t_vec2_lst		*found;

	if (app->active_sector)
	{
		found = app->active_sector->wall_list;
		while (found)
		{
			if (app->mouse_track.x == found->point.x
				&& app->mouse_track.y == found->point.y)
				return (found);
			if (found->next == app->active_sector->wall_list)
				break ;
			found = found->next;
		}
	}
	return (NULL);
}

/**
 * Mouse scroll zoom
 */
int	events_mouse_wheel(t_app *app, SDL_Event *event)
{
	if (event->wheel.y > 0 && app->zoom_area.x < 200)
	{
		app->zoom_area.x *= 2;
		app->zoom_area.y *= 2;
		app->view_pos.x *= 2;
		app->view_pos.y *= 2;
		app->zoom_range += 1;
		app->movement_speed /= 2;
	}	
	else if (event->wheel.y < 0 && app->zoom_area.x > 6)
	{
		app->zoom_area.x /= 2;
		app->zoom_area.y /= 2;
		app->view_pos.x /= 2;
		app->view_pos.y /= 2;
		app->zoom_range -= 1;
		app->movement_speed *= 2;
	}
	return (0);
}

/**
 * Dispatches SDL2 event to event handler functions.
*/
int	dispatch_event(t_app *app, SDL_Event *event)
{
	if (event->type == SDL_QUIT)
		return (events_window_destroy());
	if (event->type == SDL_KEYUP)
		return (events_keyup(event->key.keysym.sym, app));
	if (event->type == SDL_KEYDOWN)
		return (events_keydown(event->key.keysym.sym, app));
	if (event->type == SDL_MOUSEMOTION)
		return (events_mouse_track(app));
	if (event->type == SDL_MOUSEWHEEL)
		return (events_mouse_wheel(app, event));
	if (event->type == SDL_MOUSEBUTTONUP)
		return (events_mouse_click(app, event));
	if (event->type == SDL_MOUSEBUTTONDOWN)
		return (events_mouse_drag(app));
	return (0);
}
