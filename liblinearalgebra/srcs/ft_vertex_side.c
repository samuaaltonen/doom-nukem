/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vertex_side.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 12:48:54 by saaltone          #+#    #+#             */
/*   Updated: 2022/10/10 15:22:23 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "liblinearalgebra.h"

/**
 * Returns 1 if given coordinate point (vector2) is located at left side of
 * given vertex and 0 if left side.
 */
int	ft_vertex_side(t_vertex2 vertex, t_vector2 coord)
{
	return ((vertex.b.x - vertex.a.x) * (coord.y - vertex.a.y)
		- (vertex.b.y - vertex.a.y) * (coord.x - vertex.a.x) > 0.0);
}
