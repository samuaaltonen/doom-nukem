/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector_wall_raycast.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 13:12:51 by saaltone          #+#    #+#             */
/*   Updated: 2022/11/17 15:08:19 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * @brief Calculates height offset for current rayhit based on sector ceiling
 * slope
 * 
 * @param hit 
 * @return double 
 */
static double	apply_ceiling_slope(t_rayhit *hit)
{
	double		perpendicular_distance;
	double		pos_angle;
	t_vector2	slope_vector;

	slope_vector = ft_vector2_sub(hit->sector->ceil_slope_end,
			hit->sector->ceil_slope_start);
	pos_angle = ft_vector_angle(ft_vector2_sub(hit->position,
			hit->sector->ceil_slope_start), slope_vector);
	perpendicular_distance = cos(pos_angle) * ft_vector_length(ft_vector2_sub(
		hit->position, hit->sector->ceil_slope_start));
	hit->ceil_horizon_angle = cos(ft_vector_angle(hit->ray, slope_vector)) / hit->distortion;
	hit->ceil_horizon = hit->sector->ceil_slope_magnitude * hit->ceil_horizon_angle;
	hit->ceil_slope_height = perpendicular_distance * hit->sector->ceil_slope_magnitude;
	return (perpendicular_distance * hit->sector->ceil_slope_magnitude);
}

/**
 * @brief Calculates height offset for current rayhit based on sector floor
 * slope
 * 
 * @param hit 
 * @return double 
 */
static double	apply_floor_slope(t_rayhit *hit)
{
	double		perpendicular_distance;
	double		pos_angle;
	t_vector2	slope_vector;

	slope_vector = ft_vector2_sub(hit->sector->floor_slope_end,
			hit->sector->floor_slope_start);
	pos_angle = ft_vector_angle(ft_vector2_sub(hit->position,
			hit->sector->floor_slope_start), slope_vector);
	perpendicular_distance = cos(pos_angle) * ft_vector_length(ft_vector2_sub(
		hit->position, hit->sector->floor_slope_start));
	hit->floor_horizon_angle = cos(ft_vector_angle(hit->ray, slope_vector)) / hit->distortion;
	hit->floor_horizon = hit->sector->floor_slope_magnitude * hit->floor_horizon_angle;
	hit->floor_slope_height = perpendicular_distance * hit->sector->floor_slope_magnitude;
	return (perpendicular_distance * hit->sector->floor_slope_magnitude);
}

/**
 * @brief If wall is a portal, calculate parent positions as well (used in
 * partial wall rendering)
 * 
 * @param app 
 * @param hit 
 * @param relative_height 
 */
static void	calculate_parent_positions(t_app *app, t_rayhit *hit,
	double relative_height)
{
	t_rayhit	parenthit;

	t_sector	*parent;
	double		ceil_slope;
	double		floor_slope;

	ft_memcpy(&parenthit, hit, sizeof(t_rayhit));
	parent = &app->sectors[hit->sector->parent_sector];
	parenthit.sector = parent;

	ceil_slope = 0.0;
	floor_slope = 0.0;
	if (parent->ceil_slope_height)
		ceil_slope = apply_ceiling_slope(&parenthit);
	if (parent->floor_slope_height)
		floor_slope = apply_floor_slope(&parenthit);

	hit->parent_height = (int)(relative_height
		* (parent->ceil_height + ceil_slope - parent->floor_height - floor_slope));
	hit->parent_wall_start = WIN_H * app->player.horizon - hit->parent_height
		+ (int)(relative_height * ((app->player.height + app->player.elevation) - parent->floor_height - floor_slope));
	hit->parent_wall_end = hit->parent_wall_start + hit->parent_height;
	hit->parent_wall_start_actual = hit->parent_wall_start;
	if (hit->parent_wall_start < 0)
		hit->parent_wall_start = 0;
	if (hit->parent_wall_start >= WIN_H)
		hit->parent_wall_start = WIN_H - 1;
	if (hit->parent_wall_end < 0)
		hit->parent_wall_end = 0;
	if (hit->parent_wall_end >= WIN_H)
		hit->parent_wall_end = WIN_H - 1;
}

/**
 * @brief Calculates wall starting and ending positions in window y coordinates.
 * 
 * @param app 
 * @param hit 
 */
void	set_wall_vertical_positions(t_app *app, t_rayhit *hit)
{
	double		relative_height;
	double		ceil_slope;
	double		floor_slope;

	ceil_slope = 0.0;
	floor_slope = 0.0;
	if (hit->sector->ceil_slope_height)
		ceil_slope = apply_ceiling_slope(hit);
	if (hit->sector->floor_slope_height)
		floor_slope = apply_floor_slope(hit);
	relative_height = WIN_H / hit->distance;
	hit->height = (int)(relative_height
			* (hit->sector->ceil_height + ceil_slope - hit->sector->floor_height - floor_slope));
	hit->wall_start = WIN_H * app->player.horizon - hit->height + (int)(relative_height
			* ((app->player.height + app->player.elevation) - hit->sector->floor_height - floor_slope));
	hit->wall_start_actual = hit->wall_start;
	hit->wall_end = hit->wall_start + hit->height;
	hit->texture_step.y = TEX_SIZE / relative_height;
	hit->texture_offset.y = 0;

	if (ceil_slope)
		hit->wall_start_actual += relative_height * ceil_slope - relative_height * (1 + (int)ceil_slope);

	if (hit->sector->parent_sector >= 0)
		calculate_parent_positions(app, hit, relative_height);
	if (hit->wall_start < 0)
		hit->wall_start = 0;
	if (hit->wall_end < 0)
		hit->wall_end = 0;
	if (hit->wall_start >= WIN_H)
		hit->wall_start = WIN_H - 1;
	if (hit->wall_end >= WIN_H)
		hit->wall_end = WIN_H - 1;
}

/**
 * @brief Performs raycast from player to wall. Updates values into rayhit
 * struct to be used later in rendering. Returns TRUE if there was a hit and
 * FALSE otherwise.
 * 
 * @param app 
 * @param wall 
 * @param hit 
 * @param x 
 * @return t_bool 
 */
static t_bool	raycast_hit(t_app *app, t_line wall, t_rayhit *hit, int x)
{
	t_line	ray_line;
	double	camera_x;

	ray_line.a = app->player.pos;
	camera_x = 2 * x / (double) WIN_W - 1.f;
	hit->ray = (t_vector2){
		app->player.dir.x + app->player.cam.x * camera_x,
		app->player.dir.y + app->player.cam.y * camera_x};
	ray_line.b.x = hit->ray.x + app->player.pos.x;
	ray_line.b.y = hit->ray.y + app->player.pos.y;
	if (!ft_line_intersection(wall, ray_line, &hit->position))
		return (FALSE);
	hit->distance = ft_vector_length((t_vector2){
		hit->position.x - app->player.pos.x,
		hit->position.y - app->player.pos.y});
	hit->texture_offset.x = ft_vector_length((t_vector2){
		wall.a.x - hit->position.x,
		wall.a.y - hit->position.y});
	hit->texture_offset.x = hit->texture_offset.x
		- (double)(int)hit->texture_offset.x;
	hit->distortion = cos(ft_vector_angle(hit->ray, app->player.dir));
	hit->distance = hit->distortion * hit->distance;
	set_wall_vertical_positions(app, hit);
	return (TRUE);
}

/**
 * @brief Draws individual sector wall, possible ceiling and floor of that
 * vertical screenline. Also updates occlusion arrays accordingly.
 * 
 * @param app 
 * @param thread 
 * @param wall 
 * @param start_x 
 * @param end_x 
 */
void	sector_walls_raycast(t_app *app, t_thread_data *thread, t_wall *wall,
	t_limit limit)
{
	t_rayhit	hit;
	int			x;

	hit.floor_slope_height = 0.0;
	hit.ceil_slope_height = 0.0;
	hit.sector = &app->sectors[wall->sector_id];
	hit.wall_type = wall->wall_type;
	hit.texture = app->sectors[wall->sector_id].wall_textures[wall->wall_id];
	hit.light = hit.sector->light;
	x = limit.start - 1;
	while (++x < limit.end)
	{
		if (x % THREAD_COUNT != thread->id
			|| wall->start_x > x || wall->end_x < x
			|| app->occlusion_top[x] + app->occlusion_bottom[x] >= WIN_H
			|| !raycast_hit(app, wall->line, &hit, x))
			continue ;
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
		draw_ceiling(app, x, &hit);
		draw_floor(app, x, &hit);
		draw_wall(app, x, &hit, OCCLUDE_BOTH);
	}
}
