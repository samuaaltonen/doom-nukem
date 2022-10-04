/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 15:14:08 by saaltone          #+#    #+#             */
/*   Updated: 2022/10/04 12:23:17 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

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
 * Initializes application struct.
 */
int	app_init(t_app **app)
{
	*app = (t_app *)malloc(sizeof(t_app));
	ft_bzero(*app, sizeof(t_app));
	if (!(*app))
		return (0);
	return (1);
}

/**
 * Prepares the application to be rendered:
 * Creates window, loads assets, adds event hooks and sets
 * initial player position / direction.
 */
void	app_prepare(t_app *app)
{
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0 || TTF_Init() < 0)
		exit_error(MSG_ERROR_SDL_INIT);
	app->sprite = init_xpm_image(TEXTURE_PANELS);
	app->bg = init_xpm_image(TEXTURE_BACKGROUND);
	app->win = SDL_CreateWindow(WIN_NAME, 0, 0, WIN_W, WIN_H, SDL_WINDOW_SHOWN);
	if (!app->win)
		exit_error(MSG_ERROR_WINDOW);
	app->surface = SDL_GetWindowSurface(app->win);
	if (!app->surface)
		exit_error(MSG_ERROR_WINDOW_SURFACE);
	app->font = TTF_OpenFont(FONT_FILE, 22);
	if (!app->font)
		exit_error(MSG_ERROR_FONT);
	if (SDL_SetRelativeMouseMode(SDL_TRUE) < 0)
		exit_error(MSG_ERROR_MOUSE);
	SDL_WarpMouseInWindow(app->win, WIN_W / 2, WIN_H / 2);
	app->player = (t_player){(t_vector2){POSITION_START_X, POSITION_START_Y},
		(t_vector2){DIRECTION_START_X, DIRECTION_START_Y},
		(t_vector2){0.f, 0.f}, 1.0f, 0.5f};
	init_camera_plane(app);
}

/**
 * Rendering function to be called in loop hook. Calls individual renderers and
 * draws resulting image(s) to the window.
 */
void	app_render(t_app *app)
{
	/* SDL_Surface	*converted_surface; */
	SDL_Surface *text_surface;

	handle_movement(app);
	update_fps_counter(app);
	update_info(app);
	ft_bzero(app->depthmap, WIN_H * WIN_W * sizeof(double));
	render_multithreading(app, render_skybox);
	//render_multithreading(app, render_background);
	render_multithreading(app, render_polygons);
	/* if (app->surface->format != app->image->surface->format)
	{
		converted_surface = SDL_ConvertSurface(app->image->surface, app->surface->format, 0);
		//SDL_BlitScaled(converted_surface, NULL, app->surface, NULL);
		SDL_BlitSurface(app->image->surface, NULL, app->surface, NULL);
		SDL_FreeSurface(converted_surface);
	}
	else
		SDL_BlitSurface(app->image->surface, NULL, app->surface, NULL); */
	text_surface = TTF_RenderText_Solid(app->font, app->conf->fps_info, (SDL_Color){255, 255, 255, 0});
	SDL_BlitSurface(text_surface, NULL, app->surface, NULL);
	SDL_FreeSurface(text_surface);
	SDL_UpdateWindowSurface(app->win);
}

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
		app_render(app);
	}
}
