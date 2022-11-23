/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector_draw_transparent.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 15:47:41 by saaltone          #+#    #+#             */
/*   Updated: 2022/11/23 17:18:02 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * @brief Applies occlusion and sets y limits accordingly. Also updates new
 * occlusion values.
 * 
 * @param app 
 * @param x 
 * @param occlusion 
 * @param y 
 * @return t_bool 
 */
static t_bool	apply_occlusion(t_app *app, int x, t_limit *y)
{
	if (app->occlusion_top[x] > y->start)
		y->start = app->occlusion_top[x];
	if (app->occlusion_bottom[x] > WIN_H - y->end)
		y->end = WIN_H - app->occlusion_bottom[x];
	if (y->start == y->end || y->start > y->end)
		return (FALSE);
	return (TRUE);
}

/**
 * @brief Applies offsets for texture coordinate.
 * 
 * @param hit 
 * @param y 
 * @param tex_x 
 * @param tex_y 
 */
static void	apply_offsets(t_rayhit *hit, t_limit y, int *tex_x, double *tex_y)
{
	*tex_x = (int)(((double)hit->texture + hit->texture_offset.x) * TEX_SIZE);
	*tex_y += hit->texture_step.y * (y.start - hit->wall_start_actual);
	if (*tex_y < 0.0)
		*tex_y += TEX_SIZE * (-*tex_y / TEX_SIZE + 1);
}

/**
 * @brief Draws vertical line of a wall.
 * 
 * @param app 
 * @param x 
 * @param hit 
 * @param occlusion_type 
 */
void	draw_transparent_wall(t_app *app, int x, t_rayhit *hit)
{
	t_limit		y;
	int			tex_x;
	double		tex_y;
	float		depth;
	int			color;

	if (hit->texture == -1 || x < 0 || x >= WIN_W)
		return ;
	y.start = hit->wall_start;
	y.end = hit->wall_end;
	tex_y = hit->texture_offset.y;
	if (!apply_occlusion(app, x, &y))
		return ;
	apply_offsets(hit, y, &tex_x, &tex_y);
	depth = (float)hit->distance;
	while (y.start < y.end)
	{
		tex_y += hit->texture_step.y;
		if (tex_y >= (double) TEX_SIZE)
			tex_y = fmod(tex_y, (double) TEX_SIZE);
		color = get_pixel_color(app->assets.sprite, tex_x, (int) tex_y);
		if ((color & 0xFF000000) > 0 && app->overwrite_buffer_count < MAX_OVERWRITE_PIXELS)
		{
			app->overwrite_buffer[app->overwrite_buffer_count] = (t_buffer_unit){
				x, y.start, shade_color(color, hit->light), depth
			};
			app->overwrite_buffer_count++;
		}
		y.start++;
	}
}
