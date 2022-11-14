/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lerp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 15:06:41 by htahvana          #+#    #+#             */
/*   Updated: 2022/11/03 15:57:59 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "liblinearalgebra.h"

double	ft_lerp(double a, double b, double f)
{
	return (a + f * (b - a));
}

t_vector2	ft_vec2_lerp(t_vector2 a, t_vector2 b, double f)
{
	t_vector2 new;

	new.x = ft_lerp(a.x, b.x, f);
	new.y = ft_lerp(a.y, b.y, f);
	return (new);
}

t_vector3	ft_vec3_lerp(t_vector3 a, t_vector3 b, double f)
{
	t_vector3 new;

	new.x = ft_lerp(a.x, b.x, f);
	new.y = ft_lerp(a.y, b.y, f);
	new.z = ft_lerp(a.y, b.y, f);
	return (new);
}