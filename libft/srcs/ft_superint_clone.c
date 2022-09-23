/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_superint_clone.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 22:12:01 by saaltone          #+#    #+#             */
/*   Updated: 2022/03/11 12:06:43 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Clones superint values and count.
*/
int	ft_superint_clone(t_superint **to, t_superint **from)
{
	int	i;

	i = (*from)->count - 1;
	while (i >= 0)
	{
		while ((*to)->allocated < i + 1)
		{
			if (!ft_superint_expand(to))
				return (0);
		}
		(*to)->numbers[i] = (*from)->numbers[i];
		i--;
	}
	(*to)->count = (*from)->count;
	return (1);
}
