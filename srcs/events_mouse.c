/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_mouse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 15:40:40 by saaltone          #+#    #+#             */
/*   Updated: 2022/10/04 16:57:28 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * Tracks mouse position and changes player direction accordingly.
 */
int	events_mouse_track(t_app *app)
{
	t_point	current_pos;
	t_point	delta;

	if (!app->conf->mouse_active)
		return (0);
	SDL_GetMouseState(&current_pos.x, &current_pos.y);
	delta.x = current_pos.x - WIN_W / 2;
	if (delta.x != 0)
		player_rotate(app,
			(double) delta.x / MOUSE_SENSITIVITY * app->conf->delta_time);
	SDL_WarpMouseInWindow(app->win, WIN_W / 2, WIN_H / 2);
	return (0);
}
