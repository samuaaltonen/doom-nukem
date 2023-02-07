/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector_draw_wall_decor.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 00:16:45 by saaltone          #+#    #+#             */
/*   Updated: 2023/02/07 17:21:24 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * @brief Applies occlusion and sets y limits accordingly.
 * 
 * @param app 
 * @param x 
 * @param occlusion 
 * @param y 
 * @return t_bool 
 */
static t_bool	apply_occlusion(t_rayhit *hit, int x, t_limit *y)
{
	if (hit->occlusion_top[x] > y->start)
		y->start = hit->occlusion_top[x];
	if (hit->occlusion_bottom[x] > WIN_H - y->end)
		y->end = WIN_H - hit->occlusion_bottom[x];
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
	*tex_x = (int)(hit->decor_texture_offset * TEX_SIZE);
	*tex_y = (double)hit->decor_texture * TEX_SIZE + hit->texture_step
		* ((double)(y.start + 1) - hit->decor_start_actual);
	if (*tex_y < 0.0)
		*tex_y += TEX_SIZE * (-*tex_y / TEX_SIZE + 1);
}

/**
 * @brief Draws vertical line of a wall decoration.
 * 
 * @param app 
 * @param x 
 * @param hit 
 * @param occlusion_type 
 */
void	draw_wall_decor(t_app *app, int x, t_rayhit *hit)
{
	t_limit		y;
	int			tex_x;
	double		tex_y;
	int			color;

	if (hit->decor_texture == -1)
		return ;
	y.start = hit->decor_start;
	y.end = hit->decor_end;
	if (!apply_occlusion(hit, x, &y))
		return ;
	apply_offsets(hit, y, &tex_x, &tex_y);
	while (y.start < y.end)
	{
		tex_y += hit->texture_step;
		if ((int)tex_y < OBJECT_ICON_H)
			color = get_pixel_color(app->assets.object_icon, tex_x,
					(int) tex_y);
		if ((color & 0xFF000000) > 0)
			put_pixel_to_surface(app->surface, x, y.start,
			shade_depth(shade_color(color, hit->light), (float)hit->distance));
		y.start++;
	}
}
