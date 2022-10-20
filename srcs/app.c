/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <danielmdc94@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 15:14:08 by saaltone          #+#    #+#             */
/*   Updated: 2022/10/20 12:45:04 by dpalacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * Main game loop. Polls SDL event queue until it is empty and then 
 * proceeds to next frame.
 */
void	app_loop(t_app *app)
{
	SDL_Event	event;

	while (TRUE)
	{
		while (SDL_PollEvent(&event))
			dispatch_event(app, &event);
		if (!app->conf->toggle_loop)
			render_frame(app);
	}
}


/**
 * Calculates frame delta time and sets FPS accordingly.
 */
static void	update_fps_counter(t_app *app)
{
	struct timespec	time_now;
	struct timespec	time_since;

	clock_gettime(CLOCK_REALTIME, &time_now);
	time_since.tv_nsec = time_now.tv_nsec - app->conf->fps_clock.tv_nsec;
	time_since.tv_sec = time_now.tv_sec - app->conf->fps_clock.tv_sec;
	app->conf->delta_time = (double)time_since.tv_sec
		+ 1.0e-9 * time_since.tv_nsec;
	app->conf->fps = (int)(1 / app->conf->delta_time);
	app->conf->fps_clock = time_now;
}

/**
 * Rendering function to be called in loop hook. Calls individual renderers and
 * draws resulting image(s) to the window.
 */
void	render_frame(t_app *app)
{
	flush_surface(app->surface);
	update_fps_counter(app);
	update_info(app);
	ft_bzero(app->depthmap, WIN_H * WIN_W * sizeof(double));
	/*
	else
	{
		render_multithreading(app, render_skybox);
		render_multithreading(app, render_polygons);
	} */
	if (app->status.title_screen)
		title_screen(app);
	//else if (app->main_menu)
	//	main_menu(app);
	else if (app->status.game_active)
		render_game(app);
	SDL_UpdateWindowSurface(app->win);
}

void	render_game(t_app *app)
{
	SDL_ShowCursor(SDL_DISABLE);
	handle_movement(app);
	render_sectors(app);
	render_ui(app);
}
