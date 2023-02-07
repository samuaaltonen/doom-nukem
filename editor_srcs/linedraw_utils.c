/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linedraw_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 13:08:45 by ssulkuma          #+#    #+#             */
/*   Updated: 2023/02/07 18:30:38 by saaltone         ###   ########.fr       */
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

/**
 * @brief Checks if sector line connects to the first point of the list.
 * 
 * @param app
 * @return t_bool
*/
t_bool	check_last_point(t_app *app)
{
	t_wall_list	*tmp;
	t_wall_list	*prev;
	int			points;

	prev = NULL;
	tmp = app->active;
	points = 0;
	while (tmp)
	{
		if (tmp->next)
		{
			points++;
			prev = tmp;
		}
		tmp = tmp->next;
		if (tmp == app->active)
			break ;
	}
	if (points < 2 || points >= MAX_SECTOR_CORNERS)
		return (FALSE);
	if (prev && ft_vector_compare(app->active->point, app->mouse_track)
		&& !ft_line_side((t_line){prev->point,
			app->active_last->point}, app->mouse_track))
		return (TRUE);
	return (FALSE);
}
