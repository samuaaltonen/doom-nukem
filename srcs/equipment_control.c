/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equipment_control.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 21:05:44 by htahvana          #+#    #+#             */
/*   Updated: 2023/02/06 21:10:28 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

void	player_reload(t_app *app)
{
	if (check_timer(&app->shoot_timer) && app->player.inventory.ammo
		&& app->player.equipped_weapon.ammo
		< app->player.equipped_weapon.magazine)
	{
		play_sound(app, AUDIO_RELOAD);
		if (app->player.equipped_weapon.magazine <= app->player.inventory.ammo)
			app->player.equipped_weapon.ammo
				= app->player.equipped_weapon.magazine;
		else
			app->player.equipped_weapon.ammo = app->player.inventory.ammo;
		start_timer(&app->shoot_timer, 0.8);
	}
}

void	jetpack(t_app *app)
{
	if (app->player.jetpack)
	{
		app->player.jetpack = FALSE;
		app->player.elevation_velocity = JETPACK_FALL;
	}
	else if (!app->player.jetpack)
	{
		app->player.jetpack = TRUE;
		app->player.flying = TRUE;
		app->player.elevation_velocity = 0.0;
	}
}

void	weapon(t_app *app, int weapon)
{
	if (app->player.weapons & 0b00000001 && weapon == 1)
	{
		app->hand.equipped = 0;
		app->player.equipped_weapon.type = 7;
		app->player.equipped_weapon.magazine = WEAPON1_MAG;
		app->player.equipped_weapon.fire_rate = 0.3;
		start_timer(&app->shoot_timer, 2.0f);
	}
	else if (app->player.weapons & 0b00000001 && weapon == 2)
	{
		app->hand.equipped = 1;
		app->player.equipped_weapon.type = 4;
		app->player.equipped_weapon.magazine = WEAPON2_MAG;
		app->player.equipped_weapon.fire_rate = 0.1;
		start_timer(&app->shoot_timer, 2.0f);
	}
	if (app->player.equipped_weapon.magazine <= app->player.inventory.ammo)
		app->player.equipped_weapon.ammo = app->player.equipped_weapon.magazine;
	else
		app->player.equipped_weapon.ammo = app->player.inventory.ammo;
}
