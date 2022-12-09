/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lerp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 15:06:41 by htahvana          #+#    #+#             */
/*   Updated: 2022/12/09 15:32:42 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "liblinearalgebra.h"

/**
 * @brief Lerps value a towards value b by multiplier f.
 * 
 * @param a 
 * @param b 
 * @param f 
 * @return double 
 */
double	ft_lerp(double a, double b, double f)
{
	return (a + f * (b - a));
}

/**
 * @brief Lerps vector2 a towards vector2 b by multiplier f.
 * 
 * @param a 
 * @param b 
 * @param f 
 * @return double 
 */
t_vector2	ft_vec2_lerp(t_vector2 a, t_vector2 b, double f)
{
	t_vector2	new;

	new.x = ft_lerp(a.x, b.x, f);
	new.y = ft_lerp(a.y, b.y, f);
	return (new);
}

/**
 * @brief Lerps vector3 a towards vector3 b by multiplier f.
 * 
 * @param a 
 * @param b 
 * @param f 
 * @return double 
 */
t_vector3	ft_vec3_lerp(t_vector3 a, t_vector3 b, double f)
{
	t_vector3	new;

	new.x = ft_lerp(a.x, b.x, f);
	new.y = ft_lerp(a.y, b.y, f);
	new.z = ft_lerp(a.y, b.y, f);
	return (new);
}
