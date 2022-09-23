/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_superint_minus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 17:41:54 by saaltone          #+#    #+#             */
/*   Updated: 2022/03/14 15:37:44 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	update_count(t_superint **superint)
{
	if ((*superint)->count <= 1)
		return (1);
	if ((*superint)->numbers[(*superint)->count - 1] == 0)
	{
		(*superint)->count--;
		update_count(superint);
	}
	return (1);
}

/*
 * Performs substraction for 2 superints. If value goes to negative, sets it to
 * zero.
*/
int	ft_superint_minus(t_superint **from, t_superint **minus)
{
	t_sll	temp;
	t_ull	carry;
	int		i;

	if (ft_superint_compare(from, minus) < 0)
		return (ft_superint_zero(from));
	i = -1;
	carry = 0;
	while (++i < (*minus)->count || carry)
	{
		if (i > (*from)->count - 1)
			return (ft_superint_zero(from));
		temp = (t_sll)(*from)->numbers[i] - carry;
		if (i < (*minus)->count)
			temp -= (t_sll)(*minus)->numbers[i];
		carry = 0;
		if (temp < 0)
		{
			(*from)->numbers[i] = 1000000000 + temp;
			carry = 1;
		}
		else
			(*from)->numbers[i] = temp;
	}
	return (update_count(from));
}

/*
 * Substract int from superint
*/
int	ft_superint_minus_int(t_superint **from, int minus)
{
	t_sll	temp;
	int		i;

	i = 0;
	while (minus)
	{
		if (i > (*from)->count - 1)
			return (ft_superint_zero(from));
		temp = (t_sll)(*from)->numbers[i] - minus;
		minus = 0;
		if (temp < 0)
		{
			(*from)->numbers[i] = 1000000000 + temp;
			minus = -temp;
		}
		else
			(*from)->numbers[i] = temp;
		i++;
	}
	return (1);
}
