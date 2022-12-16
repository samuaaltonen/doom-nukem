/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <danielmdc94@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 14:15:51 by saaltone          #+#    #+#             */
/*   Updated: 2022/12/16 13:25:54 by dpalacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * Handles events for key presses (keyup).
 */
int	events_keyup(int keycode, t_app *app)
{
	if (keycode == SDLK_RIGHT)
		app->conf->keystates ^= RIGHT;
	if (keycode == SDLK_LEFT)
		app->conf->keystates ^= LEFT;
	if (keycode == SDLK_UP)
		app->conf->keystates ^= UP;
	if (keycode == SDLK_DOWN)
		app->conf->keystates ^= DOWN;
	if (keycode == SDLK_w)
		app->conf->keystates ^= W;
	if (keycode == SDLK_s)
		app->conf->keystates ^= S;
	if (keycode == SDLK_a)
		app->conf->keystates ^= A;
	if (keycode == SDLK_d)
		app->conf->keystates ^= D;
	if (keycode == SDLK_q)
		app->conf->keystates ^= Q;
	if (keycode == SDLK_e)
		app->conf->keystates ^= E;
	if (keycode == SDLK_r)
		app->conf->keystates ^= R;
	if (keycode == SDLK_c)
		app->conf->keystates ^= C;
	if (keycode == SDLK_LSHIFT)
		app->conf->keystates ^= SHIFT;
	if (keycode == SDLK_LCTRL)
		app->conf->keystates ^= CTRL;
	if (keycode == SDLK_ESCAPE)
		exit(EXIT_SUCCESS);
	if (keycode == SDLK_p)
		app->conf->toggle_loop = ft_toggle(app->conf->toggle_loop);
	if (keycode == SDLK_TAB)
	{
		//----DEBUG FEATURE
		if (app->status == STATUS_GAME || app->status == STATUS_PAUSEMENU)
			pause_game(app);
		if (app->status == STATUS_MAINMENU)
			app->status = STATUS_TITLESCREEN;
		//----
	}
	if (keycode == SDLK_SPACE)
	{
		if (app->status == STATUS_TITLESCREEN)
			app->status = STATUS_MAINMENU;
		//----DEBUG FEATURE
		else if (app->status == STATUS_MAINMENU)
			start_game(app);
		if (app->status == STATUS_GAMEOVER)
			app->status = STATUS_MAINMENU;
		//----
		app->conf->keystates ^= SPACE;
	}
	if (keycode == SDLK_b)
	{
		app->enemies[0].next = ATTACK;
		ft_printf("Set to ATTACK\n");
	}
	return (0);
}

/**
 * Handles events for key presses (keydown).
 */
int	events_keydown(int keycode, t_app *app)
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
	if (keycode == SDLK_c)
		app->conf->keystates |= C;
	if (keycode == SDLK_LSHIFT)
		app->conf->keystates |= SHIFT;
	if (keycode == SDLK_LCTRL)
		app->conf->keystates |= CTRL;
	if (keycode == SDLK_SPACE)
		app->conf->keystates |= SPACE;
	if (keycode == SDLK_f)
		interaction_check(app);
	return (0);
}
