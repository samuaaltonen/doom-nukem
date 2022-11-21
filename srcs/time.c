/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 12:22:26 by dpalacio          #+#    #+#             */
/*   Updated: 2022/11/21 13:47:01 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

static void	update_fps_info(t_app *app);
static void	update_avg_fps(t_app *app);

/**
 * Calculates frame delta time and sets FPS accordingly.
 */
void	update_fps_counter(t_app *app)
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
	update_avg_fps(app);
    update_fps_info(app);
}

/**
 * Updates the info string with given value backwards from given index
 */
static void	update_fps_info(t_app *app)
{
	int	char_index;
	int	i;

	char_index = 7;
	i = -1;
	while (++i < 4)
	{
		app->conf->fps_info[char_index - i] = app->conf->fps_avg % 10 + '0';
		app->conf->fps_avg = app->conf->fps_avg / 10;
	}
}

/**
 * Updates the fps average every 100 frames
 */
static void	update_avg_fps(t_app *app)
{
	if (app->conf->frames_total == 100)
	{
		app->conf->fps_chunk = app->conf->fps_total;
	}
	if (app->conf->frames_total > 100)
	{
		app->conf->frames_total = 0;
		app->conf->fps_total = 0;
	}
	app->conf->fps_total += app->conf->fps;
	app->conf->frames_total++;
	app->conf->fps_avg = (int)((double)app->conf->fps_chunk / 100.0);
}
