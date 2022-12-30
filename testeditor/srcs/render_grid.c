/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_grid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 15:28:54 by ssulkuma          #+#    #+#             */
/*   Updated: 2022/12/30 11:14:16 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * Renders a single line on the x-axis.
*/
static void	render_row(t_app *app, int y, int color)
{
	int	x;

	x = -1;
	while (++x < app->surface->w)
		put_pixel_to_surface(app->surface, x, y, color);
}

/**
 * Renders a single line on the y-axis.
*/
static void	render_col(t_app *app, int x, int color)
{
	int	y;

	y = -1;
	while (++y < app->surface->h)
		put_pixel_to_surface(app->surface, x, y, color);
}

/**
 * Renders the center lines.
*/
void	render_center(t_app *app, int color)
{
	t_point		point;

	point.x = (0 - app->view_pos.x) * (app->surface->w)
		/ (app->view_size.x - app->view_pos.x);
	point.y = (0 - app->view_pos.y) * (app->surface->h)
		/ (app->view_size.y - app->view_pos.y);
	render_row(app, point.y, color);
	render_col(app, point.x, color);
	render_row(app, point.y + 1, color);
	render_col(app, point.x + 1, color);
}

void	render_divider(t_app *app)
{
	render_grid(app, app->divider, BG_DARK);
	render_grid(app, app->divider * 2, BG_LIGHT);
}

/**
 * @brief renders a grid with the divider and color param
 * -50 + ( 0  / 1000) * 100
 * 
 * @param app 
 * @param divider 
 * @param color 
 */
void	render_grid(t_app *app, double divider, int color)
{
	int			x;
	int			y;
	t_vector2	screen;
	t_vector2	prev;

	y = -1;
	x = -1;
	prev = (t_vector2){0.0f, 0.0f};
	while (++y < app->surface->h)
	{
		screen.y = app->view_pos.y + (y / (double)app->surface->h)
			* app->zoom_area.y;
		if (fmod(screen.y, divider) > prev.y || screen.y == 0.0f)
			render_row(app, y, color);
		prev.y = fmod(screen.y, divider);
	}
	while (++x < app->surface->w)
	{
		screen.x = app->view_pos.x + (x / (double)app->surface->w)
			* app->zoom_area.x;
		if (fmod(screen.x, divider) < prev.x || screen.x == 0.0f)
			render_col(app, x, color);
		prev.x = fmod(screen.x, divider);
	}
	render_center(app, color);
}
