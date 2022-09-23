/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_foreach.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 17:48:28 by saaltone          #+#    #+#             */
/*   Updated: 2022/01/17 18:17:28 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_array_foreach(t_array **array, void (*f)(void *))
{
	int	i;

	if (!array || !(*array))
		return ;
	i = 0;
	while (i < (*array)->used)
	{
		f((*array)->data + (i * (*array)->element_size));
		i++;
	}
}
