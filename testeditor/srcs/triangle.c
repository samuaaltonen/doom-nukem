/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 15:52:24 by htahvana          #+#    #+#             */
/*   Updated: 2023/01/16 15:22:08 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * @brief 
 * 
 * @param a
 * @param b
 * @param c
 * @return t_bool
*/
static t_bool	sort_triangle(t_point *a, t_point *b, t_point *c)
{
	int		same;

	same = 0;
	if (a->y == b->y)
		same++;
	if (a->y == c->y)
		same++;
	if (b->y == c->y)
		same++;
	if (same == 3)
		return (FALSE);
	if (a->y > b->y)
		ft_point_swap(a, b);
	if (a->y > c->y)
		ft_point_swap(a, c);
	if (b->y > c->y)
		ft_point_swap(b, c);
	return (TRUE);
}

/**
 * @brief Calcultes triangle top.
 * 
 * @param triangle
 * @param pos
 * @param heights
 * @param hor
*/
static void	calculate_top(t_triangle triangle, t_point *pos,
								t_point *heights, t_point *hor)
{
	t_vector2	relative_heights;

	relative_heights.x = (double)(pos->y - triangle.a.y) / heights->x;
	relative_heights.y = (double)(pos->y - triangle.a.y) / heights->y;
	hor->x = triangle.a.x + (triangle.c.x - triangle.a.x) * relative_heights.x;
	hor->y = triangle.a.x + (triangle.b.x - triangle.a.x) * relative_heights.y;
	if (hor->x > hor->y)
		ft_swap(&hor->x, &hor->y);
	pos->x = hor->x - 1;
}

/**
 * @brief Calculates triangle bottom.
 * 
 * @param triangle
 * @param pos
 * @param heights
 * @param hor
*/
static void	calculate_bot(t_triangle triangle, t_point *pos,
									t_point *heights, t_point *hor)
{
	t_vector2	relative_heights;

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
 * to the full height of the triange (total_height),
 * the other is to the point in between (segment_height)
 * calculates the relative height to both points
 * calculates the horizontal x coordinates using the relative heights,
 * at the current y coordinate
 * 
 *  do it for the upper and lower part of the triangle
 * 
 * @param relative_heights is the long and short side of a triangle ratio
 * @param heights x is the total height, y is the segment height
 */
void	fill_triangle(t_app *app, t_triangle triangle, int color)
{
	t_point		pos;
	t_point		hor;
	t_point		heights;

	if (sort_triangle(&triangle.a, &triangle.b, &triangle.c))
	{
		heights.x = triangle.c.y - triangle.a.y;
		heights.y = triangle.b.y - triangle.a.y + 1;
		pos.y = triangle.a.y - 1;
		while (++pos.y <= triangle.b.y)
		{
			calculate_top(triangle, &pos, &heights, &hor);
			while (++pos.x <= hor.y)
				put_pixel_to_surface(app->surface, pos.x, pos.y, color);
		}
		heights.y = triangle.c.y - triangle.b.y + 1;
		pos.y = triangle.b.y - 1;
		while (++pos.y <= triangle.c.y)
		{
			calculate_bot(triangle, &pos, &heights, &hor);
			while (++pos.x <= hor.y)
				put_pixel_to_surface(app->surface, pos.x, pos.y, color);
		}
	}
}
