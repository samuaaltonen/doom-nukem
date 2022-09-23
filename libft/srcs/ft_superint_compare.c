/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_superint_compare.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 22:00:59 by saaltone          #+#    #+#             */
/*   Updated: 2022/03/11 01:11:49 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Compares two superints. Returns: 
 * positive if a is higher than b
 * 0 if a is same as b
 * negative if a is less than b
*/
int	ft_superint_compare(t_superint **a, t_superint **b)
{
	int	i;

	if ((*a)->count != (*b)->count)
		return ((*a)->count - (*b)->count);
	i = (*a)->count - 1;
	while (i > 0 && (*a)->numbers[i] == (*b)->numbers[i])
		i--;
	return ((*a)->numbers[i] - (*b)->numbers[i]);
}
