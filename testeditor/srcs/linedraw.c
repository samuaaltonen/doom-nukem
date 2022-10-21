/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linedraw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 13:01:44 by htahvana          #+#    #+#             */
/*   Updated: 2022/10/21 13:43:29 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

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

static void	linedraw_low(t_app *app, t_point *a, t_point *b, int color)
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
		put_pixel_to_surface(app->surface, line.pos.x, line.pos.y, color);
		line.pos.x += 1;
		if (line.err < 0)
			line.err += (2 * line.dif.y);
		else
		{
			line.pos.y += line.d;
			line.err += (2 * (line.dif.y - line.dif.x));
		}
	}
	put_pixel_to_surface(app->surface, line.pos.x, line.pos.y, color);
}

static void	linedraw_high(t_app *app, t_point *a, t_point *b, int color)
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
		put_pixel_to_surface(app->surface, line.pos.x, line.pos.y, color);
		line.pos.y += 1;
		if (line.err < 0)
			line.err += (2 * line.dif.x);
		else
		{
			line.pos.x += line.d;
			line.err += (2 * (line.dif.x - line.dif.y));
		}
	}
	put_pixel_to_surface(app->surface, line.pos.x, line.pos.y, color);
}

/**
 * @brief Draw line between two vector points
 * 
 * @param app 
 * @param a 
 * @param b 
 * @param color 
 */
void	draw_line(t_app *app, t_vector2 *a, t_vector2 *b, int color)
{
	t_point pixel_a;
	t_point pixel_b;

	pixel_a.x = (a->x - app->view_pos.x) * (app->surface->w) / (app->view_size.x - app->view_pos.x);
	pixel_a.y = (a->y - app->view_pos.y) * (app->surface->h) / (app->view_size.y - app->view_pos.y);

	pixel_b.x = (b->x - app->view_pos.x) * (app->surface->w) / (app->view_size.x - app->view_pos.x);
	pixel_b.y = (b->y - app->view_pos.y) * (app->surface->h) / (app->view_size.y - app->view_pos.y);

	if (!check_borders(app, &pixel_a, &pixel_b))
		return ;
	if (abs(pixel_b.y - pixel_a.y) < abs(pixel_b.x - pixel_a.x))
	{
		if (pixel_a.x > pixel_b.x)
			linedraw_low(app, &pixel_b, &pixel_a, color);
		else
			linedraw_low(app, &pixel_a, &pixel_b, color);
	}
	else
	{
		if (pixel_a.y > pixel_b.y)
			linedraw_high(app, &pixel_b, &pixel_a, color);
		else
			linedraw_high(app, &pixel_a, &pixel_b, color);
	}
}

/**
 * @brief Draw line between two given wall list points
 * 
 * @param app 
 * @param a 
 * @param b 
 * @param color 
 */
void	draw_list_lines(t_app *app, t_vec2_lst *a, t_vec2_lst *b, int color)
{
	t_point pixel_a;
	t_point pixel_b;

	pixel_a.x = (a->point.x - app->view_pos.x) * (app->surface->w) / (app->view_size.x - app->view_pos.x);
	pixel_a.y = (a->point.y - app->view_pos.y) * (app->surface->h) / (app->view_size.y - app->view_pos.y);

	pixel_b.x = (b->point.x - app->view_pos.x) * (app->surface->w) / (app->view_size.x - app->view_pos.x);
	pixel_b.y = (b->point.y - app->view_pos.y) * (app->surface->h) / (app->view_size.y - app->view_pos.y);

	if (!check_borders(app, &pixel_a, &pixel_b))
		return ;
	if (abs(pixel_b.y - pixel_a.y) < abs(pixel_b.x - pixel_a.x))
	{
		if (pixel_a.x > pixel_b.x)
			linedraw_low(app, &pixel_b, &pixel_a, color);
		else
			linedraw_low(app, &pixel_a, &pixel_b, color);
	}
	else
	{
		if (pixel_a.y > pixel_b.y)
			linedraw_high(app, &pixel_b, &pixel_a, color);
		else
			linedraw_high(app, &pixel_a, &pixel_b, color);
	}
}
