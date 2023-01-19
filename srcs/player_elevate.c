/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_elevate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 15:21:33 by saaltone          #+#    #+#             */
/*   Updated: 2023/01/19 14:37:17 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * @brief Updates players elevation velocity based on forces gravity and floor
 * normal force.
 * 
 * @param app 
 * @param floor 
 * @param ceil 
 */
static void	update_elevation_velocity(t_app *app, double floor)
{
	if (app->player.jetpack)
		app->player.elevation_velocity = GRAVITY * JETPACK_FALL;
	else if (app->player.flying
		|| app->player.elevation > floor + ELEVATION_EPSILON)
		app->player.elevation_velocity += GRAVITY * app->conf->delta_time;
	if (app->player.elevation < floor && app->player.elevation_velocity
		< (floor - app->player.elevation) * -GRAVITY)
	{
		if (app->player.elevation_velocity < FALL_DAMAGE_FORCE_THRESHOLD)
			damage(app, -(int)app->player.elevation_velocity
				* FALL_DAMAGE_MULTIPLIER);
		if (!app->player.jetpack)
			app->player.flying = FALSE;
		app->player.elevation_velocity = (floor - app->player.elevation)
			* -GRAVITY;
	}
	if (!app->player.flying
		&& fabs(floor - app->player.elevation) < ELEVATION_EPSILON
		&& !app->player.jetpack)
	{
		app->player.flying = FALSE;
		app->player.elevation = floor;
		app->player.elevation_velocity = 0.0;
	}
}

/**
 * @brief Updates player elevation based on elevation velocity, sector
 * floor/ceiling height and jetpack or jumping.
 * 
 * @param app 
 */
void	update_elevation(t_app *app)
{
	double	old_elevation;
	double	floor;
	double	ceil;

	old_elevation = app->player.elevation;
	floor = sector_floor_height(app, app->player.sector, app->player.pos);
	ceil = sector_ceil_height(app, app->player.sector, app->player.pos);
	update_elevation_velocity(app, floor);
	if (fabs(app->player.elevation_velocity) > MOVE_MIN)
		app->player.elevation += app->player.elevation_velocity
			* app->conf->delta_time;
	if (ceil < app->player.elevation + app->player.height + COLLISION_CEIL)
		app->player.elevation = ceil - app->player.height - COLLISION_CEIL;
	if (!app->player.flying && app->player.elevation > floor)
		app->player.elevation = floor;
	if (!app->player.jetpack && old_elevation >= floor
		&& app->player.elevation < floor
		&& app->player.elevation_velocity < 0)
	{
		app->player.flying = FALSE;
		app->player.elevation = floor;
		app->player.elevation_velocity = 0.0;
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
