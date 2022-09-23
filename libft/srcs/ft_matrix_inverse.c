/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_inverse.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 16:00:58 by saaltone          #+#    #+#             */
/*   Updated: 2022/07/12 16:04:36 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_matrix2	ft_matrix_inverse(t_matrix2 matrix)
{
	double	multiplier;

	multiplier = 1.0f / (matrix.a.x * matrix.b.y - matrix.b.x * matrix.a.y);
	return ((t_matrix2){
		(t_vector2){multiplier * matrix.b.y, -multiplier * matrix.a.y},
		(t_vector2){-multiplier * matrix.b.x, multiplier * matrix.a.x}
	});
}
