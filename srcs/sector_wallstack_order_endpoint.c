/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector_wallstack_order_endpoint.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 23:00:02 by saaltone          #+#    #+#             */
/*   Updated: 2023/01/31 18:53:18 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * @brief Returns point that is 1 unit from starting point towards toward point.
 * 
 * @param start 
 * @param towards 
 * @return t_vector2 
 */
static t_vector2	along_line(t_vector2 start, t_vector2 towards)
{
	return (ft_vector2_add(start,
			ft_vector2_normalize(ft_vector2_sub(towards, start))));
}

/**
 * @brief Compares walls with same endpoint(s).
 * 
 * @param app 
 * @param a 
 * @param b 
 * @param compare 
 * @return t_bool 
 */
t_bool	compare_same_endpoint(t_app *app, t_line a, t_line b, t_bool *compare)
{
	t_vector2	along_a;
	t_vector2	along_b;

	if (ft_vector_compare(a.a, b.a) || ft_vector_compare(a.a, b.b))
	{
		along_a = along_line(a.a, a.b);
		if (ft_vector_compare(a.a, b.a))
			along_b = along_line(a.a, b.b);
		else
			along_b = along_line(a.a, b.a);
	}
	else if (ft_vector_compare(a.b, b.a) || ft_vector_compare(a.b, b.b))
	{
		along_a = along_line(a.b, a.a);
		if (ft_vector_compare(a.b, b.a))
			along_b = along_line(a.b, b.b);
		else
			along_b = along_line(a.b, b.a);
	}
	else
		return (FALSE);
	*compare = ft_vector_length(ft_vector2_sub(along_a, app->player.pos))
		< ft_vector_length(ft_vector2_sub(along_b, app->player.pos));
	return (TRUE);
}
