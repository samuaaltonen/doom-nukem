/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_multiply.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 15:51:24 by htahvana          #+#    #+#             */
/*   Updated: 2022/12/09 15:29:13 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "liblinearalgebra.h"

/**
 * @brief Multiplies vector2 by scalar.
 * 
 * @param a 
 * @param f 
 * @return t_vector2 
 */
t_vector2	ft_vec2_mult(t_vector2 a, double f)
{
	a.x *= f;
	a.y *= f;
	return (a);
}

/**
 * @brief Multiplies vector3 by scalar.
 * 
 * @param a 
 * @param f 
 * @return t_vector2 
 */
t_vector3	ft_vec3_mult(t_vector3 a, double f)
{
	a.x *= f;
	a.y *= f;
	a.z *= f;
	return (a);
}
