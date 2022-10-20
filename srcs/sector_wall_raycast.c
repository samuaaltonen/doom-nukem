/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector_wall_raycast.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 13:12:51 by saaltone          #+#    #+#             */
/*   Updated: 2022/10/20 14:54:12 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

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
	while (++x < wall->end_x)
	{
		if (x % THREAD_COUNT != thread->id)
			continue ;
		/**
		 * Perform rayhit. Skips when there is no hit.
		*/
		if (!raycast_hit(app, wall->vertex, &hit, x))
			continue ;
		// IF wall type normal wall:
		if (hit.sector->wall_types[wall->wall_id] == -1)
		{
			draw_ceiling(app, x, &hit);
			draw_floor(app, x, &hit);
			draw_wall(app, x, &hit);
		}
		// IF portal / member
		// Draw ceiling
		// Draw floor
		// If floor higher or ceiling smaller of next sector, draw partial wall
	}
}
