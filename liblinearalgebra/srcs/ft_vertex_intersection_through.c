/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vertex_intersection_through.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 22:01:27 by saaltone          #+#    #+#             */
/*   Updated: 2022/10/15 18:35:50 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "liblinearalgebra.h"

/**
 * Returns 1 only when there is intersection that splits the other vertex in 2
 * parts. Therefore intersection with only a corner of other vertex returns 0.
 * 
 * See also: ft_vertex_intersection
*/
int	ft_vertex_intersection_through(t_vertex2 vertex_a, t_vertex2 vertex_b)
{
	if (ft_vertex_side(vertex_a, vertex_b.a)
		!= ft_vertex_side(vertex_a, vertex_b.b))
		return (1);
	return (0);
}
