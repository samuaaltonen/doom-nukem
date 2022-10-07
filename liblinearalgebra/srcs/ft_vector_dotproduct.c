/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_dotproduct.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 14:56:45 by saaltone          #+#    #+#             */
/*   Updated: 2022/10/07 15:17:22 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "liblinearalgebra.h"

/**
 * Returns dot product of 2 vectors.
 */
double	ft_vector_dotproduct(t_vector2 a, t_vector2 b)
{
	return (a.x * b.x + a.y * b.y);
}
