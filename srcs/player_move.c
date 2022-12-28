/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 15:21:33 by saaltone          #+#    #+#             */
/*   Updated: 2022/12/28 14:32:59 by saaltone         ###   ########.fr       */
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

	if (app->player.elevation_velocity < GRAVITY)
		app->player.elevation_velocity = GRAVITY;
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
 * @brief Updates player elevation based on gravity, sector floor/ceiling height
 * and jetpack or jumping.
 * 
 * @param app 
 */
void	update_elevation(t_app *app)
{
	double	floor;
	double	ceil;

	floor = sector_floor_height(app, app->player.sector, app->player.pos);
	ceil = sector_ceil_height(app, app->player.sector, app->player.pos);
	if (!app->player.flying && app->player.elevation > floor)
		app->player.elevation = floor;
	if (app->player.jetpack)
		app->player.elevation_velocity = GRAVITY * JETPACK_FALL;
	else if (app->player.flying && app->player.elevation > floor)
		app->player.elevation_velocity += GRAVITY * app->conf->delta_time;
	if (app->player.elevation < floor && app->player.elevation_velocity
		< (floor - app->player.elevation) * -GRAVITY)
	{
		if (!app->player.jetpack)
			app->player.flying = FALSE;
		app->player.elevation_velocity = (floor - app->player.elevation)
			* -GRAVITY;
	}
	if (ceil < app->player.elevation + app->player.height + COLLISION_CEIL)
		app->player.elevation = ceil - app->player.height - COLLISION_CEIL;
	else if (fabs(app->player.elevation_velocity) > MOVE_MIN)
		app->player.elevation += app->player.elevation_velocity
			* app->conf->delta_time;
}

/**
 * @brief Updates player's position if possible.
 * 
 * @param app 
 */
void	update_position(t_app *app)
{
	update_elevation(app);
	if (!limit_speed(app))
		return ;
	app->player.move_pos = ft_vector2_add(app->player.pos,
			ft_vec2_mult(app->player.move_vector, app->conf->delta_time));
	collisions_check(app);
	app->player.pos = collisions_apply(app);
	check_player_sector(app);
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

/**
 * @brief Updates player elevation/flying values based on elevation change
 * direction.
 * 
 * @param app 
 * @param movement 
 * @param speed 
 */
void	player_elevate(t_app *app, t_movement movement, double speed)
{
	if ((movement == UPWARD || movement == DOWNWARD) && app->player.jetpack)
		app->player.elevation += speed;
	if (movement == UPWARD && !app->player.jetpack && !app->player.flying)
	{
		app->player.flying = TRUE;
		app->player.elevation_velocity = speed;
	}
}
