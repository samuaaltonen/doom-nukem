/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_line_intersection.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 22:01:27 by saaltone          #+#    #+#             */
/*   Updated: 2022/10/25 10:45:47 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "liblinearalgebra.h"

/**
 * Calculates intersection point between 2 lines. If there is no intersection
 * returns 0, otherwise 1 and sets the intersection point to given vector2
 * pointer.
 * 
 * See also:
 * https://en.wikipedia.org/wiki/Line%E2%80%93line_intersection
*/
int	ft_line_intersection(t_line line_a, t_line line_b,
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
	intersection->x = line_a.a.x + t * (line_a.b.x - line_a.a.x);
	intersection->y = line_a.a.y + t * (line_a.b.y - line_a.a.y);
	return (1);
}
