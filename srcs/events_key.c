/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <danielmdc94@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 14:15:51 by saaltone          #+#    #+#             */
/*   Updated: 2022/10/20 12:32:20 by dpalacio         ###   ########.fr       */
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
	if (keycode == SDLK_e)
		app->conf->toggle_loop = ft_toggle(app->conf->toggle_loop);
	if (keycode == SDLK_SPACE)
	{
		app->game_active = ft_toggle(app->game_active);
		app->title_screen = ft_toggle(app->title_screen);
	}
		
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
	return (0);
}
