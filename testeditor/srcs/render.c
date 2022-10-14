/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 16:18:36 by htahvana          #+#    #+#             */
/*   Updated: 2022/10/14 16:16:52 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"


void	render_sector(t_app *app, t_vec2list *sector_start)
{
	t_vec2list *tmp;

	tmp = sector_start;
	while (tmp->next != sector_start && tmp->next != NULL)
	{
		draw_list_lines(app, tmp, tmp->next, 0xEEEEEE);
		tmp = tmp->next;
	}
	if(tmp->next == sector_start)
		draw_list_lines(app, tmp, sector_start, 0xEEEEEE);
}

void	render_sectors(t_app *app)
{
	t_sectorlist *tmp;

	tmp = app->sectors;
	while(tmp)
	{
		render_sector(app, tmp->wall_list);
		tmp = tmp->next;
	}
}

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
		if(fmod(screen.y, divider) > prev.y || screen.y == 0.0f)
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

void	render_selection_point(t_app *app)
{
	(void)app;
}