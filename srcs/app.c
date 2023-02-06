/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 15:14:08 by saaltone          #+#    #+#             */
/*   Updated: 2023/02/01 19:38:32 by saaltone         ###   ########.fr       */
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
		render_frame(app);
	}
}

/**
 * @brief Rendering function to be called in app loop. Calls individual
 * renderers and draws resulting image(s) to the window.
 * 
 * @param app 
 */
void	render_frame(t_app *app)
{
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
	else if (app->status == STATUS_CONTROLS)
		render_controls(app);
	else if (app->status == STATUS_SELECTLEVEL)
		render_select_level(app);
	SDL_UpdateWindowSurface(app->win);
	play_music(app);
}
