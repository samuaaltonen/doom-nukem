/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_create.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 17:05:36 by saaltone          #+#    #+#             */
/*   Updated: 2022/01/17 17:27:33 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_array	*ft_array_create(int element_size, int count)
{
	t_array	*array;

	array = (t_array *)malloc(sizeof(t_array));
	if (!array)
		return (NULL);
	array->data = malloc(element_size * count);
	if (!(array->data))
	{
		free(array);
		return (NULL);
	}
	array->element_size = element_size;
	array->allocated = count;
	array->used = 0;
	return (array);
}
