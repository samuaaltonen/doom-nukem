/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_line_intersection_full.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 13:31:32 by saaltone          #+#    #+#             */
/*   Updated: 2022/11/29 15:20:26 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "liblinearalgebra.h"

/**
 * @brief Returns 1 if both line segments are parts of the same infinite line.
 * (i.e. all points on line segment a can be found from line segment b, and
 * vice versa)
 * 
 * AB cross AC = AB cross AD = 0
 * 
 * @param a 
 * @param b 
 * @return int 
 */
int	ft_line_intersection_full(t_line a, t_line b)
{
	double	cross_ab_ac;
	double	cross_ab_ad;

	cross_ab_ac = ft_vector_crossproduct(ft_vector2_sub(a.b, a.a),
			ft_vector2_sub(b.a, a.a));
	cross_ab_ad = ft_vector_crossproduct(ft_vector2_sub(a.b, a.a),
			ft_vector2_sub(b.b, a.a));
	return (cross_ab_ac == 0.0 && cross_ab_ad == 0.0);
}
