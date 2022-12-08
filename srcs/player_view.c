/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_view.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 14:56:23 by saaltone          #+#    #+#             */
/*   Updated: 2022/12/05 17:46:00 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * @brief Updates skybox offsets
 * 
 * @param app 
 */
static void	update_sky_values(t_app *app)
{
	app->sky.start.x = app->sky.size.x * ft_vector_angle_right(app->player.dir,
			(t_vector2){1.0, 0.0}) / M_PI;
	app->sky.start.y = WIN_H * app->player.horizon - app->sky.size.y / 2;
}

/**
 * @brief Rotates player direction by given angle.
 * 
 * @param app 
 * @param angle 
 */
void	player_rotate(t_app *app, double angle)
{
	t_matrix2	rotation;

	rotation = (t_matrix2){
		(t_vector2){cos(angle), -sin(angle)},
		(t_vector2){sin(angle), cos(angle)}
	};
	app->player.dir = ft_vector_multiply_matrix(app->player.dir, rotation);
	app->player.cam = ft_vector_multiply_matrix(app->player.cam, rotation);
	app->conf->skybox_offset = fmod(app->conf->skybox_offset + 720.f, 720.f)
		+ angle * RADIAN_IN_DEG;
	update_sky_values(app);
}

/**
 * @brief Updates player horizon values when looking up/down.
 * 
 * @param app 
 * @param angle 
 */
void	player_horizon(t_app *app, double change)
{
	app->player.horizon -= change;
	if (app->player.horizon > HORIZON_UPPER_LIMIT)
		app->player.horizon = HORIZON_UPPER_LIMIT;
	if (app->player.horizon < HORIZON_LOWER_LIMIT)
		app->player.horizon = HORIZON_LOWER_LIMIT;
	update_sky_values(app);
}
