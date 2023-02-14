/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_weapon_info.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:32:37 by ssulkuma          #+#    #+#             */
/*   Updated: 2023/02/14 15:57:40 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * @brief Sets weapon values. [0] lasergun, [1] bow, [2] shotgun,
 * [3] machinegun, [4] grenade.
 * 
 * @param app
*/
void	weapons_init(t_app *app)
{
	app->player.weapons[0].damage = 30;
	app->player.weapons[0].range = 12;
	app->player.weapons[0].fire_rate = 3;
	app->player.weapons[0].magazine = 7;
	app->player.weapons[1].damage = 40;
	app->player.weapons[1].range = 12;
	app->player.weapons[1].fire_rate = 1;
	app->player.weapons[1].magazine = 16;
	app->player.weapons[2].damage = 20;
	app->player.weapons[2].range = 12;
	app->player.weapons[2].fire_rate = 4;
	app->player.weapons[2].magazine = 1;
}

/**
 * @brief Renders weapon related texts on the help menu sidebar when player edit
 * mode is turned on.
 * 
 * @param app
 * @param stats
*/
static void	render_weapon_texts(t_app *app, char *stats)
{
	render_text(app, (t_rect){40, 102, 100, 15}, "DAMAGE");
	stats = ft_itoa(app->player.weapons[app->player.selected_weapon].damage);
	if (!stats)
		return ;
	render_text(app, (t_rect){220, 102, 100, 15}, stats);
	free(stats);
	render_text(app, (t_rect){40, 115, 100, 15}, "RANGE");
	stats = ft_itoa(app->player.weapons[app->player.selected_weapon].range);
	if (!stats)
		return ;
	render_text(app, (t_rect){220, 115, 100, 15}, stats);
	free(stats);
	render_text(app, (t_rect){40, 128, 100, 15}, "RPS");
	stats = ft_itoa(app->player.weapons[app->player.selected_weapon].fire_rate);
	if (!stats)
		return ;
	render_text(app, (t_rect){220, 128, 100, 15}, stats);
	free(stats);
	render_text(app, (t_rect){40, 141, 100, 15}, "MAGAZINE");
	stats = ft_itoa(app->player.weapons[app->player.selected_weapon].magazine);
	if (!stats)
		return ;
	render_text(app, (t_rect){120, 141, 100, 15}, stats);
	free(stats);
}

/**
 * @brief Renders weapon staticbars on the help menu sidebar when player
 * edit mode is turned on.
 * 
 * @param app
*/
static void	render_weapon_statics(t_app *app)
{
	int		x;
	int		y;
	char	*stats;

	stats = NULL;
	y = 100;
	while (y < 150)
	{
		x = 120;
		while (x < 220)
		{
			if (x < app->player.weapons[app->player.selected_weapon].damage
				+ 120 && y < 110)
				put_pixel_to_surface(app->surface, x, y, TEXT);
			if (x < app->player.weapons[app->player.selected_weapon].range
				+ 120 && y > 113 && y < 123)
				put_pixel_to_surface(app->surface, x, y, TEXT);
			if (x < app->player.weapons[app->player.selected_weapon].fire_rate
				+ 120 && y > 126 && y < 136)
				put_pixel_to_surface(app->surface, x, y, TEXT);
			x++;
		}
		y++;
	}
	render_weapon_texts(app, stats);
}

/**
 * @brief Renders the weapon icons and selection frame around the icon if
 * the weapon is enabled.
 * 
 * @param app
*/
void	render_weapons(t_app *app)
{
	int		index;

	render_player_icons(app, app->assets.objects,
		(t_point){40, 60}, MAX_WEAPONS);
	index = 0;
	while (index < MAX_WEAPONS)
	{
		if (app->player.weapons[index].enabled)
		{
			render_ui_frame(app, (t_rect){(SMALL_ICON) * (index + 1)
				+ (10 * (index + 1)) - 3, 59, 35, 35}, 1, 0);
		}
		index++;
	}
	render_weapon_statics(app);
}

/**
 * @brief If left mouse click is within the icon rectangles, toggles the
 * weapon's selection on/off.
 * 
 * @param app
 * @param mouse
*/
void	select_weapons(t_app *app, t_point mouse)
{
	int	index;

	index = 0;
	while (index < MAX_WEAPONS)
	{
		if (check_mouse(mouse, (t_rect){(SMALL_ICON) * (index + 1)
				+ (10 * (index + 1)) - 3, 60, 35, 35}))
			app->player.weapons[index].enabled
				= ft_toggle(app->player.weapons[index].enabled);
		index++;
	}
}
