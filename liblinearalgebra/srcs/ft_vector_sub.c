/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_sub.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 16:05:51 by htahvana          #+#    #+#             */
/*   Updated: 2022/11/01 15:14:43 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "liblinearalgebra.h"

/**
 * @brief Subtracts b from a
 * 
 * @param a 
 * @param b 
 */
t_vector2	ft_vector2_sub(t_vector2 a, t_vector2 b)
{
		a.x = a.x - b.x;
		a.y = a.y - b.y;
		return (a);
}

t_vector3	ft_vector3_sub(t_vector3 a, t_vector3 b)
{
		a.x = a.x - b.x;
		a.y = a.y - b.y;
		a.z = a.z - b.z;
		return (a);
}