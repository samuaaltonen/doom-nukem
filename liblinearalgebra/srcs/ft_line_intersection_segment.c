/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_line_intersection_segment.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 17:13:55 by saaltone          #+#    #+#             */
/*   Updated: 2022/12/12 16:04:03 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "liblinearalgebra.h"

/**
 * Calculates intersection point between 2 line segments. If there is no
 * intersection returns 0, otherwise 1 and sets the intersection point to given
 * vector2 pointer.
 *
 * See also:
 * https://en.wikipedia.org/wiki/Line%E2%80%93line_intersection
*/
int	ft_line_intersection_segment(t_line line_a, t_line line_b,
		t_vector2 *intersection)
{
	double	t;
	double	u;
	double	divider;

	divider = ((line_a.a.x - line_a.b.x) * (line_b.a.y - line_b.b.y)
			- (line_a.a.y - line_a.b.y) * (line_b.a.x - line_b.b.x));
	if (divider == 0.f)
		return (0);
	t = ((line_a.a.x - line_b.a.x) * (line_b.a.y - line_b.b.y)
			- (line_a.a.y - line_b.a.y) * (line_b.a.x - line_b.b.x))
		/ divider;
	u = ((line_a.a.x - line_b.a.x) * (line_a.a.y - line_a.b.y)
			- (line_a.a.y - line_b.a.y) * (line_a.a.x - line_a.b.x))
		/ divider;
	if (t < 0.f || t > 1.f || u < 0.f || u > 1.f)
		return (0);
	if (!intersection)
		return (1);
	intersection->x = line_a.a.x + t * (line_a.b.x - line_a.a.x);
	intersection->y = line_a.a.y + t * (line_a.b.y - line_a.a.y);
	return (1);
}
