/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_line_side.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 12:48:54 by saaltone          #+#    #+#             */
/*   Updated: 2022/10/25 10:45:47 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "liblinearalgebra.h"

/**
 * Returns 1 if given coordinate point (vector2) is located at left side of
 * given line and 0 if right side. Returns 0 if point is located on line.
 */
int	ft_line_side(t_line line, t_vector2 coord)
{
	return ((line.b.x - line.a.x) * (coord.y - line.a.y)
		- (line.b.y - line.a.y) * (coord.x - line.a.x) > 0.0);
}
