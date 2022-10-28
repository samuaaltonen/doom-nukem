/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector_draw_wall.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 00:16:45 by saaltone          #+#    #+#             */
/*   Updated: 2022/10/28 15:24:09 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * Draws vertical line.
 */
void	draw_wall(t_app *app, int x, t_rayhit *hit, int occlusion)
{
	int		y_start;
	int		y_end;
	double	tex_y;

	if (hit->texture == -1)
		return ;
	y_start = hit->wall_start;
	y_end = hit->wall_end;
	tex_y = hit->texture_offset.y;
	/**
	 * Check occlusion and only draw not occluded parts.
	 */
	if (x < 0 || x >= WIN_W)
		return ;
	if (app->occlusion_top[x] > y_start)
		y_start = app->occlusion_top[x];
	if (app->occlusion_bottom[x] > WIN_H - y_end)
		y_end = WIN_H - app->occlusion_bottom[x];
	if (y_start == y_end || y_start > y_end)
		return;
	if (occlusion == OCCLUDE_BOTH || occlusion == OCCLUDE_TOP)
		app->occlusion_top[x] = y_end;
	if (occlusion == OCCLUDE_BOTH || occlusion == OCCLUDE_BOTTOM)
		app->occlusion_bottom[x] = WIN_H - y_start;
	tex_y += hit->texture_step.y * (y_start - hit->wall_start);
	if (tex_y < 0.0)
		tex_y += TEX_SIZE * (-tex_y / TEX_SIZE + 1);
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
