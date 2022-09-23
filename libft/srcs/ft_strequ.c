/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 14:34:02 by saaltone          #+#    #+#             */
/*   Updated: 2021/11/10 14:30:47 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strequ(char const *s1, char const *s2)
{
	int	cmp;

	if (!s1 && !s2)
		return (1);
	if (!s1 || !s2)
		return (0);
	cmp = ft_strcmp(s1, s2);
	if (cmp == 0)
		return (1);
	return (0);
}
