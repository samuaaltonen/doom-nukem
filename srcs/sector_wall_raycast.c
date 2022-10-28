/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector_wall_raycast.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 13:12:51 by saaltone          #+#    #+#             */
/*   Updated: 2022/10/28 15:07:00 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * If wall is a portal, calculate parent positions as well (used in partial
 * wall rendering)
*/
static void	calculate_parent_positions(t_app *app, t_rayhit *hit,
	double relative_height)
{
	t_sector	*parent;

	parent = &app->sectors[hit->sector->parent_sector];
	hit->parent_height = (int)(relative_height
		* (parent->ceiling_height - parent->floor_height));
	hit->parent_wall_start = WIN_H / 2 - hit->parent_height
		+ (int)(relative_height * ((app->player.height + app->player.elevation) - parent->floor_height));
	hit->parent_wall_end = hit->parent_wall_start + hit->parent_height;
	if (hit->parent_wall_start < 0)
	{
		hit->parent_texture_offset_top += -hit->parent_wall_start * hit->texture_step.y;
		hit->parent_wall_start = 0;
	}
	if (hit->parent_wall_start >= WIN_H)
		hit->parent_wall_start = WIN_H - 1;
	if (hit->wall_end < 0)
		hit->parent_texture_offset_bottom += -hit->wall_end * hit->texture_step.y;
	if (hit->parent_wall_end < 0)
	{
		hit->parent_texture_offset_bottom = -hit->parent_wall_end * hit->texture_step.y;
		hit->parent_wall_end = 0;
	}
	if (hit->parent_wall_end >= WIN_H)
		hit->parent_wall_end = WIN_H - 1;
}

static double	apply_ceiling_slope(t_rayhit *hit)
{
	double		relation;
	double		perpendicular_distance;
	double		pos_angle;
	t_vector2	slope_start_to_hit;

	relation = hit->sector->ceiling_slope_height
		/ hit->sector->ceiling_slope_length;
	slope_start_to_hit = ft_vector2_sub(hit->position,
			hit->sector->ceiling_slope_start);
	pos_angle = ft_vector_angle(slope_start_to_hit,
		ft_vector2_sub(hit->sector->ceiling_slope_end,
			hit->sector->ceiling_slope_start));
	perpendicular_distance = cos(pos_angle) * ft_vector_length(ft_vector2_sub(
		hit->position,
		hit->sector->ceiling_slope_start));
	return (perpendicular_distance * relation);
}

static double	apply_floor_slope(t_rayhit *hit)
{
	double		relation;
	double		perpendicular_distance;
	double		pos_angle;
	t_vector2	slope_start_to_hit;

	relation = hit->sector->floor_slope_height
		/ hit->sector->floor_slope_length;
	slope_start_to_hit = ft_vector2_sub(hit->position,
			hit->sector->floor_slope_start);
	pos_angle = ft_vector_angle(slope_start_to_hit,
		ft_vector2_sub(hit->sector->floor_slope_end,
			hit->sector->floor_slope_start));
	perpendicular_distance = cos(pos_angle) * ft_vector_length(ft_vector2_sub(
		hit->position,
		hit->sector->floor_slope_start));
	return (perpendicular_distance * relation);
}

/**
 * Calculates wall starting and ending positions in window y coordinates.
*/
void	set_wall_vertical_positions(t_app *app, t_rayhit *hit)
{
	double		relative_height;
	double		ceiling_slope;
	double		floor_slope;

	ceiling_slope = 0.0;
	floor_slope = 0.0;
	if (hit->sector->ceiling_slope_height)
		ceiling_slope = apply_ceiling_slope(hit);
	if (hit->sector->floor_slope_height)
		floor_slope = apply_floor_slope(hit);
	relative_height = WIN_H / hit->distance;
	hit->height = (int)(relative_height
			* (hit->sector->ceiling_height + ceiling_slope - hit->sector->floor_height - floor_slope));
	hit->wall_start = WIN_H / 2 - hit->height + (int)(relative_height
			* ((app->player.height + app->player.elevation) - hit->sector->floor_height - floor_slope));
	hit->wall_end = hit->wall_start + hit->height;
	hit->texture_step.y = TEX_SIZE / relative_height;
	hit->texture_offset.y = 0;
	if (hit->sector->parent_sector >= 0)
	{
		hit->parent_texture_offset_top = 0;
		hit->parent_texture_offset_bottom = fabs((double)TEX_SIZE - relative_height * floor_slope * hit->texture_step.y);
		calculate_parent_positions(app, hit, relative_height);
	}
	if (hit->wall_start < 0)
	{
		hit->texture_offset.y -= hit->wall_start * hit->texture_step.y;
		hit->wall_start = 0;
	}
	if (hit->wall_end < 0)
	{
		hit->texture_offset.y -= hit->wall_end * hit->texture_step.y;
		hit->wall_end = 0;
	}
	if (hit->wall_start >= WIN_H)
		hit->wall_start = WIN_H - 1;
	if (hit->wall_end >= WIN_H)
		hit->wall_end = WIN_H - 1;
}

/**
 * Performs raycast from player to wall. Updates values into rayhit struct to be
 * used later in rendering.
 * Returns TRUE if there was a hit and FALSE otherwise.
*/
static t_bool	raycast_hit(t_app *app, t_line wall, t_rayhit *hit, int x)
{
	t_line	ray_line;
	double	camera_x;
	double	angle;

	ray_line.a = app->player.pos;
	camera_x = 2 * x / (double) WIN_W - 1.f;
	hit->ray = (t_vector2){
		app->player.dir.x + app->player.cam.x * camera_x, 
		app->player.dir.y + app->player.cam.y * camera_x};
	ray_line.b = ft_vector_resize(hit->ray, MAX_VIEW_DISTANCE);
	angle = ft_vector_angle(ray_line.b, app->player.dir);
	ray_line.b.x += app->player.pos.x;
	ray_line.b.y += app->player.pos.y;
	if (!ft_line_intersection(wall, ray_line, &hit->position))
		return (FALSE);
	hit->distance = ft_vector_length((t_vector2){
		hit->position.x - app->player.pos.x,
		hit->position.y - app->player.pos.y});
	hit->texture_offset.x = fmod(ft_vector_length((t_vector2){
		wall.a.x - hit->position.x,
		wall.a.y - hit->position.y}), 1.0);
	hit->distortion = cos(angle);
	hit->distance = hit->distortion * hit->distance;
	set_wall_vertical_positions(app, hit);
	return (TRUE);
}

/**
 * Draws individual sector wall, possible ceiling and floor of that vertical
 * screenline. Also updates occlusion arrays accordingly.
 */
void	sector_walls_raycast(t_app *app, t_thread_data *thread, t_wall *wall, int start_x, int end_x)
{
	t_rayhit	hit;
	int			x;

	hit.sector = &app->sectors[wall->sector_id];
	hit.wall_type = wall->wall_type;
	hit.texture = app->sectors[wall->sector_id].wall_textures[wall->wall_id];
	x = start_x - 1;
	while (++x < end_x)
	{
		if (x % THREAD_COUNT != thread->id)
			continue ;
		/**
		 * Perform rayhit. Skips when there is no hit.
		*/
		if (!raycast_hit(app, wall->line, &hit, x))
			continue ;
		// If portal or member (member sectors automatically portals)
		if (wall->is_portal)
		{
			if (wall->is_inside && !wall->is_member)
				draw_portal_partial(app, x, &hit);
			if (!wall->is_inside)
				draw_portal_partial_parent(app, x, &hit);
			if (wall->is_inside && wall->is_member)
			{
				draw_ceiling(app, x, &hit);
				draw_floor(app, x, &hit);
				draw_portal_partial_hole(app, x, &hit);
			}
			continue ;
		}
		// IF wall type normal wall:
		draw_ceiling(app, x, &hit);
		draw_floor(app, x, &hit);
		draw_wall(app, x, &hit, OCCLUDE_BOTH);
	}
}
