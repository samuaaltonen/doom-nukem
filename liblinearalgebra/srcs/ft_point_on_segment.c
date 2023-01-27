/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_point_on_segment.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 15:24:38 by saaltone          #+#    #+#             */
/*   Updated: 2023/01/25 16:45:37 by htahvana         ###   ########.fr       */
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
int	ft_point_on_segment(t_line line, t_vector2 point)
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

int	ft_point_on_segment_epsilon(t_line line, t_vector2 point, double epsilon)
{
	double	len;
	double	dista;
	double	distb;

	len = ft_point_distance(line.a, line.b);
	dista = ft_point_distance(point, line.a);
	distb = ft_point_distance(point, line.b);
	if (dista + distb >= len - epsilon
		&& dista + distb <= len + epsilon)
		return (1);
	return (0);
}
