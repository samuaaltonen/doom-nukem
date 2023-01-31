/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_line_intersection_full.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 13:31:32 by saaltone          #+#    #+#             */
/*   Updated: 2023/01/31 15:59:08 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "liblinearalgebra.h"

/**
 * @brief Returns 1 if all points on line segment a can be found from line
 * segment b, and vice versa.
 * 
 * @param a 
 * @param b 
 * @return int 
 */
int	ft_line_intersection_full(t_line a, t_line b)
{
	return (ft_line_point(a, b.a) && ft_line_point(a, b.b));
}
