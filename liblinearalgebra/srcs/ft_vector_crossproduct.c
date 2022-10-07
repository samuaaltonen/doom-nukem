/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_crossproduct.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 17:24:58 by saaltone          #+#    #+#             */
/*   Updated: 2022/10/07 17:30:15 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "liblinearalgebra.h"

/**
 * Returns 2 dimensional cross product.
 */
double	ft_vector_crossproduct(t_vector2 a, t_vector2 b)
{
	return (a.x * b.y - a.y * b.x);
}
