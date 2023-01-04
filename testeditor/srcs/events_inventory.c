/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_inventory.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 15:59:10 by ssulkuma          #+#    #+#             */
/*   Updated: 2023/01/04 15:59:41 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * Decreases the item amount of the inventory if the item is selected.
*/
static void	decrease_item_amount(t_app *app)
{
	if (app->selected[0] && app->player.inventory.ammo > 0)
		app->player.inventory.ammo--;
	if (app->selected[1] && app->player.inventory.special_ammo > 0)
		app->player.inventory.special_ammo--;
	if (app->selected[2] && app->player.inventory.potion > 0)
		app->player.inventory.potion--;
	if (app->selected[3] && app->player.inventory.antidote > 0)
		app->player.inventory.antidote--;
	if (app->selected[4] && app->player.inventory.key > 0)
		app->player.inventory.key--;
	if (app->selected[5] && app->player.inventory.jetpack > 0)
		app->player.inventory.jetpack--;
	// if (app->selected[6] && app->player.inventory.item1 > 0)
	// 	app->player.inventory.item1--;
	// if (app->selected[7] && app->player.inventory.item2 > 0)
	// 	app->player.inventory.item2--;
	// if (app->selected[8] && app->player.inventory.item3 > 0)
	// 	app->player.inventory.item3--;
	// if (app->selected[9] && app->player.inventory.item4 > 0)
	// 	app->player.inventory.item4--;
}

/**
 * Increases the item amount of the inventory if the item is selected.
*/
static void	increase_item_amount(t_app *app)
{
	if (app->selected[0] && app->player.inventory.ammo < MAX_AMMO)
		app->player.inventory.ammo++;
	if (app->selected[1] && app->player.inventory.special_ammo < MAX_AMMO)
		app->player.inventory.special_ammo++;
	if (app->selected[2] && app->player.inventory.potion < MAX_ITEM_CAPACITY)
		app->player.inventory.potion++;
	if (app->selected[3] && app->player.inventory.antidote < MAX_ITEM_CAPACITY)
		app->player.inventory.antidote++;
	if (app->selected[4] && app->player.inventory.key < MAX_ITEM_CAPACITY)
		app->player.inventory.key++;
	if (app->selected[5] && app->player.inventory.jetpack < 1)
		app->player.inventory.jetpack++;
	// if (app->selected[6] && app->player.inventory.item1 < MAX_ITEM_CAPACITY)
	// 	app->player.inventory.item1++;
	// if (app->selected[7] && app->player.inventory.item2 < MAX_ITEM_CAPACITY)
	// 	app->player.inventory.item2++;
	// if (app->selected[8] && app->player.inventory.item3 < MAX_ITEM_CAPACITY)
	// 	app->player.inventory.item3++;
	// if (app->selected[9] && app->player.inventory.item4 < MAX_ITEM_CAPACITY)
	// 	app->player.inventory.item4++;
}

/**
 * Event function to change item amount in inventory using the left and
 * right arrowkeys.
*/
void	change_item_amount(t_app *app, SDL_Keycode key)
{
	if (key == SDLK_LEFT)
		decrease_item_amount(app);
	if (key == SDLK_RIGHT)
		increase_item_amount(app);
}
