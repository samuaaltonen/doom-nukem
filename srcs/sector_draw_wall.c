/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector_draw_wall.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <danielmdc94@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 00:16:45 by saaltone          #+#    #+#             */
/*   Updated: 2022/10/20 13:09:14 by dpalacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * Draws vertical line.
 */
void	draw_wall(t_app *app, int x, t_rayhit *hit)
{
	int		y_start;
	int		y_end;
	double	tex_y;

	y_start = hit->wall_start;
	y_end = hit->wall_end;
	tex_y = hit->texture_offset.y;
	/**
	 * Check occlusion and only draw not occluded parts.
	 */
	if (x < 0 || x >= WIN_W)
		return ;
	if (app->occlusion_top[x] > y_start)
		y_start = app->occlusion_top[x] + 1;
	if (app->occlusion_bottom[x] > WIN_H - y_end)
		y_end = WIN_H - app->occlusion_bottom[x];
	if (y_start == y_end || y_start > y_end)
		return;
	app->occlusion_top[x] = y_end;
	app->occlusion_bottom[x] = WIN_H - y_start;
	while (y_start < y_end)
	{
		tex_y += hit->texture_step.y;
		if (tex_y >= (double) TEX_SIZE)
			tex_y = fmod(tex_y, (double) TEX_SIZE);
		put_pixel_to_surface(app->surface, x, y_start, get_pixel_color(
			app->assets.sprite, (int)(((double)hit->texture + hit->texture_offset.x) * (double)TEX_SIZE), 
			(int) tex_y));
		y_start++;
	}
}
