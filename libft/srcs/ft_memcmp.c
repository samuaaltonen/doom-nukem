/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 12:29:13 by saaltone          #+#    #+#             */
/*   Updated: 2021/11/10 10:44:12 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while (i < n && ((unsigned char *) s1)[i] == ((unsigned char *) s2)[i])
		i++;
	if (i == n)
		return (0);
	else
		return (((unsigned char *) s1)[i] - ((unsigned char *) s2)[i]);
}
