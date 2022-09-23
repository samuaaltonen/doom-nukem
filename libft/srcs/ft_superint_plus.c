/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_superint_plus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 13:45:20 by saaltone          #+#    #+#             */
/*   Updated: 2022/03/14 15:44:18 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Adds second superint to the first one.
*/
int	ft_superint_plus(t_superint **addto, t_superint **add)
{
	t_ull	temp;
	t_ull	carry;
	int		i;

	i = -1;
	carry = 0;
	while (++i < (*add)->count || carry)
	{
		if ((*addto)->allocated < i + 1 && !ft_superint_expand(addto))
			return (0);
		temp = (t_ull)(*addto)->numbers[i];
		if (i < (*add)->count)
			temp += (t_ull)(*add)->numbers[i];
		temp += carry;
		carry = 0;
		if (temp >= 1000000000)
			carry = 1;
		if (temp >= 1000000000)
			(*addto)->numbers[i] = temp % 1000000000;
		else
			(*addto)->numbers[i] = temp;
		if (i > (*addto)->count - 1)
			(*addto)->count++;
	}
	return (1);
}

/*
 * Adds int to superint.
*/
int	ft_superint_plus_int(t_superint **addto, int plus)
{
	t_ull	temp;
	int		i;

	i = 0;
	while (plus)
	{
		if ((*addto)->allocated < i + 1 && !ft_superint_expand(addto))
			return (0);
		temp = (t_ull)(*addto)->numbers[i] + plus;
		plus = 0;
		if (temp >= 1000000000)
			plus = temp / 1000000000;
		(*addto)->numbers[i] = temp % 1000000000;
		if (i > (*addto)->count - 1)
			(*addto)->count++;
		i++;
	}
	return (1);
}

/*
 * Adds unsigned long long to superint.
*/
int	ft_superint_plus_ull(t_superint **addto, t_ull plus)
{
	t_ull	temp;
	int		i;

	if (plus <= 2147483647)
		return (ft_superint_plus_int(addto, plus));
	if (!ft_superint_plus_int(addto, 2147483647))
		return (0);
	plus -= 2147483647;
	i = 0;
	while (plus)
	{
		if ((*addto)->allocated < i + 1 && !ft_superint_expand(addto))
			return (0);
		temp = (t_ull)(*addto)->numbers[i] + plus;
		plus = 0;
		if (temp >= 1000000000)
			plus = temp / 1000000000;
		(*addto)->numbers[i] = temp % 1000000000;
		if (i > (*addto)->count - 1)
			(*addto)->count++;
		i++;
	}
	return (1);
}
