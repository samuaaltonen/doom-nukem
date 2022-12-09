/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_normalize.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 14:10:05 by htahvana          #+#    #+#             */
/*   Updated: 2022/12/09 15:28:36 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "liblinearalgebra.h"

/**
 * @brief Returns normalized vector a.
 * 
 * @param a 
 * @return t_vector2 
 */
t_vector2	ft_vector2_normalize(t_vector2 a)
{
	double	length;

	length = ft_vector_length(a);
	if (length == 0.0f)
		return ((t_vector2){0.0, 0.0});
	return ((t_vector2){a.x / length, a.y / length});
}
