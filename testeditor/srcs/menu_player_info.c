/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_player_info.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 14:56:05 by ssulkuma          #+#    #+#             */
/*   Updated: 2022/11/15 13:52:44 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
* Renders weapon, armor and inventory icons on the help menu sidebar.
*/
void	render_icons(t_app *app, SDL_Surface *asset, t_point point, int max)
{
	t_rect		src;
	t_rect		icon;
	int			index;

	index = 1;
	while (index <= max)
	{
		set_icon_rect(&src, (t_point){ICON_SIZE * index, 0},
				(t_point){ICON_SIZE / 2, ICON_SIZE / 2});
		set_icon_rect(&icon, point, (t_point){ICON_SIZE / 2, ICON_SIZE / 2});
		blit_surface(asset, &src, app->surface, &icon);
		point.x += (ICON_SIZE / 2) + 10;
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
		toggle_active_color(app, 1, "<", left);
	else
		toggle_active_color(app, 0, "<", left);
	if ((right.x - 5) < screen_pos.x && (right.x + 10) > screen_pos.x
		&& right.y < screen_pos.y && (right.y + 10) > screen_pos.y)
		toggle_active_color(app, 1, ">", right);
	else
		toggle_active_color(app, 0, ">", right);
}

/**
* Renders player healthbar on the help menu sidebar.
*/
void	render_healthbar(t_app *app)
{
	int		x;
	int		y;
	
	y = 280;
	while (y <= 300)
	{
		x = 39;
		while (x <= 240)
		{
			if (y == 280 || y == 300 || x == 39 || x == 240)
				put_pixel_to_surface(app->surface, x, y, 0x000000);
			else if (x < (app->player.health + 40))
				put_pixel_to_surface(app->surface, x, y, 0x00FF00);
			x++;
		}
		y++;
	}
}

/**
* Renders weapon and armor staticbars on the help menu sidebar.
*/
// void	render_statics(t_app *app)
// {
	
// }
