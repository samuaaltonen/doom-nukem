/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_multiply.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 15:51:24 by htahvana          #+#    #+#             */
/*   Updated: 2022/11/03 15:52:30 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "liblinearalgebra.h"

t_vector2	ft_vec2_mult(t_vector2 a, double f)
{
	a.x *= f;
	a.y *= f;
	return (a);
}

t_vector3	ft_vec3_mult(t_vector3 a, double f)
{
	a.x *= f;
	a.y *= f;
	a.z *= f;
	return (a);
}