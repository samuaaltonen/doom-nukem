/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_sub.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 16:05:51 by htahvana          #+#    #+#             */
/*   Updated: 2022/12/08 16:07:26 by saaltone         ###   ########.fr       */
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
