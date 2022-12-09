/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_point_distance.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 17:29:44 by htahvana          #+#    #+#             */
/*   Updated: 2022/12/09 15:30:46 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "liblinearalgebra.h"

/**
 * @brief Returns distance between 2 coordinates.
 * 
 * @param a 
 * @param b 
 * @return double 
 */
double	ft_point_distance(t_vector2 a, t_vector2 b)
{
	return (ft_vector_length((t_vector2){b.x - a.x, b.y - a.y}));
}
