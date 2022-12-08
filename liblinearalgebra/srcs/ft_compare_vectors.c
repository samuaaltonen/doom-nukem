/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_compare_vectors.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 15:40:52 by htahvana          #+#    #+#             */
/*   Updated: 2022/11/29 15:20:07 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "liblinearalgebra.h"

int	ft_cmp_vec2(t_vector2 a, t_vector2 b)
{
	if (a.x != b.x || a.y != b.y)
		return (0);
	return (1);
}
