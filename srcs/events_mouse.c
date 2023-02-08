/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_mouse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 15:40:40 by saaltone          #+#    #+#             */
/*   Updated: 2023/02/08 16:52:24 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * @brief Tracks mouse position and changes player direction and horizon value
 * accordingly.
 * 
 * @param app 
 * @return int 
 */
int	events_mouse_motion(t_app *app)
{
	t_point	delta;

	SDL_GetMouseState(&app->mouse_pos.x, &app->mouse_pos.y);
	if (app->status == STATUS_GAME)
	{
		delta.x = app->event.motion.xrel;
		delta.y = app->event.motion.yrel;
		app->mouse_delta = delta;
		if (delta.x != 0)
			player_rotate(app, (double)delta.x * MOUSE_SENSITIVITY_HORIZONTAL);
		if (delta.y != 0)
			player_horizon(app, (double)delta.y * MOUSE_SENSITIVITY_VERTICAL);
	}
	return (0);
}

/**
 * @brief Mouse key down events.
 * 
 * @param mouse_button 
 * @param app 
 * @return int 
 */
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

/**
 * @brief Mouse key up events.
 * 
 * @param mouse_button 
 * @param app 
 * @return int 
 */
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
