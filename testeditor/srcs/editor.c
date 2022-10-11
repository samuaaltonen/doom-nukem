/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 13:03:35 by htahvana          #+#    #+#             */
/*   Updated: 2022/10/11 14:49:55 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

static void	render_row(t_app *app, int y, int color)
{
	int	x;

	x = -1;
	while (++x < app->surface->w)
		put_pixel_to_surface(app->surface, x, y, color);
} 
static void	render_col(t_app *app, int x, int color)
{
	int	y;

	y = -1;
	while (++y < app->surface->h)
		put_pixel_to_surface(app->surface, x, y, color);
}

void	render_grid(t_app *app, double divider, int color)
{
	int			x;
	int			y;
	t_vector2	screen;
	t_vector2	prev;

	y = 0;
	x = 0;
	prev = (t_vector2){0.0f,0.0f};
	while (y < app->surface->h)
 	{
		screen.x = app->view_pos.x + (x / (double)app->surface->w) * app->zoom_area.x;
		screen.y = app->view_pos.y + (y / (double)app->surface->h) * app->zoom_area.y;
		if(fmod(screen.y, divider) < prev.y || screen.y == 0.0f)
			render_row(app, y, color);
		prev.y = fmod(screen.y, divider);
		y++;
	}
	while (x < app->surface->w)
	{
		screen.x = app->view_pos.x + (x / (double)app->surface->w) * app->zoom_area.x;
		screen.y = app->view_pos.y + (y / (double)app->surface->h) * app->zoom_area.y;
		if(fmod(screen.x, divider) < prev.x || screen.x == 0.0f)
			render_col(app, x, color);
		prev.x = fmod(screen.x, divider);

		x++;
	}
		//-50 + ( 0  / 1000) * 100
}

//current real time nearest point to cursor
t_vector2 *nearest_point_cursor(t_app *app)
{
(void)app;
 return(NULL);

}

//check if point is already in list
t_bool valid_point(t_app *app)
{
(void)app;
 return(0);

}

//check if point is first element in list and complete sector
t_bool complete_sector(t_app *app)
{
(void)app;
 return(0);

}
