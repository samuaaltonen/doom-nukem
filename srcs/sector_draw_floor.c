/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector_draw_floor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 13:23:28 by saaltone          #+#    #+#             */
/*   Updated: 2022/12/02 13:45:20 by htahvana         ###   ########.fr       */
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
 * Draws floor.
 */
void	draw_floor(t_app *app, int x, t_rayhit *hit)
{
	t_vector2	world_pos;
	int			y_start;
	int			y_end;
	double		distance;
	double		elevation_offset;
	int			color;

	if (x < 0 || x >= WIN_W)
		return ;
	y_start = hit->wall_end;
	y_end = WIN_H - 1;
	if (hit->occlusion_top[x] > y_start)
		y_start = hit->occlusion_top[x];
	if (hit->occlusion_bottom[x] > WIN_H - y_end)
		y_end = WIN_H - hit->occlusion_bottom[x];
	if (y_start == y_end || y_start > y_end)
		return;
	hit->occlusion_bottom[x] = WIN_H - y_start;

	elevation_offset = 0.0;
	if (hit->floor_slope_height)
		elevation_offset = hit->sector->floor_slope_magnitude * hit->distance
			* hit->floor_horizon_angle;

	while (y_start < y_end)
	{
		if (hit->sector->floor_slope_height != 0.0) {
			distance = ((app->player.height + app->player.elevation + elevation_offset) - hit->sector->floor_height - hit->floor_slope_height)
				* WIN_H / (y_start - WIN_H * app->player.horizon + WIN_H * hit->floor_horizon);
		}
		else
			distance = ((app->player.height + app->player.elevation) - hit->sector->floor_height) * WIN_H / (y_start - WIN_H * app->player.horizon);
		world_pos.x = hit->position.x - (hit->distance - distance) * hit->ray.x;
		world_pos.y = hit->position.y - (hit->distance - distance) * hit->ray.y;
		color = get_position_color(app, world_pos, hit->sector->floor_texture);
		if ((color & 0xFF000000) > 0)
			put_pixel_to_surface(app->surface, x, y_start, shade_color(color, hit->light));
		else
			put_pixel_to_surface(app->surface, x, y_start, get_sky_pixel(app, x, y_start));
		if (y_start % 2 == 0)
			app->depthmap[y_start / 2][x] = (float)distance;
		y_start++;
	}
}
