/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_line_resize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 17:01:41 by saaltone          #+#    #+#             */
/*   Updated: 2022/10/25 10:45:47 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "liblinearalgebra.h"

/**
 * @brief Extends line to given length. If both_sides is seleted, extends both
 * ends of the line.
 * 
 * @param line 
 * @param length 
 * @param side 
 * @return t_line 
 */
t_line	ft_line_resize(t_line line, double length, int side)
{
	t_line		resized;
	t_vector2	line_direction;

	if (!length)
	{
		resized.a = (t_vector2){0.0, 0.0};
		resized.b = (t_vector2){0.0, 0.0};
		return (resized);
	}
	line_direction = ft_vector_resize((t_vector2){
			line.b.x - line.a.x,
			line.b.y - line.a.y,
		}, length);
	resized = line;
	if (side == EXTEND_CORNER_A || side == EXTEND_BOTH)
	{
		resized.a.x -= line_direction.x;
		resized.a.y -= line_direction.y;
	}
	if (side == EXTEND_CORNER_B || side == EXTEND_BOTH)
	{
		resized.b.x += line_direction.x;
		resized.b.y += line_direction.y;
	}
	return (resized);
}
