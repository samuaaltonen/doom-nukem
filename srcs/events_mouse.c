/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_mouse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <danielmdc94@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 15:40:40 by saaltone          #+#    #+#             */
/*   Updated: 2022/11/17 15:02:42 by dpalacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * Tracks mouse position and changes player direction accordingly.
 */
int	events_mouse_motion(t_app *app)
{
	t_point	delta;

	SDL_GetMouseState(&app->mouse_pos.x, &app->mouse_pos.y);
	if (app->status == STATUS_GAME)
	{
		delta.x = app->event.motion.xrel;
		delta.y = app->event.motion.yrel;
		if (delta.x != 0)
			player_rotate(app,
				(double) delta.x * MOUSE_SENSITIVITY_HORIZONTAL
				* app->conf->delta_time);
		if (delta.y != 0)
		{
			app->player.horizon -= delta.y * MOUSE_SENSITIVITY_VERTICAL
				* app->conf->delta_time;
			if (app->player.horizon > HORIZON_UPPER_LIMIT)
				app->player.horizon = HORIZON_UPPER_LIMIT;
			if (app->player.horizon < HORIZON_LOWER_LIMIT)
				app->player.horizon = HORIZON_LOWER_LIMIT;
		}
	}
	return (0);
}

int	events_mouse_down(int mouse_button, t_app *app)
{
	if (mouse_button == SDL_BUTTON_LEFT)
		app->conf->buttonstates |= LEFT_MOUSE;
	if (mouse_button == SDL_BUTTON_RIGHT)
		app->conf->buttonstates |= RIGHT_MOUSE;
	if (mouse_button == SDL_BUTTON_MIDDLE)
		app->conf->buttonstates |= MIDDLE_MOUSE;
	return (0);
}

int	events_mouse_up(int mouse_button, t_app *app)
{
	if (mouse_button == SDL_BUTTON_LEFT)
		app->conf->buttonstates ^= LEFT_MOUSE;
	if (mouse_button == SDL_BUTTON_RIGHT)
		app->conf->buttonstates ^= RIGHT_MOUSE;
	if (mouse_button == SDL_BUTTON_MIDDLE)
		app->conf->buttonstates ^= MIDDLE_MOUSE;
	return (0);
}
