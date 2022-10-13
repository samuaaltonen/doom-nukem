/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector_wall_draw.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 13:12:51 by saaltone          #+#    #+#             */
/*   Updated: 2022/10/13 23:16:27 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * Draws ceiling.
 */
static void	draw_ceiling(t_app *app, int x, int y_start, int y_end)
{
	/**
	 * Check TOP occlusion and only draw not occluded parts.
	 */
	if (x < 0 || x >= WIN_W)
		return ;
	if (app->occlusion_top[x] > y_start)
		y_start = app->occlusion_top[x] + 1;
	if (y_start == y_end || y_start > y_end)
		return;
	app->occlusion_top[x] = y_end;
	/**
	 * TODO: TEXTURES
	 * Draw vertical line
	 */
	while (y_start < y_end)
	{
		put_pixel_to_surface(app->surface, x, y_start, 0x333333);
		y_start++;
	}
}

/**
 * Draws floor.
 */
static void	draw_floor(t_app *app, int x, int y_start, int y_end)
{
	/**
	 * Check BOTTOM occlusion and only draw not occluded parts.
	 */
	if (x < 0 || x >= WIN_W)
		return ;
	if (app->occlusion_bottom[x] > WIN_H - y_end)
		y_end = WIN_H - app->occlusion_bottom[x];
	if (y_start == y_end || y_start > y_end)
		return;
	app->occlusion_bottom[x] = WIN_H - y_start;
	/**
	 * TODO: TEXTURES
	 * Draw vertical line
	 */
	while (y_start < y_end)
	{
		put_pixel_to_surface(app->surface, x, y_start, 0xcccccc);
		y_start++;
	}
}

/**
 * Draws vertical line.
 */
static void	draw_wall(t_app *app, int x, t_rayhit *hit)
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
			app->sprite, (int)(((double)hit->texture + hit->texture_offset.x) * (double)TEX_SIZE), 
			(int) tex_y));
		y_start++;
	}
}

/**
 * Calculates wall starting and ending positions in window y coordinates.
*/
static void	calculate_vertical_positions(t_app *app, t_rayhit *hit)
{
	double	relative_height;

	relative_height = WIN_H / hit->distance;
	hit->height = (int)(relative_height
			* (hit->sector->ceiling_height - hit->sector->floor_height));
	hit->wall_start = WIN_H / 2 - hit->height + (int)(relative_height
			* (app->player.height - hit->sector->floor_height));
	hit->wall_end = hit->wall_start + hit->height;
	hit->texture_step.y = TEX_SIZE / relative_height;
	hit->texture_offset.y = 0;
	if (hit->wall_start < 0)
	{
		hit->texture_offset.y = -hit->wall_start * hit->texture_step.y;
		hit->wall_start = 0;
	}
	if (hit->wall_end > WIN_H)
		hit->wall_end = WIN_H - 1;
}

/**
 * Performs raycast from player to wall. Updates values into rayhit struct to be
 * used later in rendering.
 * Returns TRUE if there was a hit and FALSE otherwise.
*/
static t_bool	wall_raycast(t_app *app, t_vertex2 wall, t_rayhit *hit, int x)
{
	t_vertex2	ray_vertex;
	double		camera_x;
	double		angle;

	ray_vertex.a = app->player.pos;
	camera_x = 2 * x / (double) WIN_W - 1.f;
	ray_vertex.b = ft_vector_resize((t_vector2){
		app->player.dir.x + app->player.cam.x * camera_x, 
		app->player.dir.y + app->player.cam.y * camera_x},
		MAX_VIEW_DISTANCE);
	angle = ft_vector_angle(ray_vertex.b, app->player.dir);
	ray_vertex.b.x += app->player.pos.x;
	ray_vertex.b.y += app->player.pos.y;
	if (!ft_vertex_intersection(wall, ray_vertex, &hit->position))
		return (FALSE);
	hit->distance = ft_vector_length((t_vector2){
		hit->position.x - app->player.pos.x,
		hit->position.y - app->player.pos.y});
	hit->texture_offset.x = fmod(ft_vector_length((t_vector2){
		wall.a.x - hit->position.x,
		wall.a.y - hit->position.y}), 1.0);
	hit->distance = distortion_correction(angle, hit->distance);
	calculate_vertical_positions(app, hit);
	return (TRUE);
}

/**
 * Draws individual sector wall, possible ceiling and floor of that vertical
 * screenline. Also updates occlusion arrays accordingly.
 */
void	sector_wall_draw(t_app *app, t_wall *wall)
{
	t_rayhit	hit;
	int			x;

	hit.sector = &test_sectors[wall->sector_id];
	hit.texture = test_sectors[wall->sector_id].wall_textures[wall->wall_id];
	x = wall->start_x;
	while (++x < wall->end_x)
	{
		/**
		 * Perform rayhit. Skips when there is no hit.
		*/
		if (!wall_raycast(app, wall->vertex, &hit, x))
			continue ;
		// IF wall type normal wall:
		if (hit.sector->wall_types[wall->wall_id] == -1)
		{
			draw_ceiling(app, x, 0, hit.wall_start);
			draw_floor(app, x, hit.wall_end, WIN_H - 1);
			draw_wall(app, x, &hit);
		}
		// IF portal / member
		// Draw ceiling
		// Draw floor
		// If floor higher or ceiling smaller of next sector, draw partial wall
	}
}