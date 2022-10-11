/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector_wall_translate.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 16:46:07 by saaltone          #+#    #+#             */
/*   Updated: 2022/10/12 00:21:45 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * Updates screen x position to pixel positions.
 */
/* static void	translate_x(t_app *app, double ray_angle, int side,
	t_point_matrix *pixels)
{
	int		screen_x;

	if (side)
		ray_angle *= -1.0;
	if (ray_angle < -M_2_PI)
		screen_x = 0;
	else if (ray_angle > M_2_PI)
		screen_x = WIN_W - 1;
	else
		screen_x = WIN_W / 2 + WIN_W * tan(ray_angle)
			/ app->player.camera_length / 2;
	pixels->a.x = screen_x;
	pixels->b.x = screen_x;
} */

/**
 * Updates starting and ending pixels depending on distance.
 */
/* static void	translate_y(t_app *app, int sector_id, double distance,
	t_point_matrix *pixels)
{
	double	relative_height;
	int		height;
	int		start_pixel;
	int		end_pixel;

	relative_height = WIN_H / distance;
	height = (int)(relative_height
			* (test_sectors[sector_id].ceiling_height
				- test_sectors[sector_id].floor_height));
	start_pixel = WIN_H / 2 - height + (int)(relative_height
			* (app->player.height
				- test_sectors[sector_id].floor_height));
	end_pixel = start_pixel + height;
	pixels->a.y = start_pixel;
	pixels->b.y = end_pixel;
} */

/**
 * Translates given position to screenspace. Calculated distance and offsets.
 */
/* t_point_matrix	translate_to_screen_space(t_app *app, int sector_id,
	t_vector2 coord)
{
	t_point_matrix	pixels;
	t_vector2		ray;
	double			distance;
	double			ray_angle;
	int				side;

	ray = (t_vector2){coord.x - app->player.pos.x, coord.y - app->player.pos.y};
	ray_angle = ft_vector_angle(ray, app->player.dir);
	distance = distortion_correction(ray_angle, ft_vector_length(ray));
	side = ft_vertex_side((t_vertex2){app->player.pos,
			(t_vector2){app->player.pos.x + app->player.dir.x,
			app->player.pos.y + app->player.dir.y}}, coord);
	translate_x(app, ray_angle, side, &pixels);
	translate_y(app, sector_id, distance, &pixels);
	return (pixels);
} */

/**
 * Translates world coordinate position to camera space and converts it to
 * window x position.
*/
int	translate_window_x(t_app *app, t_vector2 coord)
{
	int			x;
	t_vector2	ray;
	double		angle;

	ray = (t_vector2){coord.x - app->player.pos.x, coord.y - app->player.pos.y};
	angle = ft_vector_angle(ray, app->player.dir);
	// If left side, mark angle as negative
	if (ft_vertex_side((t_vertex2){app->player.pos,
			(t_vector2){app->player.pos.x + app->player.dir.x,
			app->player.pos.y + app->player.dir.y}}, coord))
		angle *= -1.0;
	if (angle < -M_2_PI)
		x = 0;
	else if (angle > M_2_PI)
		x = WIN_W - 1;
	else
		x = WIN_W / 2 + WIN_W * tan(angle) / app->player.camera_length / 2;
	return (x);
}