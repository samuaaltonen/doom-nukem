/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   polygon_raycast.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 20:57:37 by saaltone          #+#    #+#             */
/*   Updated: 2022/09/27 17:15:50 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * Sets starting pixel, wall height and texture step limited to window
 * dimensions.
 */
static void	wall_limits(int *start_pixel, int *height,
	double *tex_y, double y_step)
{
	*height += 2;
	*tex_y = 0;
	if (*start_pixel < 0)
	{
		*tex_y = -*start_pixel * y_step;
		*height = WIN_H;
		*start_pixel = 0;
	}
}

/**
 * Draws vertical line to image based on wall distance (closer = higher).
 */
static void	draw_vertical_line(t_app *app, t_polygon *polygon, int x, double distance, double texture_offset)
{
	int		start_pixel;
	int		i;
	int		height;
	double	tex_y;
	double	y_step;

	texture_offset = fmod(texture_offset, 1.0);
	height = (int) ((WIN_H / distance) * (polygon->top - polygon->bottom));
	y_step = TEX_SIZE / (WIN_H / distance);
	start_pixel = WIN_H / 2 - height + (int) (WIN_H / distance / 2.f);
	wall_limits(&start_pixel, &height, &tex_y, y_step);
	i = 0;
	while (i < height)
	{
		tex_y += y_step;
		if (tex_y >= (double) TEX_SIZE)
			tex_y = fmod(tex_y, (double) TEX_SIZE);
		put_pixel_to_image_check(app, (t_point){x, start_pixel + i},
			get_pixel_color(app->sprite, (int)(((double)polygon->texture + texture_offset) * (double)TEX_SIZE), tex_y),
			distance);
		i++;
	}
	if (polygon->hits[x].y_first_top)
	{
		polygon->hits[x].y_second_top = start_pixel;
		polygon->hits[x].y_second_bottom = start_pixel + i;
		polygon->hits[x].distance_second = distance;
		return ;
	}
	polygon->hits[x].y_first_top = start_pixel;
	polygon->hits[x].y_first_bottom = start_pixel + i;
	polygon->hits[x].distance_first = distance;
}

/**
 * Reduces calculated distance based on angle to remove fisheye effect.
*/
static void	distortion_correction(double camera_x, double camera_length, 
	double *distance)
{
	double	ray_angle;
	
	if (camera_x == 0.f)
		return ;
	ray_angle = atan(fabs(camera_x * camera_length));
	*distance *= cos(ray_angle);
}

/**
 * Raycasts a polygon vertex.
*/
void    polygon_vertex_raycast(t_app *app, t_polygon *polygon, int corner_a, int corner_b)
{
	t_vertex2	wall_vertex;
	t_vertex2	ray_vertex;
	t_vector2	intersection;
	double		camera_x;
	double		distance;
	double		texture_offset;
	int			x;

	wall_vertex = (t_vertex2){polygon->corners[corner_a], polygon->corners[corner_b]};
	ray_vertex.a = app->player.pos;
	x = -1;
	while (++x < WIN_W)
	{
		camera_x = 2 * x / (double) WIN_W - 1.f;
		ray_vertex.b = ft_vector_resize((t_vector2){
			app->player.dir.x + app->player.cam.x * camera_x, 
			app->player.dir.y + app->player.cam.y * camera_x},
			MAX_VIEW_DISTANCE);
		ray_vertex.b.x += app->player.pos.x;
		ray_vertex.b.y += app->player.pos.y;
		if (!ft_vertex_intersection(wall_vertex, ray_vertex, &intersection))
			continue ;
		distance = ft_vector_length((t_vector2){
			intersection.x - app->player.pos.x,
			intersection.y - app->player.pos.y,
		});
		texture_offset = ft_vector_length((t_vector2){
			wall_vertex.a.x - intersection.x,
			wall_vertex.a.y - intersection.y,
		});
		distortion_correction(camera_x, app->player.camera_length, &distance);
		draw_vertical_line(app, polygon, x, distance, texture_offset);
	}
}

void    polygon_raycast(t_app *app, t_polygon *polygon)
{
    int				i;
	t_polygon_hit	hits[WIN_W];

    i = 0;
	ft_bzero((void *)&hits, sizeof(t_polygon_hit) * WIN_W);
	polygon->hits = (t_polygon_hit *)&hits;
    while (i < polygon->corner_count)
    {
        if (i + 1 < polygon->corner_count)
            polygon_vertex_raycast(app, polygon, i, i + 1);
        else
            polygon_vertex_raycast(app, polygon, i, 0);
        i++;
    }
	polygon_draw_floors(app, polygon);
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
