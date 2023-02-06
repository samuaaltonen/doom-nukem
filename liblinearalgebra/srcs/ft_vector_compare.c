/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_compare.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 15:40:52 by htahvana          #+#    #+#             */
/*   Updated: 2023/01/31 18:41:14 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "liblinearalgebra.h"

/**
 * @brief Compares vectors.
 * 
 * @param a 
 * @param b 
 * @return int 
 */
int	ft_vector_compare(t_vector2 a, t_vector2 b)
{
	if (a.x != b.x || a.y != b.y)
		return (0);
	return (1);
}
