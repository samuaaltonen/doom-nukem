/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vertex_intersection_through.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 22:01:27 by saaltone          #+#    #+#             */
/*   Updated: 2022/10/13 12:17:18 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "liblinearalgebra.h"

/**
 * See: ft_vertex_intersection
 * 
 * ft_vertex_intersection_through returns 1 only when there is intersection
 * that splits the other line in 2 parts. Therefore intersection with only a
 * corner of other vertex returns 0.
*/
int	ft_vertex_intersection_through(t_vertex2 vertex_a, t_vertex2 vertex_b,
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
	if ((intersection->x == vertex_a.a.x && intersection->y == vertex_a.a.y)
		|| (intersection->x == vertex_a.b.x && intersection->y == vertex_a.b.y)
		|| (intersection->x == vertex_b.a.x && intersection->y == vertex_b.a.y)
		|| (intersection->x == vertex_b.b.x && intersection->y == vertex_b.b.y))
		return (0);
	return (1);
}
