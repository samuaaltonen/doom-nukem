/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_player_info.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 14:56:05 by ssulkuma          #+#    #+#             */
/*   Updated: 2022/11/24 15:55:47 by htahvana         ###   ########.fr       */
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
* Renders player healthbar on the help menu sidebar.
*/
void	render_healthbar(t_app *app)
{
	int		x;
	int		y;
	
	y = 285;
	while (y <= 305)
	{
		x = 39;
		while (x <= 240)
		{
			if (y == 285 || y == 305 || x == 39 || x == 240)
				put_pixel_to_surface(app->surface, x, y, TEXT);
			else if (x < (app->player.health + 40))
				put_pixel_to_surface(app->surface, x, y, PLAYER);
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
	if (app->selected[1] && key == SDLK_LEFT
		&& app->player.inventory.potion > 1)
		app->player.inventory.potion--;
	if (app->selected[2] && key == SDLK_LEFT
		&& app->player.inventory.antidote > 1)
		app->player.inventory.antidote--;
	if (app->selected[1] && key == SDLK_RIGHT
		&& app->player.inventory.potion < 10)
		app->player.inventory.potion++;
	if (app->selected[2] && key == SDLK_RIGHT
		&& app->player.inventory.antidote < 10)
		app->player.inventory.antidote++;
}
