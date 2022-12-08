/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_player_info.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 14:56:05 by ssulkuma          #+#    #+#             */
/*   Updated: 2022/12/08 18:09:20 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
* Renders a statusbar on the help menu sidebar.
*/
void	render_statusbar(t_app *app, t_point point, int statusbar, int color)
{
	int		x;
	int		y;

	y = point.y;
	while (y <= point.y + 20)
	{
		x = point.x;
		while (x <= point.x + 201)
		{
			if (y == point.y || y == point.y + 20
				|| x == point.x || x == point.x + 201)
				put_pixel_to_surface(app->surface, x, y, TEXT);
			else if (x < (statusbar + 40))
				put_pixel_to_surface(app->surface, x, y, color);
			x++;
		}
		y++;
	}
}

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

/**
 * Checks that the player's health and armor is between 1 - 200.
*/
static void	check_player_statusbars(t_app *app)
{
	if (app->player.armor < 1)
		app->player.armor = 1;
	if (app->player.armor > 200)
		app->player.armor = 200;
	if (app->player.health < 1)
		app->player.health = 1;
	if (app->player.health > 200)
		app->player.health = 200;
}

/**
 * Renders player specific information on the help menu sidebar.
*/
void	player_edit_menu(t_app *app)
{
	check_player_statusbars(app);
	change_font(app, 15, TEXT);
	render_text(app, (t_rect){10, 40, 50, 20}, "WEAPONS");
	change_font(app, 11, TEXT);
	render_weapons(app);
	change_font(app, 15, TEXT);
	render_text(app, (t_rect){10, 165, 50, 20}, "ARMOR");
	render_text(app, (t_rect){112, 165, 50, 20}, ft_itoa(app->player.armor));
	render_text(app, (t_rect){140, 165, 80, 20}, " / 200");
	change_font(app, 11, TEXT);
	render_text(app, (t_rect){25, 187, 50, 20}, "<");
	render_text(app, (t_rect){250, 187, 50, 20}, ">");
	render_statusbar(app, (t_point){39, 185}, app->player.armor, TEXT);
	change_font(app, 15, TEXT);
	render_text(app, (t_rect){10, 225, 50, 20}, "HEALTH");
	render_text(app, (t_rect){112, 225, 50, 20}, ft_itoa(app->player.health));
	render_text(app, (t_rect){140, 225, 80, 20}, " / 200");
	change_font(app, 11, TEXT);
	render_text(app, (t_rect){25, 247, 50, 20}, "<");
	render_text(app, (t_rect){250, 247, 50, 20}, ">");
	render_statusbar(app, (t_point){39, 245}, app->player.health, ACTIVE_TEXT);
	render_inventory(app);
}
