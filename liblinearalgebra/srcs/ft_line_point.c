/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_line_point.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 14:32:32 by saaltone          #+#    #+#             */
/*   Updated: 2022/11/29 15:20:41 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "liblinearalgebra.h"

/**
 * @brief Returns 1 if coordinate point is located on line, 0 otherwise.
 * 
 * @param line 
 * @param coord 
 * @return int 
 */
int	ft_line_point(t_line line, t_vector2 coord)
{
	return ((line.b.x - line.a.x) * (coord.y - line.a.y)
		- (line.b.y - line.a.y) * (coord.x - line.a.x) == 0.0);
}
