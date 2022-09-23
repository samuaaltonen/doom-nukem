/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 14:15:51 by saaltone          #+#    #+#             */
/*   Updated: 2022/08/08 17:21:39 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * Handles events for key presses (keyup).
 */
int	events_keyup(int keycode, t_app *app)
{
	if (keycode == SDLK_RIGHT)
		app->conf->keystates ^= ROTATE_RIGHT_DOWN;
	if (keycode == SDLK_LEFT)
		app->conf->keystates ^= ROTATE_LEFT_DOWN;
	if (keycode == SDLK_UP)
		app->conf->keystates ^= FORWARD_DOWN;
	if (keycode == SDLK_DOWN)
		app->conf->keystates ^= BACKWARD_DOWN;
	if (keycode == SDLK_w)
		app->conf->keystates ^= FORWARD_W_DOWN;
	if (keycode == SDLK_s)
		app->conf->keystates ^= BACKWARD_S_DOWN;
	if (keycode == SDLK_a)
		app->conf->keystates ^= LEFT_DOWN;
	if (keycode == SDLK_d)
		app->conf->keystates ^= RIGHT_DOWN;
	if (keycode == SDLK_ESCAPE)
		exit(EXIT_SUCCESS);
	if (keycode == SDLK_h)
		app->conf->toggle_help = ft_toggle(app->conf->toggle_help);
	return (0);
}

/**
 * Handles events for key presses (keydown).
 */
int	events_keydown(int keycode, t_app *app)
{
	if (keycode == SDLK_RIGHT)
		app->conf->keystates |= ROTATE_RIGHT_DOWN;
	if (keycode == SDLK_LEFT)
		app->conf->keystates |= ROTATE_LEFT_DOWN;
	if (keycode == SDLK_UP)
		app->conf->keystates |= FORWARD_DOWN;
	if (keycode == SDLK_DOWN)
		app->conf->keystates |= BACKWARD_DOWN;
	if (keycode == SDLK_w)
		app->conf->keystates |= FORWARD_W_DOWN;
	if (keycode == SDLK_s)
		app->conf->keystates |= BACKWARD_S_DOWN;
	if (keycode == SDLK_a)
		app->conf->keystates |= LEFT_DOWN;
	if (keycode == SDLK_d)
		app->conf->keystates |= RIGHT_DOWN;
	if (keycode == SDLK_u)
		app->conf->fov--;
	if (keycode == SDLK_i)
		app->conf->fov++;
	if (keycode == SDLK_u || keycode == SDLK_i)
		init_camera_plane(app);
	app_render(app);
	return (0);
}
