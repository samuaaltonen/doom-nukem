/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <danielmdc94@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 15:41:22 by saaltone          #+#    #+#             */
/*   Updated: 2022/12/13 12:54:48 by dpalacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

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
		return (events_mouse_motion(app));
	if (event->type == SDL_MOUSEBUTTONDOWN)
		return (events_mouse_down(event->button.button, app));
	if (event->type == SDL_MOUSEBUTTONUP)
		return (events_mouse_up(event->button.button, app));
	if (event->type == SDL_MOUSEWHEEL)
		return (events_mouse_wheel(event->wheel.y, app));
	if (event->type == SDL_WINDOWEVENT)
		return (events_window_other(event->window.event, app));
	return (0);
}
