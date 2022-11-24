/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector_draw_sky.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 14:53:03 by saaltone          #+#    #+#             */
/*   Updated: 2022/11/24 15:58:56 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

static void	draw_sky(t_app *app, int x)
{
	int			y;
	t_vector2	texture_pos;

	y = app->occlusion_top[x];
	texture_pos.x = (x + app->sky.start.x) * app->sky.pixel_step.x;
	texture_pos.y = (y - app->sky.start.y) * app->sky.pixel_step.y;
	if (texture_pos.x < 0.0)
		texture_pos.x += app->sky.size.x * app->sky.pixel_step.x;
	if (texture_pos.x >= (double)SKYBOX_W)
		texture_pos.x = fmod(texture_pos.x, (double)SKYBOX_W);
	if (texture_pos.y < 0.0)
		texture_pos.y += app->sky.size.y * app->sky.pixel_step.y;
	while (++y < WIN_H - app->occlusion_bottom[x] - 1)
	{
		texture_pos.y += app->sky.pixel_step.y;
		if (texture_pos.y >= (double)SKYBOX_H)
			texture_pos.y = fmod(texture_pos.y, (double)SKYBOX_H);
		if (app->depthmap[y][x] == MAX_VIEW_DISTANCE)
			put_pixel_to_surface(app->surface, x, y, get_pixel_color(
				app->assets.bg, (int)texture_pos.x, (int)texture_pos.y));
	}
}

/**
 * @brief Get the sky pixel color.
 * 
 * @param app 
 * @param x 
 * @param y 
 * @return int 
 */
int	get_sky_pixel(t_app *app, int x, int y)
{
	t_vector2	texture_pos;

	texture_pos.x = (x + app->sky.start.x) * app->sky.pixel_step.x;
	texture_pos.y = (y - app->sky.start.y) * app->sky.pixel_step.y;
	if (texture_pos.x < 0.0)
		texture_pos.x += app->sky.size.x * app->sky.pixel_step.x;
	if (texture_pos.x >= (double)SKYBOX_W)
		texture_pos.x = fmod(texture_pos.x, (double)SKYBOX_W);
	if (texture_pos.y < 0.0)
		texture_pos.y += app->sky.size.y * app->sky.pixel_step.y;
	return (get_pixel_color(app->assets.bg, (int)texture_pos.x, (int)texture_pos.y));
}

/**
 * @brief Renders skybox for areas that were not occluded by walls or
 * floors/ceilings.
 * 
 * @param app 
 * @param thread 
 */
void	sector_sky_render(t_app *app, t_thread_data *thread)
{
	int	x;

	x = 0;
	while (++x < WIN_W - 1)
	{
		if (x % THREAD_COUNT != thread->id
			|| app->occlusion_top[x] + app->occlusion_bottom[x] >= WIN_H)
			continue ;
		draw_sky(app, x);
	}
}
