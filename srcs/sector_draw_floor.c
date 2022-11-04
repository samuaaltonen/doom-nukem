/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector_draw_floor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 13:23:28 by saaltone          #+#    #+#             */
/*   Updated: 2022/11/04 12:07:41 by saaltone         ###   ########.fr       */
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

	/* double	alpha = atan(hit->sector->floor_slope_magnitude); */

	double	elevation_offset = hit->sector->floor_slope_magnitude * hit->distance;
	elevation_offset *= cos(hit->floor_horizon_angle);

	/* double	warped_elevation = (elevation_offset / cos(alpha)) / tan(M_PI - alpha); */

	/* hit->floor_horizon = 1.0;
	elevation_offset = 0.0; */
		/* - hit->perpendicular_distance * hit->sector->floor_slope_height
		/ hit->sector->floor_slope_length */
	if (hit->sector->floor_slope_height != 0.0) {
		distance = ((app->player.height + app->player.elevation + elevation_offset) - hit->sector->floor_height - hit->floor_slope_height)
				* WIN_H / (y_start - WIN_H / 2 * hit->floor_horizon);
		if (x == 10)
		{
			/* ft_printf("{purple}warped elevation at 10: %f{reset}\n", warped_elevation); */
			ft_printf("{green}  10{reset}: distance error: {green}%f{reset}, real distance: %f, distance by horizon: %f, ele: %f, horizon: %f, hor angle: %f, slope h: %f, s: %f\n",
				hit->distance - distance, hit->distance, distance, elevation_offset, hit->floor_horizon, hit->floor_horizon_angle, hit->floor_slope_height, hit->sector->floor_slope_magnitude);
		}
		if (x == 640)
			ft_printf("{cyan} 640{reset}: distance error: {cyan}%f{reset}, real distance: %f, distance by horizon: %f, ele: %f, horizon: %f, hor angle: %f, slope h: %f, s: %f\n",
				hit->distance - distance, hit->distance, distance, elevation_offset, hit->floor_horizon, hit->floor_horizon_angle, hit->floor_slope_height, hit->sector->floor_slope_magnitude);
		if (x == 1270)
			ft_printf("{yellow}1270{reset}: distance error: {yellow}%f{reset}, real distance: %f, distance by horizon: %f, ele: %f, horizon: %f, hor angle: %f, slope h: %f, s: %f\n",
				hit->distance - distance, hit->distance, distance, elevation_offset, hit->floor_horizon, hit->floor_horizon_angle, hit->floor_slope_height, hit->sector->floor_slope_magnitude);
	}
	while (y_start < y_end)
	{
		if (hit->sector->floor_slope_height != 0.0) {
			distance = ((app->player.height + app->player.elevation + elevation_offset) - hit->sector->floor_height - hit->floor_slope_height)
				* WIN_H / (y_start - WIN_H / 2 * hit->floor_horizon);
			if (y_start == WIN_H - 2)
			{
				if (x == 10)
					ft_printf("{green}  10{reset}: bottom distance: %f\n",
						distance);
				if (x == 640)
					ft_printf("{cyan} 640{reset}: bottom distance: %f\n",
						distance);
				if (x == 1270)
					ft_printf("{yellow}1270{reset}: bottom distance: %f\n",
						distance);
			}
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
