/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 15:14:06 by saaltone          #+#    #+#             */
/*   Updated: 2022/11/11 14:47:08 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * Inits thread information structs. They contain info about what part of the
 * window each thread calculates.
 */
void	init_thread_info(t_app *app)
{
	int	i;

	i = 0;
	while (i < THREAD_COUNT)
	{
		app->thread_info[i].app = app;
		app->thread_info[i].id = i;
		app->thread_info[i].has_work = FALSE;
		app->thread_info[i].cond = (pthread_cond_t)PTHREAD_COND_INITIALIZER;
		app->thread_info[i].lock = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
		i++;
	}
}

/**
 * Calculates initial camera plane using FOV and player direction vector.
 * Camera plane is always perpendicular to the direction vector.
 * 
 * cameralength = directionlength * tan(FOV / 2)
 */
void	init_camera_plane(t_app *app)
{
	t_vector2	camera_plane;
	double		camera_length;
	double		direction_length;

	direction_length = ft_vector_length(app->player.dir);
	camera_length = direction_length * tan(app->conf->fov
			* DEG_IN_RADIAN / 2.0f);
	camera_plane = ft_vector_resize(ft_vector_perpendicular(
				app->player.dir), camera_length);
	app->player.cam = camera_plane;
	app->player.camera_length = camera_length;
}
