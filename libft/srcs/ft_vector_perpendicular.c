/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_perpendicular.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 12:50:29 by saaltone          #+#    #+#             */
/*   Updated: 2022/07/12 16:05:03 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Returns perpendicular right hand side 2d vector of vector a. 
 * Result is right hand side vector so it points to right of the original
 * vector.
*/
t_vector2	ft_vector_perpendicular(t_vector2 a)
{
	t_vector2	b;

	b.x = -a.y;
	b.y = a.x;
	return (b);
}
