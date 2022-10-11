/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_angle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 12:11:15 by saaltone          #+#    #+#             */
/*   Updated: 2022/10/11 12:13:49 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "liblinearalgebra.h"

/**
 * Returns angle between 2 vectors in radians.
 */
double	ft_vector_angle(t_vector2 a, t_vector2 b)
{
	return (acos(ft_vector_dotproduct(a, b)
			/ (ft_vector_length(a) * ft_vector_length(b))));
}
