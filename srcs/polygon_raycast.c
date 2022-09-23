/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   polygon_raycast.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 20:57:37 by saaltone          #+#    #+#             */
/*   Updated: 2022/09/23 21:31:57 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * Raycasts a polygon vertex.
*/
void    polygon_vertex_raycast(t_app *app, t_vector2 start, t_vector2 end)
{
    t_vector2 start_ray;

    start_ray.x = app->player.dir.x + start.x;
    start_ray.y = app->player.dir.y + start.y;
    (void)start_ray;
    (void)end;
}

void    polygon_raycast(t_app *app, t_poly polygon)
{
    int i;

    i = 0;
    while (i < polygon.corner_count)
    {
        if (i + 1 < polygon.corner_count)
            polygon_vertex_raycast(app, polygon.corners[i], polygon.corners[i + 1]);
        else
            polygon_vertex_raycast(app, polygon.corners[i], polygon.corners[0]);
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
