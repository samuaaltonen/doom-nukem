/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector_draw_parent.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 17:23:43 by saaltone          #+#    #+#             */
/*   Updated: 2022/10/20 18:04:00 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * Draws partial parts of portal wall:
 * 
 * - parent ceiling
 * - parent floor
 * - parent top partial wall
 * - parent bottom partial wall
*/
void	draw_parent(t_app *app, int x, t_rayhit *hit)
{
	t_rayhit	parenthit;

	ft_memcpy(&parenthit, hit, sizeof(t_rayhit));
	parenthit.wall_start = hit->parent_wall_start;
	parenthit.wall_end = hit->parent_wall_end;
	draw_ceiling(app, x, &parenthit);
	draw_floor(app, x, &parenthit);
	parenthit.wall_end = hit->wall_start;
	draw_wall(app, x, &parenthit, OCCLUDE_TOP);
	parenthit.wall_start = hit->wall_end;
	parenthit.wall_end = hit->parent_wall_end;
	draw_wall(app, x, &parenthit, OCCLUDE_BOTTOM);
}
