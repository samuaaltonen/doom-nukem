/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector_wall_raycast.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 13:12:51 by saaltone          #+#    #+#             */
/*   Updated: 2023/02/20 20:21:31 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * @brief Raycast drawing part for portal walls.
 * 
 * If player is looking the wall from inside and wall is not from member sector,
 * draws possible partial walls on top and bottom of the portal (in case when
 * portal target sector floor is higher or ceiling is lower than portal sector).
 * 
 * Similarly if portal target is a member sector, draws possible partial parts
 * using member sector wall textures.
 * 
 * In case where player is looking the wall from inside, draws ceiling and floor
 * of a member sector and possibly partial parts when member sector floor is
 * lower than parent sectors or member sector ceiling is higher than parent
 * sectors.
 * 
 * @param app 
 * @param wall 
 * @param hit 
 * @param x 
 */
static void	raycast_portal(t_app *app, t_wall *wall, t_rayhit *hit, int x)
{
	if (!wall->is_member)
	{
		draw_portal_partial(app, x, hit);
		return ;
	}
	if (!wall->is_inside)
	{
		draw_portal_partial_parent(app, x, hit);
		return ;
	}
	draw_ceiling(app, x, hit);
	draw_floor(app, x, hit);
	draw_portal_partial_hole(app, x, hit);
}

/**
 * @brief Raycast drawing part for default walls. Draws first ceiling, then
 * floor and lastly the wall.
 * 
 * @param app 
 * @param hit 
 * @param x 
 */
static void	raycast_default(t_app *app, t_rayhit *hit, int x)
{
	draw_ceiling(app, x, hit);
	draw_floor(app, x, hit);
	draw_wall(app, x, hit, OCCLUDE_BOTH);
}

/**
 * @brief Initializes raycast hit struct.
 * 
 * @param app 
 * @param info 
 * @param hit 
 */
static void	raycast_init(t_app *app, t_raycast_info *info, t_rayhit *hit)
{
	if (info->limit.start < info->wall->start_x)
		info->limit.start = info->wall->start_x;
	if (info->limit.end > info->wall->end_x)
		info->limit.end = info->wall->end_x;
	hit->wall = info->wall;
	hit->wall_id = info->wall->wall_id;
	hit->occlusion_top = info->occlusion_top;
	hit->occlusion_bottom = info->occlusion_bottom;
	hit->floor_slope_height = 0.0;
	hit->ceil_slope_height = 0.0;
	hit->sector = &app->sectors[info->wall->sector_id];
	hit->wall_type = info->wall->wall_type;
	hit->texture = app->sectors[info->wall->sector_id] \
		.wall_textures[info->wall->wall_id];
	hit->light = (int)hit->sector->light;
	hit->drawn = FALSE;
}

/**
 * @brief Performs raycast to individual wall.
 * 
 * @param app 
 * @param thread 
 * @param wall 
 * @param start_x 
 * @param end_x 
 */
void	sector_walls_raycast(t_app *app, t_thread_data *thread,
	t_raycast_info info)
{
	t_rayhit	hit;
	int			x;

	raycast_init(app, &info, &hit);
	x = info.limit.start - 1;
	while (++x < info.limit.end
		|| (x <= info.limit.end && info.limit.end == WIN_W - 1))
	{
		if (x % THREAD_COUNT != thread->id
			|| info.occlusion_top[x] + info.occlusion_bottom[x] >= WIN_H
			|| !raycast_hit(app, info.wall->line, &hit, x)
			|| hit.distance > (double)MAX_VIEW_DISTANCE)
			continue ;
		if (info.wall->is_portal)
			raycast_portal(app, info.wall, &hit, x);
		else
			raycast_default(app, &hit, x);
		if (!hit.drawn)
			continue ;
		hit.sector->is_visible[thread->id] = TRUE;
		if (hit.sector->parent_sector != -1)
			app->sectors[hit.sector->parent_sector].is_visible[thread->id]
				= TRUE;
	}
}

/**
 * @brief Performs raycast to partially transparent portal wall.
 * 
 * @param app 
 * @param thread 
 * @param info 
 */
void	sector_walls_raycast_transparent(t_app *app, t_thread_data *thread,
	t_raycast_info info)
{
	t_rayhit	hit;
	int			x;

	raycast_init(app, &info, &hit);
	x = info.limit.start - 1;
	while (++x < info.limit.end
		|| (x <= info.limit.end && info.limit.end == WIN_W - 1))
	{
		if (x % THREAD_COUNT != thread->id
			|| info.occlusion_top[x] + info.occlusion_bottom[x] >= WIN_H
			|| !raycast_hit(app, info.wall->line, &hit, x)
			|| hit.distance > (double)MAX_VIEW_DISTANCE)
			continue ;
		draw_wall(app, x, &hit, OCCLUDE_BOTH);
		if (hit.drawn)
			hit.sector->is_visible[thread->id] = TRUE;
	}
}
