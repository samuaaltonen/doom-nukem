/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_expand.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 17:19:18 by saaltone          #+#    #+#             */
/*   Updated: 2022/01/20 10:41:40 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_array	*ft_array_expand(t_array **array)
{
	t_array	*new_array;

	if (!array || !(*array))
		return (NULL);
	new_array = ft_array_create((*array)->element_size,
			((*array)->allocated) * 2);
	ft_memcpy(new_array->data, (*array)->data, (*array)->allocated);
	new_array->used = (*array)->used;
	free((*array)->data);
	free(*array);
	return (new_array);
}
