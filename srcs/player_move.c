/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 15:21:33 by saaltone          #+#    #+#             */
/*   Updated: 2023/01/27 15:05:03 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * @brief Limits player movement speed to maximum value. Also if movement is
 * very small, round to 0.
 * 
 * @param app 
 */
static t_bool	limit_speed(t_app *app)
{
	double	speed;

	speed = ft_vector_length(app->player.move_vector);
	if (speed < MOVE_MIN)
	{
		app->player.move_vector = (t_vector2){0.0, 0.0};
		return (FALSE);
	}
	if (app->player.is_decelerating)
		app->player.move_vector = ft_vec2_lerp(app->player.move_vector,
				(t_vector2){0.f, 0.f}, MOVE_DECEL * app->conf->delta_time);
	if (speed > app->player.move_speed)
		app->player.move_vector = ft_vector_resize(app->player.move_vector,
				app->player.move_speed);
	return (TRUE);
}

/**
 * @brief Updates player's position if possible.
 * 
 * @param app 
 */
void	update_position(t_app *app)
{
	int			old_sector;
	t_vector2	old_position;

	update_elevation(app);
	if (!limit_speed(app))
		return ;
	old_sector = app->player.sector;
	old_position = app->player.pos;
	app->player.move_pos = ft_vector2_add(app->player.pos,
			ft_vec2_mult(app->player.move_vector, app->conf->delta_time));
	collisions_check(app);
	app->player.pos = collisions_apply(app);
	check_player_sector(app, old_sector, old_position);
}

/**
 * @brief Updates player movement vector based on movement direction.
 * 
 * @param app 
 * @param movement 
 * @param speed 
 */
void	player_move(t_app *app, t_movement movement, double speed)
{
	t_vector2	perpendicular;

	app->player.is_decelerating = FALSE;
	if (movement == FORWARD)
		app->player.move_vector = ft_vector2_add(app->player.move_vector,
				(t_vector2){app->player.dir.x * speed,
				app->player.dir.y * speed});
	if (movement == BACKWARD)
		app->player.move_vector = ft_vector2_add(app->player.move_vector,
				(t_vector2){-app->player.dir.x * speed,
				-app->player.dir.y * speed});
	if (movement == LEFTWARD || movement == RIGHTWARD)
	{
		perpendicular = ft_vector_perpendicular(app->player.dir);
		if (movement == LEFTWARD)
			app->player.move_vector = ft_vector2_sub(app->player.move_vector,
					(t_vector2){perpendicular.x * speed,
					perpendicular.y * speed});
		if (movement == RIGHTWARD)
			app->player.move_vector = ft_vector2_add(app->player.move_vector,
					(t_vector2){perpendicular.x * speed,
					perpendicular.y * speed});
	}
}
