/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_superint_to_ull.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 21:40:45 by saaltone          #+#    #+#             */
/*   Updated: 2022/03/10 21:43:53 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Casts superint into unsigned long long. Assumes superint is small enough to
 * fit in it.
*/
t_ull	ft_superint_to_ull(t_superint **superint)
{
	t_ull	result;

	result = 0;
	if ((*superint)->count >= 3)
		result += (*superint)->numbers[2] * 1000000000000000000ULL;
	if ((*superint)->count >= 2)
		result += (*superint)->numbers[1] * 1000000000ULL;
	if ((*superint)->count >= 1)
		result += (*superint)->numbers[0];
	return (result);
}
