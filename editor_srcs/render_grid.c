/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_grid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 15:28:54 by ssulkuma          #+#    #+#             */
/*   Updated: 2023/01/25 14:49:18 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * @brief Renders a single line on the x-axis.
 * 
 * @param app
 * @param y
 * @param color
*/
static void	render_row(t_app *app, int y, int color)
{
	int	x;

	x = -1;
	while (++x < app->surface->w)
		put_pixel_to_surface(app->surface, x, y, color);
}

/**
 * @brief Renders a single line on the y-axis.
 * 
 * @param app
 * @param x
 * @param color
*/
static void	render_col(t_app *app, int x, int color)
{
	int	y;

	y = -1;
	while (++y < app->surface->h)
		put_pixel_to_surface(app->surface, x, y, color);
}

/**
 * @brief Renders the center lines.
 * 
 * @param app
 * @param color
*/
void	render_center(t_app *app, int color)
{
	t_point		point;

	point.x = (0 - app->view_start.x) * (app->surface->w)
		/ (app->view_end.x - app->view_start.x);
	point.y = (0 - app->view_start.y) * (app->surface->h)
		/ (app->view_end.y - app->view_start.y);
	render_row(app, point.y, color);
	render_col(app, point.x, color);
	render_row(app, point.y + 1, color);
	render_col(app, point.x + 1, color);
}

/**
 * @brief Renders the divider lines.
 * 
 * @param app
*/
void	render_divider(t_app *app)
{
	render_grid(app, app->divider, BG_DARK);
	render_grid(app, app->divider * 2, BG_LIGHT);
}

/**
 * @brief Renders a grid with the divider and color param.
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
		screen.y = app->view_start.y + (y / (double)app->surface->h)
			* app->view_size.y;
		if (fmod(screen.y, divider) > prev.y || screen.y == 0.0f)
			render_row(app, y, color);
		prev.y = fmod(screen.y, divider);
	}
	while (++x < app->surface->w)
	{
		screen.x = app->view_start.x + (x / (double)app->surface->w)
			* app->view_size.x;
		if (fmod(screen.x, divider) < prev.x || screen.x == 0.0f)
			render_col(app, x, color);
		prev.x = fmod(screen.x, divider);
	}
	render_center(app, color);
}
