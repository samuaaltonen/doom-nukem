/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_limit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 15:17:27 by htahvana          #+#    #+#             */
/*   Updated: 2022/11/01 15:21:04 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "liblinearalgebra.h"

void	ft_vector2_limit(t_vector2 *a, double limit)
{
	if(limit > 0)
	{
		if (a->x > limit)
			a->x = limit;
		if(a->y > limit)
			a->y = limit;
	}
	else
		if (a->x < limit)
			a->x = limit;
		if(a->y < limit)
			a->y = limit;
}

void	ft_vector3_limit(t_vector3 *a, double limit)
{
	if(limit > 0)
	{
		if (a->x > limit)
			a->x = limit;
		if(a->y > limit)
			a->y = limit;
		if(a->z > limit)
			a->z = limit;
	}
	else
		if (a->x < limit)
			a->x = limit;
		if(a->y < limit)
			a->y = limit;
		if(a->z > limit)
			a->z = limit;
}