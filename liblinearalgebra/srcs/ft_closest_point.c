/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_closest_point.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:01:06 by htahvana          #+#    #+#             */
/*   Updated: 2022/12/20 14:25:16 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "liblinearalgebra.h"

/**
 * @brief Find the closest point to the point on the line.
 * 
 * @param point 
 * @param line 
 * @return t_vector2 
 */
t_vector2	ft_closest_point(t_vector2 point, t_line line)
{
	t_vector2	line_vector;
	t_vector2	perp;
	double		det;

	line_vector.x = line.b.y - line.a.y;
	line_vector.y = line.a.x - line.b.x;
	perp.x = line_vector.x * line.a.x + line_vector.y * line.a.y;
	perp.y = -line_vector.y * point.x + line_vector.x * point.y;
	det = line_vector.x * line_vector.x + line_vector.y * line_vector.y;
	if (det != 0)
	{
		point.x = (line_vector.x * perp.x - line_vector.y * perp.y) / det;
		point.y = (line_vector.x * perp.y + line_vector.y * perp.x) / det;
	}
	return (point);
}
