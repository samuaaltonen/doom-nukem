/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_resize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 13:37:57 by saaltone          #+#    #+#             */
/*   Updated: 2022/09/23 21:49:13 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "liblinearalgebra.h"

t_vector2	ft_vector_resize(t_vector2 a, double size)
{
	double	scale;

	scale = size / ft_vector_length(a);
	return ((t_vector2){a.x * scale, a.y * scale});
}
