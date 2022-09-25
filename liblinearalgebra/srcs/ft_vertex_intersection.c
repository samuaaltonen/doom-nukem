/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vertex_intersection.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 22:01:27 by saaltone          #+#    #+#             */
/*   Updated: 2022/09/25 23:19:47 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "liblinearalgebra.h"

/**
 * Calculates intersection point between 2 vertices. If there is no intersection
 * returns 0, otherwise 1 and sets the intersection point to given vector2
 * pointer.
 * 
 * See also:
 * https://en.wikipedia.org/wiki/Line%E2%80%93line_intersection
*/
int	ft_vertex_intersection(t_vertex2 vertex_a, t_vertex2 vertex_b,
		t_vector2 *intersection)
{
	double	t;
	double	u;
	double	divider;

	divider = ((vertex_a.a.x - vertex_a.b.x) * (vertex_b.a.y - vertex_b.b.y)
			- (vertex_a.a.y - vertex_a.b.y) * (vertex_b.a.x - vertex_b.b.x));
	if (divider == 0.f)
		return (0);
	t = ((vertex_a.a.x - vertex_b.a.x) * (vertex_b.a.y - vertex_b.b.y)
			- (vertex_a.a.y - vertex_b.a.y) * (vertex_b.a.x - vertex_b.b.x))
		/ divider;
	u = ((vertex_a.a.x - vertex_b.a.x) * (vertex_a.a.y - vertex_a.b.y)
			- (vertex_a.a.y - vertex_b.a.y) * (vertex_a.a.x - vertex_a.b.x))
		/ divider;
	if (t < 0.f || t > 1.f || u < 0.f || u > 1.f)
		return (0);
	intersection->x = vertex_a.a.x + t * (vertex_a.b.x - vertex_a.a.x);
	intersection->y = vertex_a.a.y + t * (vertex_a.b.y - vertex_a.a.y);
	return (1);
}
