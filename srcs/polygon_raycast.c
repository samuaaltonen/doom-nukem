/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   polygon_raycast.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 20:57:37 by saaltone          #+#    #+#             */
/*   Updated: 2022/09/26 00:38:11 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * Sets starting pixel, wall height and texture step limited to window
 * dimensions.
 */
static void	wall_limits(int *start_pixel, int *height,
	double *y_step, double *tex_y)
{
	*height += 2;
	*y_step = (TEX_SIZE / (double)*height);
	*tex_y = 0;
	if (*height > WIN_H)
	{
		*tex_y = (*height - WIN_H) / 2 * *y_step;
		*height = WIN_H;
	}
	*start_pixel = WIN_H / 2 - *height / 2;
	if (*start_pixel < 0)
		*start_pixel = 0;
}

/**
 * Draws vertical line to image based on wall distance (closer = higher).
 */
static void	draw_vertical_line(t_app *app, int x, double distance, int texture, double texture_offset)
{
	int		start_pixel;
	int		i;
	int		height;
	double	tex_y;
	double	y_step;

	height = (int) (WIN_H / distance);
	y_step = TEX_SIZE / (double) height;
	start_pixel = WIN_H / 2 - height / 2;
	wall_limits(&start_pixel, &height, &y_step, &tex_y);
	i = 0;
	while (i < height)
	{
		tex_y += y_step;
		put_pixel_to_image(app->image, x, start_pixel + i,
			get_pixel_color(app->sprite, (int)(((double)texture + fmod(texture_offset, 1.0)) * (double)TEX_SIZE), tex_y));
		i++;
	}
}

/**
 * Reduces calculated distance based on angle to remove fisheye effect.
*/
static void	distortion_correction(double camera_x, double camera_length, 
	double *distance)
{
	double			ray_angle;
	
	if (camera_x == 0.f)
		return ;
	ray_angle = atan(fabs(camera_x * camera_length));
	*distance *= cos(ray_angle);
}

/**
 * Raycasts a polygon vertex.
*/
void    polygon_vertex_raycast(t_app *app, t_vertex2 vertex, int texture)
{
	double		camera_x;
	double		distance;
	double		texture_offset;
	t_vertex2	ray_vertex;
	t_vector2	intersection;
	int			x;

	x = -1;
	ray_vertex.a = app->player.pos;
	while (++x < WIN_W)
	{
		camera_x = 2 * x / (double) WIN_W - 1.f;
		ray_vertex.b = ft_vector_resize((t_vector2){
			app->player.dir.x + app->player.cam.x * camera_x, 
			app->player.dir.y + app->player.cam.y * camera_x},
			MAX_VIEW_DISTANCE);
		ray_vertex.b.x += app->player.pos.x;
		ray_vertex.b.y += app->player.pos.y;
		if (!ft_vertex_intersection(vertex, ray_vertex, &intersection))
			continue ;
		distance = ft_vector_length((t_vector2){
			intersection.x - app->player.pos.x,
			intersection.y - app->player.pos.y,
		});
		texture_offset = ft_vector_length((t_vector2){
			vertex.a.x - intersection.x,
			vertex.a.y - intersection.y,
		});
		distortion_correction(camera_x, app->player.camera_length, &distance);
		draw_vertical_line(app, x, distance, texture, texture_offset);
	}
}

void    polygon_raycast(t_app *app, t_poly *polygon)
{
    int i;

    i = 0;
    while (i < polygon->corner_count)
    {
        if (i + 1 < polygon->corner_count)
            polygon_vertex_raycast(app, (t_vertex2){polygon->corners[i], polygon->corners[i + 1]}, polygon->texture);
        else
            polygon_vertex_raycast(app, (t_vertex2){polygon->corners[i], polygon->corners[0]}, polygon->texture);
        i++;
    }
}

/**
 * Multithreaded renderer for polygons
*/
void	*render_polygons(void *data)
{
	t_app	*app;
	int		i;

	app = (t_app *)((t_thread_data *)data)->app;
	i = ((t_thread_data *)data)->id;
	while (i < test_polygon_count)
	{
        polygon_raycast(app, &test_polygons[i]);
		i += THREAD_COUNT;
	}
	pthread_exit(NULL);
}
