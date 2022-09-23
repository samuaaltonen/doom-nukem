/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_superint_shift.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 21:50:05 by saaltone          #+#    #+#             */
/*   Updated: 2022/03/09 22:05:58 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Shifts superint to the left by shift amount.
*/
int	ft_superint_shift(t_superint **target, int shift)
{
	int	i;

	i = 0;
	while (i < shift)
	{
		if (!ft_superint_multiply_int(target, 2))
			return (0);
		i++;
	}
	return (1);
}

/*
 * Treats whole ints as shift "steps". Max value of these ints are specified to
 * be under 1 billion so one shift multiplies the number by 1 billion.
*/
int	ft_superint_shift_block(t_superint **target, int shift)
{
	int	i;

	i = 0;
	while (i < shift)
	{
		if (!ft_superint_multiply_int(target, 1000000000))
			return (0);
		i++;
	}
	return (1);
}
