/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equipment_control.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 21:05:44 by htahvana          #+#    #+#             */
/*   Updated: 2023/02/08 18:30:41 by htahvana         ###   ########.fr       */
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

void	weapon(t_app *app, SDL_Keycode keycode)
{
	int	weapon;

	weapon = 0;
	if (keycode == SDLK_1)
		weapon = 0;
	if (keycode == SDLK_2)
		weapon = 1;
	if (keycode == SDLK_3)
		weapon = 2;
	if (app->player.weapons & 0b00000001 && weapon == 0)
		app->hand.equipped = 1;
	else if (app->player.weapons & 0b00000010 && weapon == 1)
		app->hand.equipped = 2;
	else if (app->player.weapons & 0b00000100 && weapon == 2)
		app->hand.equipped = 3;
	if (app->hand.equipped == 0)
		return ;
	app->player.equipped_weapon.type = app->weapons_def[weapon].type;
	app->player.equipped_weapon.magazine = app->weapons_def[weapon].magazine;
	app->player.equipped_weapon.fire_rate = app->weapons_def[weapon].fire_rate;
	start_timer(&app->shoot_timer, 2.0f);
	if (app->player.equipped_weapon.magazine <= app->player.inventory.ammo)
		app->player.equipped_weapon.ammo = app->player.equipped_weapon.magazine;
	else
		app->player.equipped_weapon.ammo = app->player.inventory.ammo;
}
