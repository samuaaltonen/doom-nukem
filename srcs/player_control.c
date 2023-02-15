/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_control.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <danielmdc94@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 12:41:20 by dpalacio          #+#    #+#             */
/*   Updated: 2023/02/15 17:52:39 by dpalacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

static void	use_ammo(t_app *app);

static void	jetpack_handle(t_app *app)
{
	if (!app->player.jetpack && app->conf->keystates & SHIFT)
		app->player.move_speed = RUNNING_SPEED;
	else if (app->player.jetpack)
		app->player.move_speed = MOVEMENT_SPEED;
	else
		app->player.move_speed = MOVEMENT_SPEED;
	if (app->conf->keystates & SPACE && app->player.jetpack)
	{
		energy_charge(app, -4);
		app->player.move_speed = RUNNING_SPEED;
	}
	else if (app->player.jetpack)
		energy_charge(app, -1);
	else
		energy_charge(app, 1);
	if (app->conf->keystates & CTRL && !app->player.jetpack)
		app->player.target_height = PLAYER_HEIGHT_CROUCHING;
	else if (sector_vertical_space(app, app->player.sector, app->player.pos)
		>= PLAYER_HEIGHT_STANDING + COLLISION_CEIL)
		app->player.target_height = PLAYER_HEIGHT_STANDING;
	if (app->player.target_height != app->player.height)
		app->player.height += (app->player.target_height - app->player.height)
			* PLAYER_HEIGHT_CHANGE_RATE * app->conf->delta_time;
}

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
	jetpack_handle(app);
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
	if (check_timer(&app->shoot_timer) && ((app->hand.equipped > 0 && app->player.equipped_weapon.ammo > 0)
			|| (app->hand.equipped == 3 && app->player.inventory.energy >= 50)))
	{
		fire(app, (t_vector3){app->player.dir.x, app->player.dir.y,
			(app->player.horizon - 0.5f)}, (t_vector3){app->player.pos.x,
			app->player.pos.y, app->player.elevation
			+ app->player.height / 2},
			(t_point){app->player.equipped_weapon.type, app->player.sector});
		add_fire_movement(app);
		use_ammo(app);
		start_timer(&app->shoot_timer, app->player.equipped_weapon.fire_rate);
	}
	else if (app->player.equipped_weapon.ammo <= 0
		&& app->player.inventory.ammo > 0)
		player_reload(app);
}

static void	use_ammo(t_app *app)
{
	if (app->hand.equipped == 1)
	{
		play_sound(app, AUDIO_SHOT);
		app->player.equipped_weapon.ammo--;
		app->player.inventory.ammo--;
	}
	else if (app->hand.equipped == 2)
	{
		play_sound(app, AUDIO_BUMP);
		app->player.equipped_weapon.ammo--;
		app->player.inventory.ammo -=5;
	}
	else if (app->hand.equipped == 3)
	{
		play_sound(app, AUDIO_LASER);
		app->player.inventory.energy -= 50;
	}
}