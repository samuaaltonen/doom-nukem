/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector_draw_wall.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 00:16:45 by saaltone          #+#    #+#             */
/*   Updated: 2023/02/20 20:30:10 by saaltone         ###   ########.fr       */
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
 * @brief Updates occlusion array values.
 * 
 * @param hit 
 * @param x 
 * @param occlusion 
 * @param y 
 */
static void	update_occlusion(t_rayhit *hit, int x, t_limit y, int occlusion)
{
	if (y.start < y.end)
		hit->drawn = TRUE;
	if (occlusion == OCCLUDE_NONE)
		return ;
	if (occlusion == OCCLUDE_BOTH || occlusion == OCCLUDE_TOP)
		hit->occlusion_top[x] = hit->wall_end;
	if (occlusion == OCCLUDE_BOTH || occlusion == OCCLUDE_BOTTOM)
		hit->occlusion_bottom[x] = WIN_H - hit->wall_start;
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
	*tex_x = (int)(((double)hit->texture + hit->texture_offset) * TEX_SIZE);
	*tex_y = hit->texture_step
		* ((double)(y.start + 1) - hit->wall_start_actual);
	if (*tex_y < 0.0)
		*tex_y += TEX_SIZE * (-*tex_y / TEX_SIZE + 1.0);
}

/**
 * @brief Draws wall pixel to coordinate in window surface.
 * 
 * @param app 
 * @param hit 
 * @param coord 
 * @param color 
 */
static void	draw_wall_pixel(t_app *app, t_rayhit *hit, t_point coord, int color)
{
	t_bool	sky;

	sky = FALSE;
	if ((color & 0xFF000000) > 0)
		put_pixel_to_surface(app->surface, coord.x, coord.y,
			shade_depth(shade_color(color, hit->light), (float)hit->distance));
	else if (app->occlusion_top[coord.x] <= coord.y
		&& app->occlusion_bottom[coord.x] < WIN_H - coord.y)
	{
		put_pixel_to_surface(app->surface, coord.x, coord.y,
			get_sky_pixel(app, coord.x, coord.y));
		sky = TRUE;
	}
	if (coord.y % 2 == 0 && ((color & 0xFF000000) > 0 || sky))
		app->depthmap[coord.y / 2][coord.x] = (float)hit->distance;
}

/**
 * @brief Draws vertical line of a wall.
 * 
 * @param app 
 * @param x 
 * @param hit 
 * @param occlusion_type 
 */
void	draw_wall(t_app *app, int x, t_rayhit *hit, int occlusion_type)
{
	t_limit		y;
	int			tex_x;
	double		tex_y;

	y.start = hit->wall_start;
	y.end = hit->wall_end;
	if (hit->texture == -1 || x < 0 || x >= WIN_W
		|| !apply_occlusion(hit, x, &y))
		return ;
	apply_offsets(hit, y, &tex_x, &tex_y);
	while (y.start < y.end)
	{
		if (tex_y >= (double) TEX_SIZE)
			tex_y = fmod(tex_y, (double) TEX_SIZE);
		if (hit->texture == FULLY_TRANSPARENT_TEXTURE_ID)
			draw_wall_pixel(app, hit, (t_point){x, y.start}, 0);
		else
			draw_wall_pixel(app, hit, (t_point){x, y.start},
				get_pixel_color(app->assets.panels, tex_x, (int) tex_y));
		tex_y += hit->texture_step;
		y.start++;
	}
	if (hit->has_decor)
		draw_wall_decor(app, x, hit);
	update_occlusion(hit, x, y, occlusion_type);
}
