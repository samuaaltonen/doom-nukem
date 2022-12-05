/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_player_info.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 14:56:05 by ssulkuma          #+#    #+#             */
/*   Updated: 2022/11/25 16:56:22 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
* Renders weapon, armor and inventory icons on the help menu sidebar.
*/
void	render_player_icons(t_app *app, SDL_Surface *asset, t_point point, int max)
{
	t_rect		src;
	t_rect		icon;
	int			index;
	int			start_x;

	index = 1;
	start_x = point.x;
	while (index < max)
	{
		set_icon_rect(&src, (t_point){ICON_SIZE * index, 0},
				(t_point){ICON_SIZE / 2, ICON_SIZE / 2});
		set_icon_rect(&icon, point, (t_point){ICON_SIZE / 2, ICON_SIZE / 2});
		blit_surface(asset, &src, app->surface, &icon);
		point.x += (ICON_SIZE / 2) + 10;
		if (index % 5 == 0)
		{
			point.y += (ICON_SIZE / 2) + 10;
			point.x = start_x;
		}
		index++;
	}
}

/**
 * Renders arrows to the side of the icons on the help menu sidebar.
*/
void	render_arrows(t_app *app, t_point left, t_point right)
{
	t_point	screen_pos;

	SDL_GetMouseState(&screen_pos.x, &screen_pos.y);
	if ((left.x - 5) < screen_pos.x && (left.x + 10) > screen_pos.x
		&& left.y < screen_pos.y && (left.y + 10) > screen_pos.y)
		toggle_active_color(app, 1, "<", (t_rect){left.x, left.y, 15, 15});
	else
		toggle_active_color(app, 0, "<", (t_rect){left.x, left.y, 15, 15});
	if ((right.x - 5) < screen_pos.x && (right.x + 10) > screen_pos.x
		&& right.y < screen_pos.y && (right.y + 10) > screen_pos.y)
		toggle_active_color(app, 1, ">", (t_rect){right.x, right.y, 15, 15});
	else
		toggle_active_color(app, 0, ">", (t_rect){right.x, right.y, 15, 15});
}

/**
* Renders player statusbar on the help menu sidebar.
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
 * Event function to change item amount in inventory using the left and
 * right arrowkeys.
*/
void	change_item_amount(t_app *app, SDL_Keycode key)
{
	if (key == SDLK_LEFT)
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
	if (key == SDLK_RIGHT)
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
}
