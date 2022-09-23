/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 09:33:10 by saaltone          #+#    #+#             */
/*   Updated: 2021/11/05 16:48:12 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	unsigned char	*allocated;

	allocated = (unsigned char *) malloc(size);
	if (!allocated)
		return (NULL);
	ft_bzero(allocated, size);
	return (allocated);
}
