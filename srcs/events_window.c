/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_window.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 14:13:33 by saaltone          #+#    #+#             */
/*   Updated: 2022/09/27 20:19:21 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * Exits the application when window is destroyed.
 */
int	events_window_destroy(void)
{
	exit(EXIT_SUCCESS);
	return (0);
}

/**
 * Handles other window related events.
 */
int	events_window_other(int windowevent, t_app *app)
{
	if (windowevent == SDL_WINDOWEVENT_FOCUS_LOST)
		app->conf->mouse_active = FALSE;
	if (windowevent == SDL_WINDOWEVENT_FOCUS_GAINED)
	{
		app->conf->mouse_active = TRUE;
		SDL_WarpMouseInWindow(app->win, WIN_W / 2, WIN_H / 2);
	}
	if (windowevent == SDL_WINDOWEVENT_CLOSE)
		exit(EXIT_SUCCESS);
	return (0);
}
