/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector_draw_ceiling.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 00:17:22 by saaltone          #+#    #+#             */
/*   Updated: 2022/11/22 18:27:26 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * Returns color of a position on floor/ceiling.
 * 
 * TODO: angle multiplier
*/
static	int	get_position_color(t_app *app, t_vector2 pos, int texture)
{
	int	x;
	int	y;

	x = (int)(pos.x * (double) TEX_SIZE) % TEX_SIZE;
	if (x < 0)
		x += TEX_SIZE;
	y = (TEX_SIZE - (int)(pos.y * (double) TEX_SIZE)) % TEX_SIZE;
	if (y < 0)
		y += TEX_SIZE;
	return get_pixel_color(app->assets.sprite, texture * TEX_SIZE + x, y);
}

/**
 * Draws ceililing.
 */
void	draw_ceiling(t_app *app, int x, t_rayhit *hit)
{
	t_vector2	world_pos;
	int			y_start;
	int			y_end;
	double		distance;
	double		elevation_offset;

	if (x < 0 || x >= WIN_W)
		return ;
	y_start = 0;
	y_end = hit->wall_start;
	if (app->occlusion_top[x] > 0)
		y_start = app->occlusion_top[x];
	if (app->occlusion_bottom[x] > WIN_H - y_end)
		y_end = WIN_H - app->occlusion_bottom[x];
	if (y_start == y_end || y_start > y_end)
		return;
	app->occlusion_top[x] = hit->wall_start;

	elevation_offset = 0.0;
	if (hit->ceil_slope_height)
		elevation_offset = hit->sector->ceil_slope_magnitude * hit->distance
			* hit->ceil_horizon_angle;

	while (y_end > y_start)
	{
		if (hit->sector->ceil_slope_height != 0.0) {
			distance = ((app->player.height + app->player.elevation + elevation_offset) - hit->sector->ceil_height - hit->ceil_slope_height)
				* WIN_H / (y_end - WIN_H * app->player.horizon + WIN_H * hit->ceil_horizon);
		}
		else
			distance = ((app->player.height + app->player.elevation) - hit->sector->ceil_height) * WIN_H / (y_end - WIN_H * app->player.horizon);
		world_pos.x = hit->position.x - (hit->distance - distance) * hit->ray.x;
		world_pos.y = hit->position.y - (hit->distance - distance) * hit->ray.y;
		put_pixel_to_surface(app->surface, x, y_end, shade_color(get_position_color(
			app, world_pos, hit->sector->ceil_texture), hit->light));
		if (y_end % 2 == app->depthmap_fill_switch)
			app->depthmap[y_end][x] = (float)distance;
		y_end--;
	}
}
