/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_line_comparison.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 18:43:25 by htahvana          #+#    #+#             */
/*   Updated: 2023/01/27 18:53:28 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "liblinearalgebra.h"

static void	sort_line_points(t_line *line)
{
	if (line->a.y < line->b.y)
		ft_vec2_swap(&line->a, &line->b);
	else if (line->a.y == line->b.y && line->a.x > line->b.x)
		ft_vec2_swap(&line->a, &line->b);
	return ;
}

t_bool	ft_cmp_line_points(t_line a, t_line b)
{
	sort_line_points(&a);
	sort_line_points(&b);
	if (a.a.x == b.a.x
		&& a.a.y == b.a.y
		&& a.b.x == b.b.x
		&& a.b.y == b.b.y)
		return (TRUE);
	return (FALSE);
}
