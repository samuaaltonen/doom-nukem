/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_dispatch.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 19:04:50 by saaltone          #+#    #+#             */
/*   Updated: 2023/01/19 18:21:02 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * @brief Dispatches SDL2 event to event handler functions.
 * 
 * @param app 
 * @param event 
 * @return int 
 */
int	dispatch_event(t_app *app, SDL_Event *event)
{
	if (event->type == SDL_QUIT)
		return (events_window_destroy());
	if (event->type == SDL_KEYUP)
		return (events_keyup(app, event->key.keysym.sym));
	if (event->type == SDL_KEYDOWN)
		return (events_keydown(app, event->key.keysym.sym));
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

/**
 * @brief Dispatches only window and process related events (used in
 * initialization phase).
 * 
 * @return int 
 */
int	dispatch_event_minimal(SDL_Event *event)
{
	if (event->type == SDL_QUIT)
		return (events_window_destroy());
	if (event->type == SDL_KEYUP && event->key.keysym.sym == SDLK_ESCAPE)
		exit(EXIT_SUCCESS);
	return (0);
}
