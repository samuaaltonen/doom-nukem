/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_resize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 13:37:57 by saaltone          #+#    #+#             */
/*   Updated: 2022/07/08 15:48:50 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_vector2	ft_vector_resize(t_vector2 a, double size)
{
	double	scale;

	scale = size / ft_vector_length(a);
	return ((t_vector2){a.x * scale, a.y * scale});
}
