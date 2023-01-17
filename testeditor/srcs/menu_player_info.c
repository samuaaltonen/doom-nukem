/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_player_info.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 14:56:05 by ssulkuma          #+#    #+#             */
/*   Updated: 2023/01/13 15:55:43 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * @brief Renders a statusbar on the help menu sidebar.
 * 
 * @param app
 * @param point
 * @param statusbar
 * @param color
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
 * @brief Checks that the player's health and armor is between 1 - 200.
 * 
 * @param app
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
 * @brief Renders the statics that go with the health and armor statusbars.
 * 
 * @param app
*/
static void	player_statusbars(t_app *app)
{
	char	*status;

	check_player_statusbars(app);
	status = ft_itoa(app->player.armor);
	if (!status)
		return ;
	render_text(app, (t_rect){112, 165, 50, 20}, status);
	free(status);
	render_text(app, (t_rect){140, 165, 80, 20}, " / 200");
	change_font(app, 11, TEXT);
	render_text(app, (t_rect){25, 187, 50, 20}, "<");
	render_text(app, (t_rect){250, 187, 50, 20}, ">");
	render_statusbar(app, (t_point){39, 185}, app->player.armor, TEXT);
	change_font(app, 15, TEXT);
	render_text(app, (t_rect){10, 225, 50, 20}, "HEALTH");
	status = ft_itoa(app->player.health);
	if (!status)
		return ;
	render_text(app, (t_rect){112, 225, 50, 20}, status);
	free(status);
}

/**
 * @brief Renders player specific information on the help menu sidebar.
 * 
 * @param app
*/
void	player_edit_menu(t_app *app)
{
	change_font(app, 15, TEXT);
	render_text(app, (t_rect){10, 40, 50, 20}, "WEAPONS");
	change_font(app, 11, TEXT);
	render_weapons(app);
	change_font(app, 15, TEXT);
	render_text(app, (t_rect){10, 165, 50, 20}, "ARMOR");
	player_statusbars(app);
	render_text(app, (t_rect){140, 225, 80, 20}, " / 200");
	change_font(app, 11, TEXT);
	render_text(app, (t_rect){25, 247, 50, 20}, "<");
	render_text(app, (t_rect){250, 247, 50, 20}, ">");
	render_statusbar(app, (t_point){39, 245}, app->player.health, ACTIVE_TEXT);
	render_inventory(app);
}
