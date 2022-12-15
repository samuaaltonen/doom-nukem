/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_control.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <danielmdc94@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 12:41:20 by dpalacio          #+#    #+#             */
/*   Updated: 2022/12/15 13:12:17 by dpalacio         ###   ########.fr       */
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
}

/**
 * @brief Handles player movement and direction depending on keystate.
 * 
 * @param app
 */
void	handle_movement(t_app *app)
{
	if (app->conf->keystates & UP || app->conf->keystates & W)
		player_move(app, FORWARD,
			app->conf->movement_speed * app->conf->delta_time);
	if (app->conf->keystates & DOWN || app->conf->keystates & S)
		player_move(app, BACKWARD,
			app->conf->movement_speed * app->conf->delta_time);
	if (app->conf->keystates & A)
		player_move(app, LEFTWARD,
			app->conf->movement_speed * app->conf->delta_time);
	if (app->conf->keystates & D)
		player_move(app, RIGHTWARD,
			app->conf->movement_speed * app->conf->delta_time);
	if (app->conf->keystates & LEFT)
		player_rotate(app, -app->conf->rotation_speed * app->conf->delta_time);
	if (app->conf->keystates & RIGHT)
		player_rotate(app, app->conf->rotation_speed * app->conf->delta_time);
	if (app->conf->keystates & SPACE)
		player_move(app, UPWARD,
			app->conf->movement_speed * app->conf->delta_time);
	if (app->conf->keystates & CTRL)
		player_move(app, DOWNWARD,
			app->conf->movement_speed * app->conf->delta_time);
}

void	player_shoot(t_app *app)
{
	if (check_timer(&app->shoot_timer) && app->player.equiped_weapon.ammo > 0)
	{
		play_sound(app, SOUND_SHOT_PATH);
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
		play_sound(app, SOUND_RELOAD_PATH);
		if (app->player.equiped_weapon.magazine <= app->player.inventory.ammo)
			app->player.equiped_weapon.ammo = app->player.equiped_weapon.magazine;
		else
			app->player.equiped_weapon.ammo = app->player.inventory.ammo;
		start_timer(&app->shoot_timer, 0.8);
	}
}
