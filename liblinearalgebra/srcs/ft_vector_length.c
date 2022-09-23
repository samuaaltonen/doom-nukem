/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_length.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 15:07:05 by saaltone          #+#    #+#             */
/*   Updated: 2022/09/23 21:48:59 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "liblinearalgebra.h"
#include "math.h"

/**
 * Returns vector length.
*/
double	ft_vector_length(t_vector2 a)
{
	return (sqrt(a.x * a.x + a.y * a.y));
}
