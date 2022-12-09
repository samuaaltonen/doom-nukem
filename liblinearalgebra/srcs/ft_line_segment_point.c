/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_line_segment_point.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 15:24:38 by saaltone          #+#    #+#             */
/*   Updated: 2022/12/09 15:31:00 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "liblinearalgebra.h"

/**
 * @brief Returns 1 if coordinate is located on line segment.
 * 
 * @param line 
 * @param point 
 * @return int 
 */
int	ft_line_segment_point(t_line line, t_vector2 point)
{
	double	len;
	double	dista;
	double	distb;

	len = ft_point_distance(line.a, line.b);
	dista = ft_point_distance(point, line.a);
	distb = ft_point_distance(point, line.b);
	if (dista + distb >= len - LINE_POINT_EPSILON
		&& dista + distb <= len + LINE_POINT_EPSILON)
		return (1);
	return (0);
}
