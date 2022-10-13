/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_angle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 12:11:15 by saaltone          #+#    #+#             */
/*   Updated: 2022/10/13 12:17:11 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "liblinearalgebra.h"

/**
 * Returns angle between 2 vectors in radians.
 */
double	ft_vector_angle(t_vector2 a, t_vector2 b)
{
	double	ratio;

	ratio = ft_vector_dotproduct(a, b)
		/ (ft_vector_length(a) * ft_vector_length(b));
	if (ratio <= -1.0 || ratio >= 1.0)
		return (0.0);
	return (acos(ratio));
}
