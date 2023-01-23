/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loading_screen.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 19:33:51 by saaltone          #+#    #+#             */
/*   Updated: 2023/01/23 17:09:35 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

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
void	render_loading(t_app *app, double progress, t_bool dispatch_events)
{
	SDL_Event	event;

	while (SDL_PollEvent(&event))
	{
		if (dispatch_events)
			dispatch_event_minimal(&event);
	}
	draw_progress_bar_frame(app);
	draw_progress_bar(app, progress);
	SDL_UpdateWindowSurface(app->win);
}
