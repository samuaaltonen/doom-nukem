/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_add.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 16:15:30 by htahvana          #+#    #+#             */
/*   Updated: 2022/11/01 16:08:35 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "liblinearalgebra.h"

/**
 * @brief Adds b to a
 * 
 * @param a 
 * @param b 
 * @return t_vector2 
 */
t_vector2	ft_vector2_add(t_vector2 a, t_vector2 b)
{
	a.x = a.x + b.x;
	a.y = a.y + b.y;
	return (a);
}

t_vector3	ft_vector3_add(t_vector3 a, t_vector3 b)
{
		a.x = a.x + b.x;
		a.y = a.y + b.y;
		a.z = a.z + b.z;
		return (a);
}