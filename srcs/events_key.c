/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 14:15:51 by saaltone          #+#    #+#             */
/*   Updated: 2023/02/14 15:56:20 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * @brief Handles events for movement key presses.
 * 
 * @param keycode 
 * @param app 
 * @return int 
 */
static void	event_keyup_movement(int keycode, t_app *app)
{
	if (keycode == SDLK_RIGHT && app->conf->keystates & RIGHT)
		app->conf->keystates ^= RIGHT;
	if (keycode == SDLK_LEFT && app->conf->keystates & LEFT)
		app->conf->keystates ^= LEFT;
	if (keycode == SDLK_UP && app->conf->keystates & UP)
		app->conf->keystates ^= UP;
	if (keycode == SDLK_DOWN && app->conf->keystates & DOWN)
		app->conf->keystates ^= DOWN;
	if (keycode == SDLK_w && app->conf->keystates & W)
		app->conf->keystates ^= W;
	if (keycode == SDLK_a && app->conf->keystates & A)
		app->conf->keystates ^= A;
	if (keycode == SDLK_s && app->conf->keystates & S)
		app->conf->keystates ^= S;
	if (keycode == SDLK_d && app->conf->keystates & D)
		app->conf->keystates ^= D;
	if (keycode == SDLK_LSHIFT && app->conf->keystates & SHIFT)
		app->conf->keystates ^= SHIFT;
	if (keycode == SDLK_LCTRL && app->conf->keystates & CTRL)
		app->conf->keystates ^= CTRL;
}

/**
 * @brief Handles keyup events related to game states.
 * 
 * @param keycode 
 * @param app 
 */
static void	events_keyup_status(int keycode, t_app *app)
{
	if (keycode == SDLK_TAB)
	{
		if (app->status == STATUS_GAME || app->status == STATUS_PAUSEMENU)
			pause_game(app);
		if (app->status == STATUS_MAINMENU)
			app->status = STATUS_TITLESCREEN;
	}
	if (keycode == SDLK_SPACE && app->conf->keystates & SPACE)
	{
		if (app->status == STATUS_TITLESCREEN)
			app->status = STATUS_MAINMENU;
		else if (app->status == STATUS_MAINMENU)
			start_game(app);
		if (app->status == STATUS_GAMEOVER)
			app->status = STATUS_MAINMENU;
		app->conf->keystates ^= SPACE;
	}
}

/**
 * @brief Handles events for key presses (keyup).
 * 
 * @param keycode 
 * @param app 
 * @return int 
 */
int	events_keyup(int keycode, t_app *app)
{
	if (keycode == SDLK_ESCAPE)
		exit(EXIT_SUCCESS);
	event_keyup_movement(keycode, app);
	if (keycode == SDLK_q && app->conf->keystates & Q)
		app->conf->keystates ^= Q;
	if (keycode == SDLK_e && app->conf->keystates & E)
		app->conf->keystates ^= E;
	if (keycode == SDLK_r && app->conf->keystates & R)
		app->conf->keystates ^= R;
	if (app->player.inventory.jetpack && app->conf->keystates & C
		&& keycode == SDLK_c)
		app->conf->keystates ^= C;
	events_keyup_status(keycode, app);
	if (keycode == SDLK_9)
		app->player.inventory.ammo += 50;
	return (0);
}

/**
 * @brief Handles keydown events for movement.
 * 
 */
static void	events_keydown_movement(int keycode, t_app *app)
{
	if (keycode == SDLK_RIGHT)
		app->conf->keystates |= RIGHT;
	if (keycode == SDLK_LEFT)
		app->conf->keystates |= LEFT;
	if (keycode == SDLK_UP)
		app->conf->keystates |= UP;
	if (keycode == SDLK_DOWN)
		app->conf->keystates |= DOWN;
	if (keycode == SDLK_w)
		app->conf->keystates |= W;
	if (keycode == SDLK_s)
		app->conf->keystates |= S;
	if (keycode == SDLK_a)
		app->conf->keystates |= A;
	if (keycode == SDLK_d)
		app->conf->keystates |= D;
}

/**
 * @brief Handles events for key presses (keydown).
 * 
 * @param keycode 
 * @param app 
 * @return int 
 */
int	events_keydown(int keycode, t_app *app)
{
	events_keydown_movement(keycode, app);
	if (keycode == SDLK_u)
		app->conf->fov--;
	if (keycode == SDLK_u || keycode == SDLK_i)
		init_camera_plane(app);
	if (keycode == SDLK_q)
		app->conf->keystates |= Q;
	if (keycode == SDLK_e)
		app->conf->keystates |= E;
	if (keycode == SDLK_r)
		app->conf->keystates |= R;
	if (app->player.inventory.jetpack
		&& app->player.inventory.energy && keycode == SDLK_c)
		jetpack(app);
	if (keycode == SDLK_LSHIFT)
		app->conf->keystates |= SHIFT;
	if (keycode == SDLK_LCTRL)
		app->conf->keystates |= CTRL;
	if (keycode == SDLK_SPACE)
		app->conf->keystates |= SPACE;
	if (keycode == SDLK_f)
		interaction_check(app);
	if (keycode == SDLK_3 || keycode == SDLK_2 || keycode == SDLK_1)
		weapon(app, keycode);
	return (0);
}
