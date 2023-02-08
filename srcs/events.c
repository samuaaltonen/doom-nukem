/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 15:41:22 by saaltone          #+#    #+#             */
/*   Updated: 2023/02/08 16:53:50 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

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
		return (events_keyup(event->key.keysym.sym, app));
	if (event->type == SDL_KEYDOWN)
		return (events_keydown(event->key.keysym.sym, app));
	if (event->type == SDL_MOUSEMOTION)
		return (events_mouse_motion(app));
	if (event->type == SDL_MOUSEBUTTONDOWN)
		return (events_mouse_down(event->button.button, app));
	if (event->type == SDL_MOUSEBUTTONUP)
		return (events_mouse_up(event->button.button, app));
	if (event->type == SDL_WINDOWEVENT)
		return (events_window_other(event->window.event, app));
	return (0);
}

/**
 * @brief Dispatches only window and process related events (used in
 * initialization phase).
 * 
 * @return int 
 */
int	dispatch_event_minimal(t_app *app, SDL_Event *event)
{
	if (event->type == SDL_QUIT)
		return (events_window_destroy());
	if (event->type == SDL_WINDOWEVENT)
		return (events_window_other(event->window.event, app));
	if (event->type == SDL_KEYUP && event->key.keysym.sym == SDLK_ESCAPE)
		exit(EXIT_SUCCESS);
	return (0);
}
