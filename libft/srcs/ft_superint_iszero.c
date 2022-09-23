/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_superint_iszero.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 22:15:08 by saaltone          #+#    #+#             */
/*   Updated: 2022/03/09 22:15:50 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Returns 1 if all values of the superint are zero.
*/
int	ft_superint_iszero(t_superint **superint)
{
	int	i;

	i = (*superint)->count - 1;
	while (i >= 0)
	{
		if ((*superint)->numbers[i] > 0)
			return (0);
		i--;
	}
	return (1);
}
