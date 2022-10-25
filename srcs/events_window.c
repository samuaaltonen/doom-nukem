/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_window.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <danielmdc94@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 14:13:33 by saaltone          #+#    #+#             */
/*   Updated: 2022/10/24 17:28:05 by dpalacio         ###   ########.fr       */
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
		if (app->status == STATUS_GAME)
			SDL_WarpMouseInWindow(app->win, WIN_W / 2, WIN_H / 2);
	}
	if (windowevent == SDL_WINDOWEVENT_CLOSE)
		exit(EXIT_SUCCESS);
	return (0);
}
