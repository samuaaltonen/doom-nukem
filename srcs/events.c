/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 15:41:22 by saaltone          #+#    #+#             */
/*   Updated: 2022/09/24 01:21:25 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * Handles player movement and direction depending on keystate.
 */
void	handle_movement(t_app *app)
{
	if (app->conf->keystates & FORWARD_DOWN
		|| app->conf->keystates & FORWARD_W_DOWN)
		player_move(app, FORWARD,
			app->conf->movement_speed * app->conf->delta_time);
	if (app->conf->keystates & BACKWARD_DOWN
		|| app->conf->keystates & BACKWARD_S_DOWN)
		player_move(app, BACKWARD,
			app->conf->movement_speed * app->conf->delta_time);
	if (app->conf->keystates & LEFT_DOWN)
		player_move(app, LEFT,
			app->conf->movement_speed * app->conf->delta_time);
	if (app->conf->keystates & RIGHT_DOWN)
		player_move(app, RIGHT,
			app->conf->movement_speed * app->conf->delta_time);
	if (app->conf->keystates & ROTATE_LEFT_DOWN)
		player_rotate(app, -app->conf->rotation_speed * app->conf->delta_time);
	if (app->conf->keystates & ROTATE_RIGHT_DOWN)
		player_rotate(app, app->conf->rotation_speed * app->conf->delta_time);
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
	return (0);
}
