/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 14:34:02 by saaltone          #+#    #+#             */
/*   Updated: 2021/11/10 14:34:50 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strnequ(char const *s1, char const *s2, size_t n)
{
	int	cmp;

	if (!s1 && !s2)
		return (1);
	if (!s1 || !s2)
		return (0);
	cmp = ft_strncmp(s1, s2, n);
	if (cmp == 0)
		return (1);
	return (0);
}
