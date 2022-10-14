/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 14:15:51 by saaltone          #+#    #+#             */
/*   Updated: 2022/10/14 16:17:51 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * Handles events for key presses (keyup).
 */
int	events_keyup(int keycode, t_app *app)
{
	if (keycode == SDLK_RIGHT)
		app->keystates ^= ROTATE_RIGHT_DOWN;
	if (keycode == SDLK_LEFT)
		app->keystates ^= ROTATE_LEFT_DOWN;
	if (keycode == SDLK_UP)
		app->keystates ^= FORWARD_DOWN;
	if (keycode == SDLK_DOWN)
		app->keystates ^= BACKWARD_DOWN;
	if (keycode == SDLK_w)
		app->keystates ^= FORWARD_W_DOWN;
	if (keycode == SDLK_s)
		app->keystates ^= BACKWARD_S_DOWN;
	if (keycode == SDLK_a)
		app->keystates ^= LEFT_DOWN;
	if (keycode == SDLK_d)
		app->keystates ^= RIGHT_DOWN;
	if (keycode == SDLK_ESCAPE)
		exit(EXIT_SUCCESS);
	if (keycode == SDLK_h)
		app->toggle_help = ft_toggle(app->toggle_help);
	if (keycode == SDLK_c)
		app->list_creation = ft_toggle(app->list_creation);
	if (keycode == SDLK_m)
		file_open(app, "./test.test");
	if (keycode == SDLK_o)
		import_file(app, "./test.test");
	return (0);
}

/**
 * Handles events for key presses (keydown).
 */
int	events_keydown(int keycode, t_app *app)
{
	if (keycode == SDLK_RIGHT)
		app->keystates |= ROTATE_RIGHT_DOWN;
	if (keycode == SDLK_LEFT)
		app->keystates |= ROTATE_LEFT_DOWN;
	if (keycode == SDLK_UP)
		app->keystates |= FORWARD_DOWN;
	if (keycode == SDLK_DOWN)
		app->keystates |= BACKWARD_DOWN;
	if (keycode == SDLK_w)
		app->keystates |= FORWARD_W_DOWN;
	if (keycode == SDLK_s)
		app->keystates |= BACKWARD_S_DOWN;
	if (keycode == SDLK_a)
		app->keystates |= LEFT_DOWN;
	if (keycode == SDLK_d)
		app->keystates |= RIGHT_DOWN;
	return (0);
}

void	handle_movement(t_app *app)
{
	if (app->keystates & FORWARD_DOWN
		|| app->keystates & FORWARD_W_DOWN)
		app->view_pos.y += MAP_SPEED;
	if (app->keystates & BACKWARD_DOWN
		|| app->keystates & BACKWARD_S_DOWN)
		app->view_pos.y -= MAP_SPEED;
	if (app->keystates & LEFT_DOWN)
		app->view_pos.x -= MAP_SPEED;
	if (app->keystates & RIGHT_DOWN)
		app->view_pos.x += MAP_SPEED;
}