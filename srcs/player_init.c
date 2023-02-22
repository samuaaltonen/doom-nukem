/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 15:14:06 by saaltone          #+#    #+#             */
/*   Updated: 2023/02/21 14:24:39 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * @brief Calculates initial camera plane using FOV and player direction vector.
 * Camera plane is always perpendicular to the direction vector.
 * 
 * cameralength = directionlength * tan(FOV / 2)
 * 
 * @param app 
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
 * @brief Initializes skybox size and offsets.
 * 
 * @param app 
 */
void	init_skybox_plane(t_app *app)
{
	app->sky.size.y = (int)(WIN_H
			+ WIN_H * (HORIZON_UPPER_LIMIT - 0.5)
			+ WIN_H * (0.5 - HORIZON_LOWER_LIMIT));
	app->sky.size.x = WIN_W * 2;
	app->sky.pixel_step.x = SKYBOX_W / (double)app->sky.size.x;
	app->sky.pixel_step.y = SKYBOX_H / (double)app->sky.size.y;
	app->sky.start.x = app->sky.size.x * ft_vector_angle_left(app->player.dir,
			(t_vector2){1.0, 0.0}) / M_PI;
	app->sky.start.y = WIN_H * app->player.horizon - app->sky.size.y / 2;
}

/**
 * @brief Initializes player position and view.
 * 
 * @param app 
 */
void	player_init(t_app *app)
{
	app->player.dir = (t_vector2){DIRECTION_START_X, DIRECTION_START_Y};
	app->player.horizon = 0.5;
	app->player.elevation_velocity = 0.0;
	app->player.height = PLAYER_HEIGHT_STANDING;
	app->player.hp = PLAYER_MAX_HEALTH;
	app->player.inventory.energy = PLAYER_MAX_ENERGY;
	init_camera_plane(app);
	init_skybox_plane(app);
}
