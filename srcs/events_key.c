/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 14:15:51 by saaltone          #+#    #+#             */
/*   Updated: 2023/01/04 14:16:50 by htahvana         ###   ########.fr       */
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
	if (keycode == SDLK_7)
	{
		app->enemies[1].next = ATTACK;
		app->enemies[0].next = ATTACK;
		ft_printf("Set to ATTACK\n");
		fire(app,(t_vector3){app->player.dir.x, app->player.dir.y,-(app->player.horizon - 0.75f)},(t_vector3){app->player.pos.x, app->player.pos.y,app->player.elevation},(t_point){11,app->player.sector});
	}
		if (keycode == SDLK_8)
	{
		app->enemies[1].next = DEATH;
		app->enemies[0].next = DEATH;
		ft_printf("Set to DEATH\n");
	}
		if (keycode == SDLK_9)
	{
		app->enemies[1].next = WALK;
		app->enemies[0].next = WALK;
		ft_printf("Set to WALK\n");
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
