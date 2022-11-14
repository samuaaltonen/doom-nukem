/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 15:14:08 by saaltone          #+#    #+#             */
/*   Updated: 2022/11/14 16:21:23 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * Main game loop. Polls SDL event queue until it is empty and then 
 * proceeds to next frame.
 */
void	app_loop(t_app *app)
{
	while (TRUE)
	{
		while (SDL_PollEvent(&app->event))
			dispatch_event(app, &app->event);
		if (!app->conf->toggle_loop)
			render_frame(app);
	}
}



/**
 * Rendering function to be called in loop hook. Calls individual renderers and
 * draws resulting image(s) to the window.
 */
void	render_frame(t_app *app)
{
	/* flush_surface(app->surface); */
	update_fps_counter(app);
	if (app->status == STATUS_TITLESCREEN)
		render_titlescreen(app);
	else if (app->status == STATUS_MAINMENU)
		render_mainmenu(app);
	else if (app->status == STATUS_GAME)
		render_game(app);
	else if (app->status == STATUS_PAUSEMENU)
		render_pausemenu(app);
	SDL_UpdateWindowSurface(app->win);
}
