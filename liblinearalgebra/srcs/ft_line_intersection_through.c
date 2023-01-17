/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_line_intersection_through.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 22:01:27 by saaltone          #+#    #+#             */
/*   Updated: 2022/10/25 10:45:47 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "liblinearalgebra.h"

/**
 * @brief Returns 1 only when there is intersection that splits the other line
 * in 2 parts. Therefore intersection with only a corner of other line returns
 * 0.
 * 
 * See also: ft_line_intersection
 * 
 * @param line_a 
 * @param line_b 
 * @return int 
 */
int	ft_line_intersection_through(t_line line_a, t_line line_b)
{
	if (ft_line_side(line_a, line_b.a) != ft_line_side(line_a, line_b.b)
		&& !ft_line_point(line_a, line_b.a) && !ft_line_point(line_a, line_b.b))
		return (1);
	return (0);
}
