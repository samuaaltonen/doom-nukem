/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <danielmdc94@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 15:14:08 by saaltone          #+#    #+#             */
/*   Updated: 2022/12/07 18:25:02 by dpalacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * @brief Main game loop. Polls SDL event queue until it is empty and then 
 * proceeds to next frame.
 * 
 * @param app 
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
 * @brief Rendering function to be called in app loop. Calls individual renderers and
 * draws resulting image(s) to the window.
 * 
 * @param app 
 */
void	render_frame(t_app *app)
{
	flush_surface(app->surface);
	update_fps_counter(app);
	if (app->status == STATUS_TITLESCREEN)
		render_titlescreen(app);
	else if (app->status == STATUS_MAINMENU)
		render_mainmenu(app);
	else if (app->status == STATUS_GAME)
		render_game(app);
	else if (app->status == STATUS_PAUSEMENU)
		render_pausemenu(app);
	else if (app->status == STATUS_MAINOPTIONS
		|| app->status == STATUS_GAMEOPTIONS)
		render_options(app);
	else if (app->status == STATUS_GAMEOVER)
		render_gameover(app);
	SDL_UpdateWindowSurface(app->win);
}
