/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector_draw_partial.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 17:23:43 by saaltone          #+#    #+#             */
/*   Updated: 2022/11/25 16:20:38 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * @brief Draws partial parts of portal wall:
 * 
 * - ceiling
 * - floor
 * - top partial wall
 * - bottom partial wall
 * 
 * @param app 
 * @param x 
 * @param hit 
 */
void	draw_portal_partial(t_app *app, int x, t_rayhit *hit)
{
	int			temp;
	t_rayhit	portalhit;

	ft_memcpy(&portalhit, hit, sizeof(t_rayhit));
	draw_ceiling(app, x, hit);
	draw_floor(app, x, hit);
	portalhit.sector = &app->sectors[hit->wall_type];
	set_wall_vertical_positions(app, &portalhit);
	temp = hit->wall_end;
	hit->wall_end = portalhit.wall_start;
	if (hit->wall_start >= WIN_H - 1)
		draw_wall(app, x, hit, OCCLUDE_BOTH);
	else
		draw_wall(app, x, hit, OCCLUDE_TOP);
	hit->wall_start = portalhit.wall_end;
	hit->wall_end = temp;
	if (hit->wall_start >= WIN_H - 1)
		draw_wall(app, x, hit, OCCLUDE_BOTH);
	else
		draw_wall(app, x, hit, OCCLUDE_BOTTOM);
}

/**
 * @brief Draws partial parts of portal wall using parent sector info:
 * 
 * - parent ceiling
 * - parent floor
 * - parent top partial wall
 * - parent bottom partial wall
 * 
 * @param app 
 * @param x 
 * @param hit 
 */
void	draw_portal_partial_parent(t_app *app, int x, t_rayhit *hit)
{
	t_rayhit	parenthit;

	ft_memcpy(&parenthit, hit, sizeof(t_rayhit));
	parenthit.sector = &app->sectors[hit->sector->parent_sector];
	parenthit.wall_start_actual = hit->parent_wall_start_actual;
	parenthit.wall_start = hit->parent_wall_start;
	parenthit.wall_end = hit->parent_wall_end;
	set_wall_vertical_positions(app, &parenthit);
	parenthit.light = parenthit.sector->light;
	draw_ceiling(app, x, &parenthit);
	draw_floor(app, x, &parenthit);
	parenthit.light = hit->light;
	parenthit.wall_end = hit->wall_start;
	if (parenthit.wall_start >= WIN_H - 1)
		draw_wall(app, x, &parenthit, OCCLUDE_BOTH);
	else
		draw_wall(app, x, &parenthit, OCCLUDE_TOP);
	parenthit.wall_start = hit->wall_end;
	parenthit.wall_end = hit->parent_wall_end;
	if (parenthit.wall_start <= 0)
		draw_wall(app, x, &parenthit, OCCLUDE_BOTH);
	else
		draw_wall(app, x, &parenthit, OCCLUDE_BOTTOM);
}

/**
 * @brief Draws partial hole if ceiling or floor of the member sector is higher
 * or lower than the parent sector.
 * 
 * @param app 
 * @param x 
 * @param hit 
 */
void	draw_portal_partial_hole(t_app *app, int x, t_rayhit *hit)
{
	t_rayhit	parenthit;

	if (hit->wall_start >= hit->parent_wall_start
		&& hit->wall_end <= hit->parent_wall_end)
		return ;
	ft_memcpy(&parenthit, hit, sizeof(t_rayhit));
	parenthit.sector = &app->sectors[hit->sector->parent_sector];
	parenthit.wall_start_actual = hit->wall_start_actual;
	parenthit.wall_start = hit->wall_start;
	parenthit.wall_end = hit->parent_wall_start;
	if (hit->wall_start < hit->parent_wall_start)
	{
		if (parenthit.wall_start >= WIN_H - 1)
			draw_wall(app, x, &parenthit, OCCLUDE_BOTH);
		else
			draw_wall(app, x, &parenthit, OCCLUDE_TOP);
	}
	parenthit.wall_start = hit->parent_wall_end;
	parenthit.wall_end = hit->wall_end;
	if (hit->wall_end < hit->parent_wall_end)
		return ;
	if (parenthit.wall_start <= 0)
		draw_wall(app, x, &parenthit, OCCLUDE_BOTH);
	else
		draw_wall(app, x, &parenthit, OCCLUDE_BOTTOM);
}
