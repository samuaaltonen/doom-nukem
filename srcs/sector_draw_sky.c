/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector_draw_sky.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 14:53:03 by saaltone          #+#    #+#             */
/*   Updated: 2022/11/21 17:40:26 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

static void	draw_sky(t_app *app, int x)
{
	int			y;
	t_vector2	texture_pos;

	y = app->occlusion_top[x] + 1;
	texture_pos.x = x * app->sky.pixel_step.x;
	texture_pos.y = (y - app->sky.start.y) * app->sky.pixel_step.y;
	if (texture_pos.y < 0.0)
		texture_pos.y = 0;
	while (y < WIN_H - app->occlusion_bottom[x] - 1)
	{
		texture_pos.y += app->sky.pixel_step.y;
		if (texture_pos.y > (double)SKYBOX_H)
			texture_pos.y = fmod(texture_pos.y, (double)SKYBOX_H);
		put_pixel_to_surface(app->surface, x, y, get_pixel_color(
				app->assets.bg, (int)texture_pos.x, (int)texture_pos.y));
		if (y % 2)
			app->depthmap[y][x] = MAX_VIEW_DISTANCE;
		y++;
	}
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