/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vertex_resize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 17:01:41 by saaltone          #+#    #+#             */
/*   Updated: 2022/10/07 17:16:27 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "liblinearalgebra.h"

/**
 * Extends vertex to given length. If both_sides is seleted, extends both ends
 * of the vertex.
 */
t_vertex2	ft_vertex_resize(t_vertex2 vertex, double length, int side)
{
	t_vertex2	resized;
	t_vector2	vertex_direction;

	vertex_direction = ft_vector_resize((t_vector2){
			vertex.b.x - vertex.a.x,
			vertex.b.y - vertex.a.y,
		}, length);
	resized = vertex;
	if (side == EXTEND_CORNER_A || side == EXTEND_BOTH)
	{
		resized.a.x -= vertex_direction.x;
		resized.a.y -= vertex_direction.y;
	}
	if (side == EXTEND_CORNER_B || side == EXTEND_BOTH)
	{
		resized.b.x += vertex_direction.x;
		resized.b.y += vertex_direction.y;
	}
	return (resized);
}
