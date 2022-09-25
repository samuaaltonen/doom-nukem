/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 15:14:06 by saaltone          #+#    #+#             */
/*   Updated: 2022/09/25 22:28:36 by saaltone         ###   ########.fr       */
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
		app->thread_info[i] = (t_thread_data){
			app,
			i
		};
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

/**
 * Initializes configuration struct.
 */
int	conf_init(t_app *app)
{
	if (!app)
		return (0);
	app->conf = (t_conf *)malloc(sizeof(t_conf));
	if (!(app->conf))
		return (0);
	ft_bzero(app->conf, sizeof(t_conf));
	clock_gettime(CLOCK_REALTIME, &app->conf->fps_clock);
	app->conf->fov = FOV;
	app->conf->skybox_offset = 360.f;
	app->conf->movement_speed = MOVEMENT_SPEED;
	app->conf->rotation_speed = ROTATION_SPEED;
	init_thread_info(app);
	return (1);
}
