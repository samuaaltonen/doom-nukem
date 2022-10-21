/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector_wall_raycast.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 13:12:51 by saaltone          #+#    #+#             */
/*   Updated: 2022/10/21 13:21:37 by saaltone         ###   ########.fr       */
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
		+ (int)(relative_height * (app->player.height - parent->floor_height));
	hit->parent_wall_end = hit->parent_wall_start + hit->parent_height;
	hit->parent_texture_offset_top = 0;
	hit->parent_texture_offset_bottom = 0;
	if (hit->parent_wall_start < 0)
	{
		hit->parent_texture_offset_top = -hit->parent_wall_start * hit->texture_step.y;
		hit->parent_wall_start = 0;
	}
	if (hit->wall_end < 0)
		hit->parent_texture_offset_bottom = -hit->wall_end * hit->texture_step.y;
	if (hit->parent_wall_start >= WIN_H)
		hit->parent_wall_start = WIN_H - 1;
	if (hit->parent_wall_end < 0)
		hit->parent_wall_end = 0;
	if (hit->parent_wall_end >= WIN_H)
		hit->parent_wall_end = WIN_H - 1;
}

/**
 * Calculates wall starting and ending positions in window y coordinates.
*/
static void	calculate_vertical_positions(t_app *app, t_rayhit *hit)
{
	double		relative_height;

	relative_height = WIN_H / hit->distance;
	hit->height = (int)(relative_height
			* (hit->sector->ceiling_height - hit->sector->floor_height));
	hit->wall_start = WIN_H / 2 - hit->height + (int)(relative_height
			* (app->player.height - hit->sector->floor_height));
	hit->wall_end = hit->wall_start + hit->height;
	hit->texture_step.y = TEX_SIZE / relative_height;
	hit->texture_offset.y = 0;
	if (hit->sector->parent_sector >= 0)
		calculate_parent_positions(app, hit, relative_height);
	if (hit->wall_start < 0)
	{
		hit->texture_offset.y = -hit->wall_start * hit->texture_step.y;
		hit->wall_start = 0;
	}
	if (hit->wall_start >= WIN_H)
		hit->wall_start = WIN_H - 1;
	if (hit->wall_end < 0)
		hit->wall_end = 0;
	if (hit->wall_end >= WIN_H)
		hit->wall_end = WIN_H - 1;
}

/**
 * Performs raycast from player to wall. Updates values into rayhit struct to be
 * used later in rendering.
 * Returns TRUE if there was a hit and FALSE otherwise.
*/
static t_bool	raycast_hit(t_app *app, t_vertex2 wall, t_rayhit *hit, int x)
{
	t_vertex2	ray_vertex;
	double		camera_x;
	double		angle;

	ray_vertex.a = app->player.pos;
	camera_x = 2 * x / (double) WIN_W - 1.f;
	hit->ray = (t_vector2){
		app->player.dir.x + app->player.cam.x * camera_x, 
		app->player.dir.y + app->player.cam.y * camera_x};
	ray_vertex.b = ft_vector_resize(hit->ray, MAX_VIEW_DISTANCE);
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
	hit->distortion = cos(angle);
	hit->distance = hit->distortion * hit->distance;
	calculate_vertical_positions(app, hit);
	return (TRUE);
}

/**
 * Draws individual sector wall, possible ceiling and floor of that vertical
 * screenline. Also updates occlusion arrays accordingly.
 */
void	sector_walls_raycast(t_app *app, t_thread_data *thread, t_wall *wall)
{
	t_rayhit	hit;
	int			x;

	hit.sector = &app->sectors[wall->sector_id];
	hit.texture = app->sectors[wall->sector_id].wall_textures[wall->wall_id];
	x = wall->start_x;
	//ft_printf("Sector %d, floor h: %f, ceiling h: %f\n", wall->sector_id, app->sectors[wall->sector_id].floor_height, app->sectors[wall->sector_id].ceiling_height);
	while (++x < wall->end_x)
	{
		if (x % THREAD_COUNT != thread->id)
			continue ;
		/**
		 * Perform rayhit. Skips when there is no hit.
		*/
		if (!raycast_hit(app, wall->vertex, &hit, x))
			continue ;
		// If portal or member (member sectors automatically portals)
		if (wall->is_portal)
		{
			if (!wall->is_inside || (wall->is_inside && !wall->is_member))
				draw_parent(app, x, &hit);
			/**
			 * TODO: REMOVE THESE 2 LINES after editor has floor/ceiling texture changes
			 */
			hit.sector->ceiling_texture = 4;
			hit.sector->floor_texture = 4;
			draw_ceiling(app, x, &hit);
			draw_floor(app, x, &hit);
			//draw_wall(app, x, &hit, OCCLUDE_BOTH);
			continue ;
		}
		// IF wall type normal wall:
		draw_ceiling(app, x, &hit);
		draw_floor(app, x, &hit);
		draw_wall(app, x, &hit, OCCLUDE_BOTH);
	}
}
