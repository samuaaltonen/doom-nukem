/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 14:58:33 by htahvana          #+#    #+#             */
/*   Updated: 2023/01/09 14:56:51 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "liblinearalgebra.h"

/**
 * @brief Swaps t_point values.
 * 
 * @param a 
 * @param b 
 */
void	ft_point_swap(t_point *a, t_point *b)
{
	t_point	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

/**
 * @brief Swaps integers.
 * 
 * @param a 
 * @param b 
 */
void	ft_swap(int *a, int *b)
{
	int	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	ft_double_swap(double *a, double *b)
{
	double	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	ft_vec2_swap(t_vector2 *a, t_vector2 *b)
{
	t_vector2	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}
