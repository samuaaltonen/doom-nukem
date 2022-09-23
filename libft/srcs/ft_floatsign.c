/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_floatsign.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 20:33:23 by saaltone          #+#    #+#             */
/*   Updated: 2022/03/07 20:37:09 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_floatsign(long double number)
{
	t_ldouble_cast	ldouble_parts;

	ldouble_parts.f = number;
	return (ldouble_parts.s_parts.sign);
}
