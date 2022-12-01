/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <danielmdc94@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 15:41:22 by saaltone          #+#    #+#             */
/*   Updated: 2022/12/01 10:12:02 by dpalacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * Handles player movement and direction depending on keystate.
 */
void	handle_movement(t_app *app)
{
	if (app->conf->keystates & UP || app->conf->keystates & W)
		player_move(app, FORWARD,
			app->conf->movement_speed * app->conf->delta_time);
	if (app->conf->keystates & DOWN || app->conf->keystates & S)
		player_move(app, BACKWARD,
			app->conf->movement_speed * app->conf->delta_time);
	if (app->conf->keystates & A)
		player_move(app, LEFTWARD,
			app->conf->movement_speed * app->conf->delta_time);
	if (app->conf->keystates & D)
		player_move(app, RIGHTWARD,
			app->conf->movement_speed * app->conf->delta_time);
	if (app->conf->keystates & LEFT)
		player_rotate(app, -app->conf->rotation_speed * app->conf->delta_time);
	if (app->conf->keystates & RIGHT)
		player_rotate(app, app->conf->rotation_speed * app->conf->delta_time);
	if (app->conf->keystates & SPACE)
		player_move(app, UPWARD,
			app->conf->movement_speed * app->conf->delta_time);
	if (app->conf->keystates & CTRL)
		player_move(app, DOWNWARD,
			app->conf->movement_speed * app->conf->delta_time);
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
