/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 16:18:36 by htahvana          #+#    #+#             */
/*   Updated: 2022/10/10 12:28:05 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"



void	render_sector(t_app *app, t_vec2list *sector_start)
{
	t_vec2list *tmp;

	tmp = sector_start;
	while (tmp->next != sector_start && tmp->next != NULL)
	{
		linedrawing(app, tmp, tmp->next);
		tmp = tmp->next;
	}
	if(tmp->next == sector_start)
		linedrawing(app, tmp, sector_start);
}


static int	check_borders(t_app *data, t_point *a, t_point *b)
{
	if (a->x > data->surface->w && b->x > data->surface->w)
		return (0);
	if (a->x < 0 && b->x < 0)
		return (0);
	if (a->y > data->surface->h && b->y > data->surface->h)
		return (0);
	if (a->y < 0 && b->y < 0)
		return (0);
	return (1);
}

static void	line_init(t_point *a, t_point *b, t_line *line)
{
	line->dif.x = b->x - a->x;
	line->dif.y = b->y - a->y;
	line->pos.x = a->x;
	line->pos.y = a->y;
	line->d = 1;
}

static void	linedraw_low(t_app *data, t_point *a, t_point *b)
{
	t_line	line;

	line_init(a, b, &line);
	if (line.dif.y < 0)
	{
		line.d = -1;
		line.dif.y = -line.dif.y;
	}
	line.err = (2 * line.dif.y) - line.dif.x;
	while (line.pos.x < b->x)
	{
		put_pixel_to_surface(data->surface, line.pos.x, line.pos.y, 0xFF0000);
		line.pos.x += 1;
		if (line.err < 0)
			line.err += (2 * line.dif.y);
		else
		{
			line.pos.y += line.d;
			line.err += (2 * (line.dif.y - line.dif.x));
		}
	}
	put_pixel_to_surface(data->surface, line.pos.x, line.pos.y, 0xFF0000);
}

static void	linedraw_high(t_app *data, t_point *a, t_point *b)
{
	t_line	line;

	line_init(a, b, &line);
	if (line.dif.x < 0)
	{
		line.d = -1;
		line.dif.x = -line.dif.x;
	}
	line.err = (2 * line.dif.x) - line.dif.y;
	while (line.pos.y < b->y)
	{
		put_pixel_to_surface(data->surface, line.pos.x, line.pos.y, 0x00FF00);
		line.pos.y += 1;
		if (line.err < 0)
			line.err += (2 * line.dif.x);
		else
		{
			line.pos.x += line.d;
			line.err += (2 * (line.dif.x - line.dif.y));
		}
	}
	put_pixel_to_surface(data->surface, line.pos.x, line.pos.y, 0x00FF00);
}

/* static void line_to_screenspace(t_app *app, t_vec2list *a, t_vec2list *b)
{
	t_point pixel_a;
	t_point pixel_b;

	pixel_a.x =  ((a->point.x + app->view_pos.x) / app->zoom_area.x ) * (double)app->surface->w;
	pixel_a.y =  ((a->point.y + app->view_pos.y) / app->zoom_area.y ) * (double)app->surface->h;

} */

void	linedrawing(t_app *data, t_vec2list *a, t_vec2list *b)
{
	t_point pixel_a;
	t_point pixel_b;

	pixel_a.x =  fabs(((a->point.x + data->view_pos.x) / data->zoom_area.x ) * data->surface->w);
	pixel_a.y =  fabs(((a->point.y + data->view_pos.y) / data->zoom_area.y ) * data->surface->h);

	pixel_b.x =  fabs(((b->point.x + data->view_pos.x) / data->zoom_area.x ) * data->surface->w);
	pixel_b.y =  fabs(((b->point.y + data->view_pos.y) / data->zoom_area.y ) * data->surface->h);

	//printf("test x%i, y%i\n", pixel_a.x, pixel_a.y);

	if (!check_borders(data, &pixel_a, &pixel_b))
		return ;
	if (abs(pixel_b.y - pixel_a.y) < abs(pixel_b.x - pixel_a.x))
	{
		if (pixel_a.x > pixel_b.x)
			linedraw_low(data, &pixel_b, &pixel_a);
		else
			linedraw_low(data, &pixel_a, &pixel_b);
	}
	else
	{
		if (pixel_a.y > pixel_b.y)
			linedraw_high(data, &pixel_b, &pixel_a);
		else
			linedraw_high(data, &pixel_a, &pixel_b);
	}
}