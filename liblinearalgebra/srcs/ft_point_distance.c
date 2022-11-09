/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_point_distance.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 17:29:44 by htahvana          #+#    #+#             */
/*   Updated: 2022/11/09 17:31:20 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "liblinearalgebra.h"

double	ft_point_distance(t_vector2 a, t_vector2 b)
{
	return (ft_vector_length((t_vector2){b.x - a.x, b.y - a.y}));
}