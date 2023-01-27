/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_view.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 14:56:23 by saaltone          #+#    #+#             */
/*   Updated: 2023/01/27 17:02:31 by saaltone         ###   ########.fr       */
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
	app->sky.start.x = app->sky.size.x * ft_vector_angle_left(app->player.dir,
			(t_vector2){1.0, 0.0}) / M_PI;
	app->sky.start.y = WIN_H * app->player.horizon - app->sky.size.y / 2;
}

/**
 * @brief Get the player side of a line. If player is located on the line,
 * determines preferred side based on view direction. Returns -1 if player is
 * located on the line and looking directly along the line (then order doesnt
 * matter).
 * 
 * @param app 
 * @return int 
 */
int	get_player_side(t_app *app, t_line line)
{
	t_vector2	view_pos;

	if (!ft_line_point(line, app->player.pos))
		return (ft_line_side(line, app->player.pos));
	view_pos = ft_vector2_add(app->player.pos, app->player.dir);
	if (ft_line_point(line, view_pos))
		return (-1);
	return (!ft_line_side(line, view_pos));
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
