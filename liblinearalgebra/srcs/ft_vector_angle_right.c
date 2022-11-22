/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_angle_right.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 14:30:43 by saaltone          #+#    #+#             */
/*   Updated: 2022/11/22 14:32:56 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "liblinearalgebra.h"

/**
 * @brief Returns right side angle between 2 vectors. 90 degrees to the right
 * would return 90 degrees (PI / 2), while 90 degrees to the left would return
 * 270 degrees (Pi / 2 * 3).g
 * 
 * @param a 
 * @param b 
 * @return double 
 */
double	ft_vector_angle_right(t_vector2 a, t_vector2 b)
{
	double	ratio;

	ratio = ft_vector_dotproduct(a, b)
		/ (ft_vector_length(a) * ft_vector_length(b));
	if (ratio <= -1.0 || ratio >= 1.0)
		return (0.0);
	if (ft_vector_crossproduct(a, b) < 0.0)
		return (acos(ratio) + M_PI);
	return (acos(ratio));
}
