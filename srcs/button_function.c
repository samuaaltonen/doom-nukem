/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_function.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <danielmdc94@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 12:05:46 by dpalacio          #+#    #+#             */
/*   Updated: 2023/01/25 16:25:15 by dpalacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

void	button_function(t_app *app, t_rect button, void (*f)(t_app *app))
{
	if (check_mouse(app, button))
	{
		if (app->conf->buttonstates & LEFT_MOUSE)
			start_timer(&app->button_timer, 0.5);
		else if (!(app->conf->buttonstates & LEFT_MOUSE)
			&& !check_timer(&app->button_timer))
		{
			f(app);
			start_timer(&app->button_timer, 0.0);
		}	
	}
}

void	start_game(t_app *app)
{
	player_init(app);
	init_enemies(app);
	init_bullets(app);
	//----DEBUG FEATURE
	app->player.weapons = 0;
	app->player.equipped_weapon.magazine = 9;
	if (app->player.equipped_weapon.magazine <= app->player.inventory.ammo)
		app->player.equipped_weapon.ammo = app->player.equipped_weapon.magazine;
	else
		app->player.equipped_weapon.ammo = app->player.inventory.ammo;
	app->player.equipped_weapon.fire_rate = 0.2;
	//----
	app->status = STATUS_GAME;
}

void	exit_game(t_app *app)
{
	if (app)
		exit(EXIT_SUCCESS);
}
