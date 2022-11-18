/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector_draw_sky.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 14:53:03 by saaltone          #+#    #+#             */
/*   Updated: 2022/11/18 17:03:34 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

static void	draw_sky(t_app *app, int x)
{
	int						y;
	t_vector2				texture_pos;
	static const t_vector2	pixel_step = (t_vector2){
		(double)SKYBOX_W / (double)SKYBOX_ZOOM / (double)WIN_W,
		(double)SKYBOX_H / (double)SKYBOX_ZOOM / (double)WIN_H};

	y = app->occlusion_top[x] + 1;
	texture_pos.x = x * pixel_step.x;
	texture_pos.y = (double)SKYBOX_H * (1 - app->player.horizon)
		+ y * pixel_step.y;
	if (texture_pos.y < 0.0)
		texture_pos.y = 0;
	while (y < WIN_H - app->occlusion_bottom[x] - 1)
	{
		texture_pos.y += pixel_step.y;
		if (texture_pos.y > (double)SKYBOX_H)
			break ;
		put_pixel_to_surface(app->surface, x, y, get_pixel_color(
				app->assets.bg, (int)texture_pos.x, (int)texture_pos.y));
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
