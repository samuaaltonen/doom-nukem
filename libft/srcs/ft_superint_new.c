/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_superint_new.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 09:50:19 by saaltone          #+#    #+#             */
/*   Updated: 2022/08/08 18:12:16 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	superint_init_zeros(t_superint **superint)
{
	int	i;

	i = 0;
	while (i < (*superint)->allocated)
	{
		((*superint)->numbers)[i] = 0;
		i++;
	}
}

static void	superint_append_numbers(t_superint **superint, t_ull start)
{
	((*superint)->numbers)[0] = start % 1000000000;
	if (start >= 1000000000)
	{
		start /= 1000000000;
		((*superint)->numbers)[1] = start % 1000000000;
		(*superint)->count++;
	}
	if (start >= 1000000000)
	{
		start /= 1000000000;
		((*superint)->numbers)[2] = start % 1000000000;
		(*superint)->count++;
	}
}

/*
 * Creates superint struct and adds given start value to int. If necessary
 * splits up to 3 integers.
*/
t_superint	*ft_superint_new(t_ull start, int count)
{
	t_superint	*superint;

	superint = (t_superint *)malloc(sizeof(t_superint));
	if (!superint)
		return (NULL);
	superint->allocated = count;
	superint->count = 1;
	superint->numbers = (int *)malloc(sizeof(int) * count);
	if (!(superint->numbers))
	{
		free(superint);
		return (NULL);
	}
	superint_init_zeros(&superint);
	superint_append_numbers(&superint, start);
	return (superint);
}
