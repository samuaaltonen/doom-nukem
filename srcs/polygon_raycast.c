/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   polygon_raycast.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 20:57:37 by saaltone          #+#    #+#             */
/*   Updated: 2022/09/25 19:48:07 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * Draws vertical line to image based on wall distance (closer = higher).
 */
static void	draw_vertical_line(t_app *app, int x, int height)
{
	int		start_pixel;
	int		i;

	start_pixel = WIN_H / 2 - height / 2;
	i = 0;
	while (i < height)
	{
		put_pixel_to_image(app->image, x, start_pixel + i, 0x00FFFFFF);
		i++;
	}
}

/**
 * Raycasts a polygon vertex.
*/
void    polygon_vertex_raycast(t_app *app, t_vertex2 vertex)
{
	double		camera_x;
	double		distance;
	t_vertex2	ray_vertex;
	t_vector2	intersection;
	int			x;

	x = 0;
	ray_vertex.a = app->player.pos;
	while (x < WIN_W)
	{
		camera_x = 2 * x / (double) WIN_W - 1.f;
		ray_vertex.b = ft_vector_resize((t_vector2){
			app->player.dir.x + app->player.cam.x * camera_x, 
			app->player.dir.y + app->player.cam.y * camera_x},
			MAX_VIEW_DISTANCE);
		ray_vertex.b.x -= app->player.pos.x;
		ray_vertex.b.y -= app->player.pos.y;
		if (ft_vertex_intersection(vertex, ray_vertex, &intersection))
		{
			distance = ft_vector_length((t_vector2){
				intersection.x - app->player.pos.x,
				intersection.y - app->player.pos.y,
			});
			draw_vertical_line(app, x, (int) (WIN_H / distance));
		}
		x++;
	}
}

void    polygon_raycast(t_app *app, t_poly polygon)
{
    int i;

    i = 0;
    while (i < polygon.corner_count)
    {
        if (i + 1 < polygon.corner_count)
            polygon_vertex_raycast(app, (t_vertex2){polygon.corners[i], polygon.corners[i + 1]});
        else
            polygon_vertex_raycast(app, (t_vertex2){polygon.corners[i], polygon.corners[0]});
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
        polygon_raycast(app, test_polygons[i]);
		i += THREAD_COUNT;
	}
	pthread_exit(NULL);
}
