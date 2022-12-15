/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_effects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <danielmdc94@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 12:57:21 by dpalacio          #+#    #+#             */
/*   Updated: 2022/12/15 13:12:10 by dpalacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

void	heal(t_app *app)
{
	if (check_timer(&app->item_timer) && app->player.inventory.potion > 0
        && app->player.hp < MAX_HP)
	{
		app->player.inventory.potion--;
		app->player.hp += 40;
        start_timer(&app->item_timer, 5);
	}
}

void	shield(t_app *app)
{
	if (check_timer(&app->item_timer) && app->player.inventory.antidote > 0
        && app->player.shield < MAX_HP)
	{
		app->player.inventory.antidote--;
		app->player.shield = MAX_HP;
		start_timer(&app->item_timer, 5);
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
		start_timer(&app->regen_timer, REGEN_TIME);
}
