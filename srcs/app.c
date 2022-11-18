/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 15:14:08 by saaltone          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/11/17 16:57:04 by saaltone         ###   ########.fr       */
=======
/*   Updated: 2022/11/15 11:52:53 by dpalacio         ###   ########.fr       */
>>>>>>> origin/main
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
<<<<<<< HEAD
	/* int	sync_delay; */
=======
>>>>>>> origin/main
	update_fps_counter(app);
	if (app->status == STATUS_TITLESCREEN)
		render_titlescreen(app);
	else if (app->status == STATUS_MAINMENU)
		render_mainmenu(app);
	else if (app->status == STATUS_GAME)
		render_game(app);
	else if (app->status == STATUS_PAUSEMENU)
		render_pausemenu(app);
	else if (app->status == STATUS_MAINOPTIONS || app->status == STATUS_GAMEOPTIONS)
		render_options(app);
	SDL_UpdateWindowSurface(app->win);
	/* sync_delay = (int)((TARGET_FRAME_TIME - app->conf->delta_time) * 1000);
	if (sync_delay > 0)
	{
		ft_printf("Sync delay %d\n", sync_delay);
		SDL_Delay(sync_delay);
	} */
}
