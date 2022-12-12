/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <danielmdc94@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 15:14:06 by saaltone          #+#    #+#             */
/*   Updated: 2022/12/09 17:08:27 by dpalacio         ###   ########.fr       */
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
	app->sky.size.x = WIN_W * 4;
	app->sky.pixel_step.x = SKYBOX_W / (double)app->sky.size.x;
	app->sky.pixel_step.y = SKYBOX_H / (double)app->sky.size.y;
	app->sky.start.x = app->sky.size.x * ft_vector_angle_right(app->player.dir,
			(t_vector2){1.0, 0.0}) / (M_PI * 2);
	app->sky.start.y = WIN_H * app->player.horizon - app->sky.size.y / 2;
}

/**
 * @brief Initializes player position and view.
 * 
 * @param app 
 */
void	player_init(t_app *app)
{
	app->player.pos = (t_vector2){POSITION_START_X, POSITION_START_Y};
	app->player.dir = (t_vector2){DIRECTION_START_X, DIRECTION_START_Y};
	app->player.height = 0.5;
	app->player.elevation = 0.0;
	app->player.horizon = 0.5;
	app->player.current_sector = 0;
	//----DEBUG FEATURE
	app->player.weapons = 0;
	app->player.equiped_weapon.magazine = 9;
	app->player.equiped_weapon.ammo = 9;
	app->player.equiped_weapon.fire_rate = 0.2;
	//----
	init_camera_plane(app);
	init_skybox_plane(app);
}
