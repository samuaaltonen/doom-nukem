/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 15:52:24 by htahvana          #+#    #+#             */
/*   Updated: 2022/12/08 15:04:07 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

static void	sort_triangle(t_point *a, t_point *b, t_point *c)
{
	if (a->y > b->y)
		ft_point_swap(a, b);
	if (a->y > c->y) 
		ft_point_swap(a, c);
	if (b->y > c->y)
		ft_point_swap(b, c);
}

static void	calculate_top(t_triangle triangle, t_point *pos, t_point *heights, t_point *hor)
{
	t_vector2 relative_heights;

	relative_heights.x = (double)(pos->y - triangle.a.y) / heights->x;
	relative_heights.y = (double)(pos->y - triangle.a.y) / heights->y;
	hor->x = triangle.a.x + (triangle.c.x - triangle.a.x) * relative_heights.x;
	hor->y = triangle.a.x + (triangle.b.x - triangle.a.x) * relative_heights.y;
	if (hor->x > hor->y)
		ft_swap(&hor->x, &hor->y);
	pos->x = hor->x - 1;
}

static void	calculate_bot(t_triangle triangle, t_point *pos, t_point *heights, t_point *hor)
{
	t_vector2 relative_heights;

	relative_heights.x = (double)(pos->y - triangle.a.y) / heights->x;
	relative_heights.y = (double)(pos->y - triangle.b.y) / heights->y;
	hor->x = triangle.a.x + (triangle.c.x - triangle.a.x) * relative_heights.x;
	hor->y = triangle.b.x + (triangle.c.x - triangle.b.x) * relative_heights.y;
	if (hor->x > hor->y)
		ft_swap(&hor->x, &hor->y);
	pos->x = hor->x - 1;
}

/**
 * @brief sorts the points by Y height, one side of the triangle is
 *  to the full height of the triange (total_height),
 *  the other is to the point in between (segment_height)
 *  calculates the relative height to both points
 *  calculates the horizontal x coordinates using the relative heights,
 *   at the current y coordinate
 * 
 *  do it for the upper and lower part of the triangle
 * 
 * @param relative_heights is the long and short side of a triangle ratio
 * @param heights x is the total height, y is the segment height
 */
void fill_triangle(t_app *app, t_point a, t_point b, t_point c, int color)
{
	t_point pos;
	t_point hor;
	t_point heights;

	sort_triangle(&a, &b, &c);
	heights.x = c.y - a.y;
	heights.y = b.y - a.y + 1;
	pos.y = a.y - 1;
	while (++pos.y <= b.y)
	{
		calculate_top((t_triangle){a,b,c}, &pos, &heights, &hor);
		while (++pos.x <= hor.y)
			put_pixel_to_surface(app->surface, pos.x, pos.y, color);
	}
	heights.y = c.y - b.y + 1;
	pos.y = b.y - 1;
	while (++pos.y <= c.y)
	{
		calculate_bot((t_triangle){a,b,c}, &pos, &heights, &hor);
		while (++pos.x <= hor.y)
			put_pixel_to_surface(app->surface, pos.x, pos.y, color);
	}
}
