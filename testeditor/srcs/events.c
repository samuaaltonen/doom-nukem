/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 14:36:52 by htahvana          #+#    #+#             */
/*   Updated: 2022/10/11 15:57:01 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * converts mouse_pos to world space and snaps to grid
 */
static void	snap_to_nearest(t_app *app, t_point *mouse_pos, t_vector2 *snap_pos, double divider)
{
	t_vector2	world_pos;
	double		tmp;

	world_pos.x = app->view_pos.x + (mouse_pos->x / (double)app->surface->w) * app->zoom_area.x;
	world_pos.y = app->view_pos.y + (mouse_pos->y / (double)app->surface->h) * app->zoom_area.y;
	snap_pos->x = world_pos.x;
	snap_pos->y = world_pos.y;
	tmp = fabs(fmod(world_pos.x, divider));
	if(tmp < (divider / 2))
	{
		if(world_pos.x < 0)
			snap_pos->x = world_pos.x + tmp;
		else
			snap_pos->x = world_pos.x - tmp;
	}
	else
	{
		if(world_pos.x < 0)
			snap_pos->x = world_pos.x - (divider - tmp);
		else
			snap_pos->x = world_pos.x + (divider - tmp);
	}
	tmp = fabs(fmod(world_pos.y, divider));
	if(tmp < (divider / 2))
	{
		if(world_pos.y < 0)
			snap_pos->y = world_pos.y + tmp;
		else
			snap_pos->y = world_pos.y - tmp;
	}
	else
	{
		if(world_pos.y < 0)
			snap_pos->y = world_pos.y - (divider - tmp);
		else
			snap_pos->y = world_pos.y + (divider - tmp);
	}
}

/**
 * Tracks mouse position and saves the snapped location to t_app
 */
int	events_mouse_track(t_app *app)
{
	t_point	current_pos;
	
	SDL_GetMouseState(&current_pos.x, &current_pos.y);
	snap_to_nearest(app, &current_pos, &app->mouse_click, app->divider);
	ft_printf("x=%f, y=%f\n",app->mouse_click.x, app->mouse_click.y);
	return (0);
}


/**
 * Mouse scroll zoom
 */
int events_mouse_wheel(t_app *app, SDL_Event *event)
{
	if(event->wheel.y > 0 && app->zoom_area.x < 200)
	{
		app->zoom_area.x *= 2;
		app->zoom_area.y *= 2;
		app->view_pos.x *= 2;
		app->view_pos.y *= 2;
		app->zoom_range += 1;
	}	
	else if(event->wheel.y < 0 && app->zoom_area.x > 6)
	{
		app->zoom_area.x /= 2;
		app->zoom_area.y /= 2;
		app->view_pos.x /= 2;
		app->view_pos.y /= 2;
		app->zoom_range -= 1;
	}
	return (0);
}

/**
 * Dispatches SDL2 event to event handler functions.
*/
int	dispatch_event(t_app *app, SDL_Event *event)
{
	if (event->type == SDL_QUIT)
		return events_window_destroy();
	if (event->type == SDL_KEYUP)
		return events_keyup(event->key.keysym.sym, app);
	if (event->type == SDL_KEYDOWN)
		return events_keydown(event->key.keysym.sym, app);
	if (event->type == SDL_MOUSEMOTION)
		return events_mouse_track(app);
	if (event->type == SDL_MOUSEWHEEL)
		return events_mouse_wheel(app, event);	
	return (0);
}
