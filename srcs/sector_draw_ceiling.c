/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector_draw_ceiling.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 00:17:22 by saaltone          #+#    #+#             */
/*   Updated: 2023/01/27 21:35:53 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * @brief Returns color of a position on floor/ceiling.
 * 
 * @param app 
 * @param pos 
 * @param texture 
 * @return int 
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
	return (get_pixel_color(app->assets.panels, texture * TEX_SIZE + x, y));
}

/**
 * @brief Initializes vertical drawing limits.
 * 
 * @param app 
 * @param x 
 * @param hit 
 * @param elevation_offset 
 * @return t_limit 
 */
static void	initialize_limits(int x, t_limit *y, t_rayhit *hit)
{
	y->start = 0;
	y->end = hit->wall_start;
	if (hit->occlusion_top[x] > 0)
		y->start = hit->occlusion_top[x];
	if (hit->occlusion_bottom[x] > WIN_H - y->end)
		y->end = WIN_H - hit->occlusion_bottom[x];
}

/**
 * @brief Initializes elevation values for drawing.
 * 
 * @param app 
 * @param hit 
 * @param elevation 
 * @param horizon_effect 
 */
static void	initialize_elevation(t_app *app, t_rayhit *hit, double *elevation,
	double *horizon_effect)
{
	if (hit->sector->ceil_slope_height != 0.0)
	{
		*elevation = hit->sector->ceil_slope_magnitude * hit->distance
			* hit->ceil_horizon_angle + app->player.height
			+ app->player.elevation - hit->sector->ceil_height
			- hit->ceil_slope_height;
		*horizon_effect = WIN_H * app->player.horizon
			- WIN_H * hit->ceil_horizon;
		return ;
	}
	*elevation = app->player.height + app->player.elevation
		- hit->sector->ceil_height;
	*horizon_effect = WIN_H * app->player.horizon;
}

/**
 * @brief Draws ceiling pixel.
 * 
 * @param app 
 * @param hit 
 * @param coord 
 * @param distance 
 */
static void	draw_ceiling_pixel(t_app *app, t_rayhit *hit, t_point coord,
	double distance)
{
	t_vector2	world_pos;
	int			color;

	if (hit->sector->ceil_texture == FULLY_TRANSPARENT_TEXTURE_ID)
		color = 0;
	else
	{
		world_pos.x = hit->position.x - (hit->distance - distance) * hit->ray.x;
		world_pos.y = hit->position.y - (hit->distance - distance) * hit->ray.y;
		color = get_position_color(app, world_pos, hit->sector->ceil_texture);
	}
	if ((color & 0xFF000000) > 0)
		put_pixel_to_surface(app->surface, coord.x, coord.y,
			shade_depth(shade_color(color, hit->light), (float)distance));
	else
		put_pixel_to_surface(app->surface, coord.x, coord.y,
			get_sky_pixel(app, coord.x, coord.y));
	if (coord.y % 2 == 0)
		app->depthmap[coord.y / 2][coord.x] = (float)distance;
}

/**
 * Draws ceililing.
 */
void	draw_ceiling(t_app *app, int x, t_rayhit *hit)
{
	t_limit		y;
	double		distance;
	double		elevation;
	double		horizon_effect;

	if (x < 0 || x >= WIN_W)
		return ;
	initialize_limits(x, &y, hit);
	if (y.start == y.end || y.start > y.end)
		return ;
	initialize_elevation(app, hit, &elevation, &horizon_effect);
	hit->occlusion_top[x] = hit->wall_start;
	distance = elevation * WIN_H / ((double)(y.start + 1) - horizon_effect);
	while (y.start <= y.end)
	{
		distance = elevation * WIN_H / ((double)y.start - horizon_effect);
		draw_ceiling_pixel(app, hit, (t_point){x, y.start}, distance);
		y.start++;
	}
}
