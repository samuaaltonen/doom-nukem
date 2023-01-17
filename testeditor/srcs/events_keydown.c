/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_keydown.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 16:43:51 by ssulkuma          #+#    #+#             */
/*   Updated: 2023/01/13 14:08:08 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * @brief Events for arrow keys.
 * 
 * @param app
 * @param keycode
 */
static void	handle_arrow_keys(t_app *app, int keycode)
{
	if (app->current_interaction && app->interaction_menu)
	{
		interaction_edit(app, keycode);
		return ;
	}
	if (keycode == SDLK_RIGHT)
		sector_edit(app, keycode);
	if (keycode == SDLK_LEFT)
		sector_edit(app, keycode);
	if (keycode == SDLK_UP)
		sector_edit(app, keycode);
	if (keycode == SDLK_DOWN)
		sector_edit(app, keycode);
}

/**
 * @brief Handles events for key presses (keydown).
 * 
 * @param app
 * @param keycode
 * @return int
 */
int	events_keydown(t_app *app, int keycode)
{
	handle_arrow_keys(app, keycode);
	if (keycode == SDLK_w)
		app->keystates |= FORWARD_W_DOWN;
	if (keycode == SDLK_s)
		app->keystates |= BACKWARD_S_DOWN;
	if (keycode == SDLK_a)
		app->keystates |= LEFT_DOWN;
	if (keycode == SDLK_d)
		app->keystates |= RIGHT_DOWN;
	if (keycode == SDLK_LSHIFT)
		app->keystates |= SHIFT_DOWN;
	return (0);
}
