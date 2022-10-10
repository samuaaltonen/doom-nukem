/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 14:36:52 by htahvana          #+#    #+#             */
/*   Updated: 2022/10/10 14:42:36 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"


/**
 * converts mouse_pos to world space and snaps to grid
 */
static void	snap_to_nearest(t_app *app, t_point *mouse_pos, t_vector2 *snap_pos)
{
	t_vector2 world_pos;
	double divider = 1.0f;

	world_pos.x = app->view_pos.x + (mouse_pos->x / (double)app->surface->w) * app->zoom_area.x;
	world_pos.y = app->view_pos.y + (mouse_pos->y / (double)app->surface->h) * app->zoom_area.y;
	snap_pos->x = world_pos.x;
	snap_pos->y = world_pos.y;
	double tmp = fabs(fmod(world_pos.x, divider));
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
 * Tracks mouse position and changes player direction accordingly.
 */
int	events_mouse_track(t_app *app)
{
	(void)app;
	t_point	current_pos;
	t_vector2 center;
	
	SDL_GetMouseState(&current_pos.x, &current_pos.y);
	
	center = (t_vector2){0.0,0.0};
	snap_to_nearest(app, &current_pos, &app->mouse_click);
	/* pixel_a.x =  fabs(((a->point.x + data->view_pos.x) / data->zoom_area.x ) * data->surface->w);
	pixel_a.y =  fabs(((a->point.y + data->view_pos.y) / data->zoom_area.y ) * data->surface->h); */

	/* ft_printf("mouse.x=%i, mouse.y=%i, snap.x=%f, snap.y=%f\n" \
	, current_pos.x, current_pos.y, snap_pos.x, snap_pos.y); */
	return (0);
}


int events_mouse_wheel(t_app *app, SDL_Event *event)
{
	if(event->wheel.y > 0)
	{
		app->zoom_area.x *= 2;
		app->zoom_area.y *= 2;
	}	
	else if(event->wheel.y < 0)
	{
		app->zoom_area.x /= 2;
		app->zoom_area.y /= 2;
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