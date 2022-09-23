/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_superint_log10.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 23:37:23 by saaltone          #+#    #+#             */
/*   Updated: 2022/03/10 23:44:07 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Returns base-10 logarithm of superint.
*/
int	ft_superint_log10(t_superint **superint)
{
	int	log10;

	log10 = -1;
	if ((*superint)->count > 1)
		log10 += 9 * ((*superint)->count - 1);
	log10 += ft_count_digits((*superint)->numbers[(*superint)->count - 1]);
	return (log10);
}
