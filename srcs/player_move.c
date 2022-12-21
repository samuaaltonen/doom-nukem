/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 15:21:33 by saaltone          #+#    #+#             */
/*   Updated: 2022/12/21 20:07:34 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

static t_bool ceil_collision(t_app *app)
{
	if (get_sector_ceil_height(app, app->player.current_sector, app->player.pos) < app->player.elevation + PLAYER_HEIGHT)
		return (TRUE);
	return (FALSE);
}

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
 * @brief Updates player's position if possible.
 * 
 * @param app 
 */
void	update_position(t_app *app)
{
	double	pos_floor_height = get_sector_floor_height(app, app->player.current_sector, app->player.pos);

	if (!app->player.flying && app->player.elevation > pos_floor_height)
		app->player.elevation = pos_floor_height;

	if(app->player.flying)
	{
		if (app->player.jetpack)
			app->player.elevation_velocity = GRAVITY * JETPACK_FALL;
		else
			app->player.elevation_velocity += GRAVITY * app->conf->delta_time;
	}

	if (ceil_collision(app))
		app->player.elevation = get_sector_ceil_height(app, app->player.current_sector, app->player.pos) - PLAYER_HEIGHT;
	else
		app->player.elevation += app->player.elevation_velocity * app->conf->delta_time;

	if (app->player.elevation < pos_floor_height)
	{
		//ft_printf("stepping %f\n", app->player.elevation);
		if (!app->player.jetpack)
		{
			app->player.flying = FALSE;
			app->player.elevation_velocity = 0.0;
		}
		//app->player.elevation = ft_lerp(app->player.elevation, pos_floor_height, app->player.step_timer);
		app->player.elevation = pos_floor_height;
		app->player.step_timer += app->conf->delta_time;
	}
	else
		app->player.step_timer = 0.0;

	if (!limit_speed(app))
		return ;

	app->player.move_pos = ft_vector2_add(app->player.pos, ft_vec2_mult(app->player.move_vector, app->conf->delta_time));
	collision_check(app);
	/* if (!check_collisions(app, &new))
	{
		app->player.move_vector = (t_vector2){0.f, 0.f};
		app->player.move_pos = new;
	} */
	app->player.pos = app->player.move_pos;
}

/**
 * @brief Moves player to given direction if there is no collision.
 * 
 * @param app 
 * @param movement 
 * @param speed 
 */
void	player_move(t_app *app, t_movement movement, double speed)
{
	t_vector2	perpendicular;

	if (!(movement == FORWARD || movement == BACKWARD
			|| movement == LEFTWARD || movement == RIGHTWARD 
			|| movement == UPWARD || movement == DOWNWARD))
		return ;
	app->player.is_decelerating = FALSE;
	if (movement == FORWARD)
		app->player.move_vector = ft_vector2_add(app->player.move_vector,
				(t_vector2){app->player.dir.x * speed,
				app->player.dir.y * speed});
	if (movement == BACKWARD)
		app->player.move_vector = ft_vector2_add(app->player.move_vector,
				(t_vector2){-app->player.dir.x * speed,
				-app->player.dir.y  * speed});
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
	if ((movement == UPWARD || movement == DOWNWARD) && app->player.jetpack)
		app->player.elevation += speed;
	if (movement == UPWARD && !app->player.jetpack && !app->player.flying)
	{
		app->player.flying = TRUE;
		app->player.elevation_velocity = speed;
	}
}
