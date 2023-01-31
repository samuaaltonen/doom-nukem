/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector_wall_raycast_hit.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 14:06:55 by saaltone          #+#    #+#             */
/*   Updated: 2023/01/31 15:10:38 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * @brief If wall is from member sector, calculate parent positions as well
 * (used in partial wall rendering)
 * 
 * @param app 
 * @param hit 
 * @param relative 
 */
static void	set_parent_vertical_positions(t_app *app, t_rayhit *hit,
	double relative)
{
	t_rayhit	parenthit;
	t_sector	*parent;
	double		ceil_slope;
	double		floor_slope;
	double		wall_start;

	ft_memcpy(&parenthit, hit, sizeof(t_rayhit));
	parent = &app->sectors[hit->sector->parent_sector];
	parenthit.sector = parent;
	ceil_slope = 0.0;
	floor_slope = 0.0;
	if (parent->ceil_slope_magnitude)
		ceil_slope = apply_ceiling_slope(&parenthit);
	if (parent->floor_slope_magnitude)
		floor_slope = apply_floor_slope(&parenthit);
	hit->parent_height = (int)(relative * (parent->ceil_height + ceil_slope
				- parent->floor_height - floor_slope));
	wall_start = WIN_H * app->player.horizon
		+ relative * (app->player.height + app->player.elevation
			- parent->ceil_height - ceil_slope);
	hit->parent_wall_start = (int)wall_start;
	hit->parent_wall_end = hit->parent_wall_start + hit->parent_height;
	hit->parent_wall_start_actual = wall_start;
	clamp_int(&hit->parent_wall_start, 0, WIN_H - 1);
	clamp_int(&hit->parent_wall_end, 0, WIN_H - 1);
}

/**
 * @brief Calculates wall starting and ending positions in window y coordinates
 * depending on hit distance, sector height and also floor/ceiling slopes.
 * Saves actual positions (can be outside of window bounds) and clamped drawing
 * positions.
 * 
 * @param app 
 * @param hit 
 */
void	set_wall_vertical_positions(t_app *app, t_rayhit *hit)
{
	double	relative;
	double	ceil_slope;
	double	floor_slope;
	double	wall_start;

	ceil_slope = apply_ceiling_slope(hit);
	floor_slope = apply_floor_slope(hit);
	relative = WIN_H / hit->distance;
	hit->height = (int)(relative * (hit->sector->ceil_height + ceil_slope
				- hit->sector->floor_height - floor_slope));
	wall_start = WIN_H * app->player.horizon
		+ relative * (app->player.height + app->player.elevation
			- hit->sector->ceil_height - ceil_slope);
	hit->wall_start = (int)wall_start;
	hit->wall_end = (int)wall_start + hit->height;
	hit->texture_step = TEX_SIZE / relative;
	hit->wall_start_actual = wall_start;
	if (ceil_slope)
		hit->wall_start_actual = wall_start + relative * ceil_slope
			- relative * (1.0 + floor(ceil_slope));
	if (hit->sector->parent_sector >= 0)
		set_parent_vertical_positions(app, hit, relative);
	clamp_int(&hit->wall_start, 0, WIN_H - 1);
	clamp_int(&hit->wall_end, 0, WIN_H - 1);
}

/**
 * @brief Checks hit for wall endpoints when wall and ray angle is extremely
 * small to avoid inaccuracy from normal interaction calculation.
 * 
 * @param app 
 * @param wall 
 * @param hit 
 * @param x 
 * @return t_bool 
 */
static t_bool	endpoint_hit(t_app *app, t_line wall, t_rayhit *hit, int x)
{
	(void)app;
	if (x <= 0 || x >= WIN_W - 1)
		return (FALSE);
	if (hit->wall->is_inside
		|| (hit->wall->start_x != x && hit->wall->end_x != x))
		return (FALSE);
	if (hit->wall->start_x == x && hit->wall->x_flipped)
		hit->position = wall.b;
	else if (hit->wall->start_x == x)
		hit->position = wall.a;
	if (hit->wall->end_x == x && hit->wall->x_flipped)
		hit->position = wall.a;
	else if (hit->wall->end_x == x)
		hit->position = wall.b;
	return (TRUE);
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
t_bool	raycast_hit(t_app *app, t_line wall, t_rayhit *hit, int x)
{
	t_line	ray_line;
	float	camera_x;

	ray_line.a = app->player.pos;
	camera_x = 2 * x / (float) WIN_W - 1.0;
	hit->ray = (t_vector2){app->player.dir.x + app->player.cam.x * camera_x,
		app->player.dir.y + app->player.cam.y * camera_x};
	ray_line.b.x = hit->ray.x + app->player.pos.x;
	ray_line.b.y = hit->ray.y + app->player.pos.y;
	if (!endpoint_hit(app, wall, hit, x)
		&& !ft_line_intersection(wall, ray_line, &hit->position))
		return (FALSE);
	hit->distance = ft_vector_length((t_vector2){
			hit->position.x - app->player.pos.x,
			hit->position.y - app->player.pos.y});
	if (hit->distance < SMALL_DISTANCE_EPSILON)
		hit->distance = SMALL_DISTANCE_EPSILON;
	hit->texture_offset = ft_vector_length((t_vector2){
			wall.a.x - hit->position.x, wall.a.y - hit->position.y});
	hit->texture_offset -= floor(hit->texture_offset);
	hit->distortion = cos(ft_vector_angle(hit->ray, app->player.dir));
	hit->distance = hit->distortion * hit->distance;
	set_wall_vertical_positions(app, hit);
	hit->has_decor = raycast_decor(app, wall, hit);
	return (TRUE);
}
