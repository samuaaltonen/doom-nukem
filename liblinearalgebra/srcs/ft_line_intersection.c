/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intersection.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 22:01:27 by saaltone          #+#    #+#             */
/*   Updated: 2022/10/25 10:45:47 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "liblinearalgebra.h"

/**
 * @brief Calculates intersection point between 2 lines. If there is no
 * intersection returns 0, otherwise 1 and sets the intersection point to given
 * vector2 pointer.
 * 
 * See also:
 * https://en.wikipedia.org/wiki/Line%E2%80%93line_intersection
 * 
 * @param a 
 * @param b 
 * @param intersection 
 * @return int 
 */
int	ft_line_intersection(t_line a, t_line b, t_vector2 *intersection)
{
	double	divider;
	double	x;
	double	y;

	divider = (a.a.x - a.b.x) * (b.a.y - b.b.y)
		- (a.a.y - a.b.y) * (b.a.x - b.b.x);
	if (!divider)
		return (0);
	x = (a.a.x * a.b.y - a.a.y * a.b.x) * (b.a.x - b.b.x)
		- (a.a.x - a.b.x) * (b.a.x * b.b.y - b.a.y * b.b.x);
	y = (a.a.x * a.b.y - a.a.y * a.b.x) * (b.a.y - b.b.y)
		- (a.a.y - a.b.y) * (b.a.x * b.b.y - b.a.y * b.b.x);
	if (!intersection)
		return (1);
	intersection->x = x / divider;
	intersection->y = y / divider;
	return (1);
}
