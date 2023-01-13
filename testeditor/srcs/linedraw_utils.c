/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linedraw_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 13:08:45 by ssulkuma          #+#    #+#             */
/*   Updated: 2023/01/13 15:09:33 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * @brief Checks that point a and b won't go beyond surface borders.
 * 
 * @param app
 * @param a
 * @param b
 * @return int
*/
int	check_borders(t_app *app, t_point *a, t_point *b)
{
	if (a->x > app->surface->w && b->x > app->surface->w)
		return (FALSE);
	if (a->x < 0 && b->x < 0)
		return (FALSE);
	if (a->y > app->surface->h && b->y > app->surface->h)
		return (FALSE);
	if (a->y < 0 && b->y < 0)
		return (FALSE);
	return (TRUE);
}

/**
 * @brief Calculates the difference between point a and b and sets starting
 * point to the line.
 * 
 * @param a
 * @param b
 * @param line
*/
static void	line_init(t_point *a, t_point *b, t_draw_line *line)
{
	line->dif.x = b->x - a->x;
	line->dif.y = b->y - a->y;
	line->pos.x = a->x;
	line->pos.y = a->y;
	line->d = 1;
}

/**
 * @brief 
 * 
 * @param app
 * @param a
 * @param b
 * @param color
*/
void	linedraw_low(t_app *app, t_point *a, t_point *b, int color)
{
	t_draw_line	line;

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

/**
 * @brief 
 * 
 * @param app
 * @param a
 * @param b
 * @param color
*/
void	linedraw_high(t_app *app, t_point *a, t_point *b, int color)
{
	t_draw_line	line;

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
