/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 14:36:52 by htahvana          #+#    #+#             */
/*   Updated: 2022/10/10 14:07:17 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * Tracks mouse position and changes player direction accordingly.
 */
int	events_mouse_track(t_app *app)
{
	(void)app;
	t_point	current_pos;
	
	SDL_GetMouseState(&current_pos.x, &current_pos.y);
	return (0);
}


int events_mouse_wheel(t_app *app, SDL_Event *event)
{
	if(event->wheel.y > 0 && app->zoom_area.x < 100)
	{
		app->zoom_area.x *= 2;
		app->zoom_area.y *= 2;
	}	
	else if(event->wheel.y < 0 && app->zoom_area.x > 3)
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