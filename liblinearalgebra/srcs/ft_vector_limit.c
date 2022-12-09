/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_limit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 15:17:27 by htahvana          #+#    #+#             */
/*   Updated: 2022/12/09 15:29:29 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "liblinearalgebra.h"

/**
 * @brief Limits vector2 values to a number.
 * 
 * @param a 
 * @param limit 
 */
void	ft_vector2_limit(t_vector2 *a, double limit)
{
	if (limit > 0)
	{
		if (a->x > limit)
			a->x = limit;
		if (a->y > limit)
			a->y = limit;
		return ;
	}
	if (a->x < limit)
		a->x = limit;
	if (a->y < limit)
		a->y = limit;
}

/**
 * @brief Limits vector3 values to a number.
 * 
 * @param a 
 * @param limit 
 */
void	ft_vector3_limit(t_vector3 *a, double limit)
{
	if (limit > 0)
	{
		if (a->x > limit)
			a->x = limit;
		if (a->y > limit)
			a->y = limit;
		if (a->z > limit)
			a->z = limit;
		return ;
	}
	if (a->x < limit)
		a->x = limit;
	if (a->y < limit)
		a->y = limit;
	if (a->z > limit)
		a->z = limit;
}
