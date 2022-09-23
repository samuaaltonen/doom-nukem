/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_superint_divide.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 22:03:14 by saaltone          #+#    #+#             */
/*   Updated: 2022/03/14 15:31:39 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	handle_overshoot(t_superint **n, t_superint **d, t_superint **temp,
		t_ull *res)
{
	if (ft_superint_compare(temp, n) > 0)
	{
		*res -= 1;
		if (!ft_superint_clone(temp, d)
			|| !ft_superint_multiply_int(temp, *res))
			return (0);
		return (handle_overshoot(n, d, temp, res));
	}
	return (1);
}

/*
 * Performs input checks: If denumerator is zero, returns 0 (division by zero).
 * If numerator is zero, returns 1 (no error, but no need to continue division).
 * If numerator is less than denumerator, clones numerator to remainder and
 * returns 1 (remaider is set, no need to continue division).
 * Any other case, returns 2 (continues division).
*/
static int	check_input(t_superint **n, t_superint **d, t_superint **mod)
{
	if (ft_superint_iszero(d))
		return (0);
	if (ft_superint_iszero(n))
		return (1);
	if (ft_superint_compare(n, d) < 0)
	{
		if (!ft_superint_clone(mod, n))
			return (0);
		return (1);
	}
	return (2);
}

/*
 * Divides 2 superints that are same size in magnitude (scaled to same count).
 * Returns zero on error.
*/
int	ft_superint_divide_samesize(t_superint **n, t_superint **d,
		t_superint **mod, t_ull *res)
{
	t_superint	*temp;
	int			input_check;

	*res = 0;
	input_check = check_input(n, d, mod);
	if (input_check <= 1)
		return (input_check);
	if ((*n)->count < (*d)->count)
		*res = 0;
	else
		*res = (*n)->numbers[(*n)->count - 1] / (*d)->numbers[(*d)->count - 1];
	if (*res > 9)
		*res = 9;
	temp = ft_superint_new(0, 3);
	if (!ft_superint_clone(&temp, d)
		|| !ft_superint_multiply_int(&temp, *res))
		return (0);
	handle_overshoot(n, d, &temp, res);
	if (!ft_superint_clone(mod, n)
		|| !ft_superint_clone(&temp, d)
		|| !ft_superint_multiply_int(&temp, *res))
		return (0);
	ft_superint_minus(mod, &temp);
	ft_superint_destroy(&temp);
	return (1);
}
