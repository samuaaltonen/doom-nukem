/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector_draw_floor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 13:23:28 by saaltone          #+#    #+#             */
/*   Updated: 2022/11/04 00:31:44 by saaltone         ###   ########.fr       */
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

	if (x < 0 || x >= WIN_W)
		return ;
	y_start = hit->wall_end;
	y_end = WIN_H - 1;
	if (app->occlusion_top[x] > y_start)
		y_start = app->occlusion_top[x];
	if (app->occlusion_bottom[x] > WIN_H - y_end)
		y_end = WIN_H - app->occlusion_bottom[x];
	if (y_start == y_end || y_start > y_end)
		return;
	app->occlusion_bottom[x] = WIN_H - y_start;
	double	elevation_offset = hit->sector->floor_slope_height / hit->sector->floor_slope_length * hit->distance;
	elevation_offset *= cos(hit->floor_horizon_angle);
		/* - hit->perpendicular_distance * hit->sector->floor_slope_height
		/ hit->sector->floor_slope_length */
	if (hit->sector->floor_slope_height != 0.0) {
		distance = ((app->player.height + app->player.elevation + elevation_offset) - hit->sector->floor_height - hit->floor_slope_height)
				* WIN_H / (y_start - WIN_H / 2 * hit->floor_horizon);
		/* if (x == 10)
		ft_printf("{green}  10{reset}: real distance: %f, distance by horizon: %f, elevation offset: %f, horizon: %f, pos angle: %f, horizon_offset: %f\n",
			hit->distance, distance, elevation_offset, hit->floor_horizon, hit->floor_pos_angle, hit->floor_horizon_height_offset); */
		if (x == 640)
		ft_printf("{cyan} 640{reset}: real distance: %f, distance by horizon: %f, perp: %f, ele: %f, horizon: %f, off: %f, hor angle: %f, slope h: %f, s: %f\n",
			hit->distance, distance, hit->perpendicular_distance, elevation_offset, hit->floor_horizon, hit->floor_horizon_height_offset, hit->floor_horizon_angle, hit->floor_slope_height, hit->sector->floor_slope_height / hit->sector->floor_slope_length);
		/* if (x == 1270)
		ft_printf("{yellow}1270{reset}: real distance: %f, distance by horizon: %f, elevation offset: %f, horizon: %f, pos angle: %f, horizon_offset: %f\n",
			hit->distance, distance, elevation_offset, hit->floor_horizon, hit->floor_pos_angle, hit->floor_horizon_height_offset); */
	}
	while (y_start < y_end)
	{
		if (hit->sector->floor_slope_height != 0.0) {
			distance = ((app->player.height + app->player.elevation + elevation_offset) - hit->sector->floor_height - hit->floor_slope_height)
				* WIN_H / (y_start - WIN_H / 2 * hit->floor_horizon);
		}
		else
			distance = ((app->player.height + app->player.elevation) - hit->sector->floor_height) * WIN_H / (y_start - WIN_H / 2);
		world_pos.x = hit->position.x - (hit->distance - distance) * hit->ray.x;
		world_pos.y = hit->position.y - (hit->distance - distance) * hit->ray.y;
		put_pixel_to_surface(app->surface, x, y_start, get_position_color(
			app, world_pos, hit->sector->floor_texture));
		y_start++;
	}
}
