/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_normalize.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 14:10:05 by htahvana          #+#    #+#             */
/*   Updated: 2022/11/02 14:37:28 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "liblinearalgebra.h"

t_vector2 ft_vector2_normalize(t_vector2 a)
{
	double length;

	length = ft_vector_length(a);
	if(length == 0.f)
		return ((t_vector2){0.f,0.f});
	return ((t_vector2){a.x / length, a.y / length});
}