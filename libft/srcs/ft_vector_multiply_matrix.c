/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector2_multiply_matrix.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 11:14:06 by saaltone          #+#    #+#             */
/*   Updated: 2022/06/10 11:16:32 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Multiplies vector with a matrix
*/
t_vector2	ft_vector_multiply_matrix(t_vector2 vector, t_matrix2 matrix)
{
	t_vector2	result;

	result.x = vector.x * matrix.a.x + vector.y * matrix.b.x;
	result.y = vector.x * matrix.a.y + vector.y * matrix.b.y;
	return (result);
}
