/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_superint_print.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 14:10:21 by saaltone          #+#    #+#             */
/*   Updated: 2022/03/09 14:10:35 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_superint_print(t_superint **superint)
{
	int	i;
	int	j;
	int	temp;
	int	temp2;

	i = (*superint)->count - 1;
	while (i >= 0)
	{
		temp = (*superint)->numbers[i];
		j = 100000000;
		while (j > 0)
		{
			temp2 = temp / j;
			ft_putchar('0' + temp2);
			temp -= temp2 * j;
			j /= 10;
		}
		i--;
	}
	ft_putchar('\n');
}
