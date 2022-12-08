/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_add.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 16:15:30 by htahvana          #+#    #+#             */
/*   Updated: 2022/12/08 16:06:46 by saaltone         ###   ########.fr       */
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
