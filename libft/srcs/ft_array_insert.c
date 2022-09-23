/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_insert.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 17:19:08 by saaltone          #+#    #+#             */
/*   Updated: 2022/01/20 10:41:19 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_array_insert(t_array **array, void *data)
{
	if (!array || !(*array))
		return (NULL);
	if ((*array)->used >= (*array)->allocated)
	{
		*array = ft_array_expand(array);
		if (!(*array))
			return (NULL);
	}
	ft_memcpy((*array)->data + ((*array)->used * (*array)->element_size), data,
		(*array)->element_size);
	(*array)->used++;
	return ((*array)->data + (*array)->element_size);
}
