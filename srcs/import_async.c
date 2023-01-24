/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import_async.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 17:51:30 by saaltone          #+#    #+#             */
/*   Updated: 2023/01/24 14:48:35 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * @brief Draws progress bar based on progress value.
 * 
 * @param app 
 * @param progress 
 */
static void	draw_progress_bar(t_app *app, double progress)
{
	int	progress_x;
	int	x;
	int	y;

	x = WIN_W / 10 + 5;
	progress_x = (int)(progress * (WIN_W - WIN_W / 5)) + x - 10;
	while (x < progress_x && x < WIN_W - WIN_W / 10)
	{
		y = WIN_H / 10 * 8 + 5;
		while (y < WIN_H / 10 * 9 - 5)
		{
			put_pixel_to_surface(app->surface, x, y, PROGRESS_BAR_COLOR);
			y++;
		}
		x++;
	}
}

/**
 * @brief Draws progress bar frame.
 * 
 * @param app 
 */
static void	draw_progress_bar_frame(t_app *app)
{
	int	x;
	int	y;

	x = WIN_W / 10;
	while (x < WIN_W - WIN_W / 10)
	{
		put_pixel_to_surface(app->surface, x, WIN_H / 10 * 8,
			PROGRESS_BAR_FRAME_COLOR);
		put_pixel_to_surface(app->surface, x, WIN_H / 10 * 9,
			PROGRESS_BAR_FRAME_COLOR);
		x++;
	}
	y = WIN_H / 10 * 8;
	while (y < WIN_H / 10 * 9)
	{
		put_pixel_to_surface(app->surface, WIN_W / 10, y,
			PROGRESS_BAR_FRAME_COLOR);
		put_pixel_to_surface(app->surface, WIN_W - WIN_W / 10, y,
			PROGRESS_BAR_FRAME_COLOR);
		y++;
	}
}

/**
 * @brief Renders loading screen.
 * 
 * @param app 
 */
static void	render_loading(t_app *app, double progress)
{
	while (SDL_PollEvent(&app->event))
		dispatch_event_minimal(app, &app->event);
	draw_progress_bar_frame(app);
	draw_progress_bar(app, progress);
	SDL_UpdateWindowSurface(app->win);
}

/**
 * @brief Asynchronous function to be used in parallel to the main thread for
 * importing data from level file.
 * 
 * @param data 
 * @return void* 
 */
void	*async_load(void *data)
{
	t_app			*app;
	t_thread_data	*thread;

	thread = (t_thread_data *)data;
	app = (t_app *)thread->app;
	import_level(app, thread);
	pthread_exit(NULL);
}

/**
 * @brief Creates thread for data importing and monitors/renders its progress
 * with loading screen.
 * 
 * @param app 
 */
void	load_data(t_app *app)
{
	double			progress;
	t_thread_data	thread;

	ft_bzero(app->surface->pixels, app->surface->h * app->surface->pitch);
	app->import_progress = 0.0;
	progress = 0.0;
	thread.app = app;
	thread.id = 0;
	if (pthread_mutex_init(&thread.lock, NULL)
		|| pthread_create(&thread.thread, NULL, async_load, (void *)(&thread)))
		exit_error(MSG_ERROR_THREADS);
	while (progress != -1.0)
	{
		if (pthread_mutex_lock(&thread.lock))
			exit_error(MSG_ERROR_THREADS_MUTEX);
		progress = app->import_progress;
		if (pthread_mutex_unlock(&thread.lock))
			exit_error(MSG_ERROR_THREADS_MUTEX);
		render_loading(app, progress);
	}
	render_loading(app, progress);
}
