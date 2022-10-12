/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 16:18:36 by htahvana          #+#    #+#             */
/*   Updated: 2022/10/11 16:09:22 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"


static void	render_sector(t_app *app, t_vec2list *sector_start)
{
	t_vec2list *tmp;

	tmp = sector_start;
	while (tmp->next != sector_start && tmp->next != NULL)
	{
		draw_list_lines(app, tmp, tmp->next);
		tmp = tmp->next;
	}
	if(tmp->next == sector_start)
		draw_list_lines(app, tmp, sector_start);
}

void	render_sectors(t_app *app)
{
	t_sectorlist *tmp;

	tmp = app->sectors;
	render_sector(app, tmp->wall_list);
	while(tmp->next)
	{
		tmp = tmp->next;
		render_sector(app, tmp->wall_list);
	}
}

static int	check_borders(t_app *app, t_point *a, t_point *b)
{
	if (a->x > app->surface->w && b->x > app->surface->w)
		return (0);
	if (a->x < 0 && b->x < 0)
		return (0);
	if (a->y > app->surface->h && b->y > app->surface->h)
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

static void	linedraw_low(t_app *app, t_point *a, t_point *b)
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
		put_pixel_to_surface(app->surface, line.pos.x, line.pos.y, 0xFF0000);
		line.pos.x += 1;
		if (line.err < 0)
			line.err += (2 * line.dif.y);
		else
		{
			line.pos.y += line.d;
			line.err += (2 * (line.dif.y - line.dif.x));
		}
	}
	put_pixel_to_surface(app->surface, line.pos.x, line.pos.y, 0xFF0000);
}

static void	linedraw_high(t_app *app, t_point *a, t_point *b)
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
		put_pixel_to_surface(app->surface, line.pos.x, line.pos.y, 0x00FF00);
		line.pos.y += 1;
		if (line.err < 0)
			line.err += (2 * line.dif.x);
		else
		{
			line.pos.x += line.d;
			line.err += (2 * (line.dif.x - line.dif.y));
		}
	}
	put_pixel_to_surface(app->surface, line.pos.x, line.pos.y, 0x00FF00);
}

/* static void line_to_screenspace(t_app *app, t_vec2list *a, t_vec2list *b)
{
	t_point pixel_a;
	t_point pixel_b;

	pixel_a.x =  ((a->point.x + app->view_pos.x) / app->zoom_area.x ) * (double)app->surface->w;
	pixel_a.y =  ((a->point.y + app->view_pos.y) / app->zoom_area.y ) * (double)app->surface->h;

} */



void	draw_line(t_app *app, t_vector2 *a, t_vector2 *b)
{
	t_point pixel_a;
	t_point pixel_b;

	pixel_a.x =  fabs(((a->x + app->view_pos.x) / app->zoom_area.x ) * app->surface->w);
	pixel_a.y =  fabs(((a->y + app->view_pos.y) / app->zoom_area.y ) * app->surface->h);

	pixel_b.x =  fabs(((b->x + app->view_pos.x) / app->zoom_area.x ) * app->surface->w);
	pixel_b.y =  fabs(((b->y + app->view_pos.y) / app->zoom_area.y ) * app->surface->h);

	//printf("test x%i, y%i\n", pixel_a.x, pixel_a.y);

	if (!check_borders(app, &pixel_a, &pixel_b))
		return ;
	if (abs(pixel_b.y - pixel_a.y) < abs(pixel_b.x - pixel_a.x))
	{
		if (pixel_a.x > pixel_b.x)
			linedraw_low(app, &pixel_b, &pixel_a);
		else
			linedraw_low(app, &pixel_a, &pixel_b);
	}
	else
	{
		if (pixel_a.y > pixel_b.y)
			linedraw_high(app, &pixel_b, &pixel_a);
		else
			linedraw_high(app, &pixel_a, &pixel_b);
	}
}

void	draw_list_lines(t_app *app, t_vec2list *a, t_vec2list *b)
{
	t_point pixel_a;
	t_point pixel_b;

	pixel_a.x =  fabs(((a->point.x + app->view_pos.x) / app->zoom_area.x ) * app->surface->w);
	pixel_a.y =  fabs(((a->point.y + app->view_pos.y) / app->zoom_area.y ) * app->surface->h);

	pixel_b.x =  fabs(((b->point.x + app->view_pos.x) / app->zoom_area.x ) * app->surface->w);
	pixel_b.y =  fabs(((b->point.y + app->view_pos.y) / app->zoom_area.y ) * app->surface->h);

	//printf("test x%i, y%i\n", pixel_a.x, pixel_a.y);

	if (!check_borders(app, &pixel_a, &pixel_b))
		return ;
	if (abs(pixel_b.y - pixel_a.y) < abs(pixel_b.x - pixel_a.x))
	{
		if (pixel_a.x > pixel_b.x)
			linedraw_low(app, &pixel_b, &pixel_a);
		else
			linedraw_low(app, &pixel_a, &pixel_b);
	}
	else
	{
		if (pixel_a.y > pixel_b.y)
			linedraw_high(app, &pixel_b, &pixel_a);
		else
			linedraw_high(app, &pixel_a, &pixel_b);
	}
}