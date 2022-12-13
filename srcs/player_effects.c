/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_effects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <danielmdc94@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 12:57:21 by dpalacio          #+#    #+#             */
/*   Updated: 2022/12/13 13:00:03 by dpalacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

void	heal(t_app *app)
{
	if (app->player.inventory.potion > 0 && app->player.hp < MAX_HP)
	{
		app->player.inventory.potion--;
		app->player.hp += 40;
	}
}

void	shield(t_app *app)
{
	if (app->player.inventory.antidote > 0)
	{
		app->player.inventory.antidote--;
		app->player.shield = MAX_HP;
	}
}

void	regen(t_app *app, int *value)
{
	if (check_timer(&app->regen_timer) && *value % 40 != 0)
			(*value)++;

}

void	damage(t_app *app, int dmg)
{	
	int	to_shield;
	int	to_hp;

	to_shield = (dmg * app->player.shield) / MAX_HP;
	if (to_shield < dmg / 5)
		to_shield = dmg / 5;
	to_hp = dmg - to_shield;
	app->player.shield -= to_shield;
	if (app->player.shield < 0)
		app->player.shield = 0;
	app->player.hp -= to_hp;
	if (app->player.hp < 0)
		app->player.hp = 0;
		start_timer(&app->regen_timer, 5);
}
