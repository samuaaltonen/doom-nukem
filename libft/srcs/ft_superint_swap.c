/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_superint_swap.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 21:35:37 by saaltone          #+#    #+#             */
/*   Updated: 2022/03/09 21:47:46 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Swaps given superints.
*/
void	ft_superint_swap(t_superint **a, t_superint **b)
{
	t_superint	*temp;

	temp = *b;
	*b = *a;
	*a = temp;
}
