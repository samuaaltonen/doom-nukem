/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_superint_multiply.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 21:39:21 by saaltone          #+#    #+#             */
/*   Updated: 2022/03/14 16:05:16 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Multiplies superint with an integer.
*/
int	ft_superint_multiply_int(t_superint **target, int multiplier)
{
	t_ull	temp;
	int		i;
	int		carry;

	if (multiplier <= 0)
		return (ft_superint_zero(target));
	i = -1;
	carry = 0;
	while (++i < (*target)->count || carry)
	{
		if ((*target)->allocated < i + 1 && !ft_superint_expand(target))
			return (0);
		temp = carry;
		carry = 0;
		if (i < (*target)->count)
			temp += (t_sll)(*target)->numbers[i] * multiplier;
		if (temp >= 1000000000)
			carry = temp / 1000000000;
		(*target)->numbers[i] = temp % 1000000000;
		if (i > (*target)->count - 1)
			(*target)->count++;
	}
	return (1);
}

/*
 * Multiplies superint with another superint. The idea is to loop through all
 * numbers in multiplier and multiply target with each of those numbers
 * differently.
 * After multiplication multiplies the target i times 1000000000 (to correct
 * magnitude) and then increases result with the target.
 * At the end of the loop sets target back to original number so it remains
 * unchanged for the next multiplier.
*/
int	ft_superint_multiply(t_superint **n, t_superint **multiplier)
{
	t_superint	*copy;
	t_superint	*res;
	int			i;

	if (ft_superint_iszero(n) || ft_superint_iszero(multiplier))
	{
		ft_superint_zero(n);
		return (1);
	}
	copy = ft_superint_new(0, 10);
	res = ft_superint_new(0, 10);
	if (!res || !ft_superint_clone(&copy, n))
		return (0);
	i = -1;
	while (++i < (*multiplier)->count)
	{
		if (!ft_superint_multiply_int(n, (*multiplier)->numbers[i])
			|| !ft_superint_shift_block(n, i)
			|| !ft_superint_plus(&res, n) || !ft_superint_clone(n, &copy))
			return (0);
	}
	ft_superint_swap(&res, n);
	ft_superint_destroy(&res);
	ft_superint_destroy(&copy);
	return (1);
}
