/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_control.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <danielmdc94@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 12:41:20 by dpalacio          #+#    #+#             */
/*   Updated: 2023/01/17 11:45:16 by dpalacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * @brief Handles player controls
 * 
 * @param app
 */
void	player_control(t_app *app)
{
	handle_movement(app);
	update_position(app);
	regen(app, &app->player.hp);
	regen(app, &app->player.shield);
	if (app->conf->buttonstates & LEFT_MOUSE)
		player_shoot(app);
	if (app->conf->keystates & R)
		player_reload(app);
	if (app->conf->keystates & Q)
		heal(app);
	if (app->conf->keystates & E)
		shield(app);
	if (app->conf->keystates & SHIFT)
		app->player.move_speed = RUNNING_SPEED;
	else
		app->player.move_speed = MOVEMENT_SPEED;
	if (app->conf->keystates & C)
		jetpack(app);
	if (app->player.jetpack)
		energy(app, -2);
	else if (app->conf->keystates & SPACE && app->player.jetpack)
		energy(app, -20);
	else
		energy(app, 1);
	if (app->conf->keystates & CTRL && !app->player.jetpack)
		app->player.target_height = PLAYER_HEIGHT_CROUCHING;
	else if (sector_vertical_space(app, app->player.sector, app->player.pos)
		>= PLAYER_HEIGHT_STANDING + COLLISION_CEIL)
		app->player.target_height = PLAYER_HEIGHT_STANDING;
	if (app->player.target_height != app->player.height)
		app->player.height += (app->player.target_height - app->player.height) * PLAYER_HEIGHT_CHANGE_RATE * app->conf->delta_time;
}

/**
 * @brief Handles player movement and direction depending on keystate.
 * 
 * @param app
 */
void	handle_movement(t_app *app)
{
	app->player.is_decelerating = TRUE;
	if (app->conf->keystates & UP || app->conf->keystates & W)
		player_move(app, FORWARD, MOVE_ACCEL * app->conf->delta_time);
	if (app->conf->keystates & DOWN || app->conf->keystates & S)
		player_move(app, BACKWARD, MOVE_ACCEL * app->conf->delta_time);
	if (app->conf->keystates & A)
		player_move(app, LEFTWARD, MOVE_ACCEL * app->conf->delta_time);
	if (app->conf->keystates & D)
		player_move(app, RIGHTWARD, MOVE_ACCEL * app->conf->delta_time);
	if (app->conf->keystates & LEFT)
		player_rotate(app, -ROTATION_SPEED * app->conf->delta_time);
	if (app->conf->keystates & RIGHT)
		player_rotate(app, ROTATION_SPEED * app->conf->delta_time);
	if (app->conf->keystates & SPACE && !app->player.jetpack)
		player_elevate(app, UPWARD, JUMP_FORCE);
	if (app->conf->keystates & SPACE && app->player.jetpack)
		player_elevate(app, UPWARD, JETPACK_ASCENT * app->conf->delta_time);
	if (app->conf->keystates & CTRL && app->player.jetpack)
		player_elevate(app, DOWNWARD, JETPACK_DESCENT * app->conf->delta_time);
}

void	player_shoot(t_app *app)
{
	if (check_timer(&app->shoot_timer) && app->player.equiped_weapon.ammo > 0)
	{
		fire(app,(t_vector3){app->player.dir.x, app->player.dir.y,(app->player.horizon - 0.5f)},(t_vector3){app->player.pos.x, app->player.pos.y,app->player.elevation + app->player.height / 2},(t_point){18,app->player.sector});
		play_sound(app, AUDIO_SHOT);
		app->player.equiped_weapon.ammo--;
		app->player.inventory.ammo--;
		start_timer(&app->shoot_timer, app->player.equiped_weapon.fire_rate);
	}
	else if (app->player.equiped_weapon.ammo <= 0 && app->player.inventory.ammo > 0)
		player_reload(app);
}

void	player_reload(t_app *app)
{
	if (check_timer(&app->shoot_timer) && app->player.inventory.ammo
		&& app->player.equiped_weapon.ammo < app->player.equiped_weapon.magazine)
	{
		play_sound(app, AUDIO_RELOAD);
		if (app->player.equiped_weapon.magazine <= app->player.inventory.ammo)
			app->player.equiped_weapon.ammo = app->player.equiped_weapon.magazine;
		else
			app->player.equiped_weapon.ammo = app->player.inventory.ammo;
		start_timer(&app->shoot_timer, 0.8);
	}
}

void	jetpack(t_app *app)
{
	if (check_timer(&app->item_timer) && app->player.jetpack)
	{
		app->player.jetpack = FALSE;
		app->player.elevation_velocity = JETPACK_FALL;
		start_timer(&app->item_timer, 4);
	}
	else if (check_timer(&app->item_timer) && !app->player.jetpack)
	{
		app->player.jetpack = TRUE;
		app->player.flying = TRUE;
		app->player.elevation_velocity = 0.0;
		start_timer(&app->item_timer, 1);
	}
}
