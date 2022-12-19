/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_weapon_info.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:32:37 by ssulkuma          #+#    #+#             */
/*   Updated: 2022/12/19 16:12:59 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * Sets weapon values. [0] lasergun, [1] bow, [2] shotgun, [3] machinegun,
 * [4] grenade.
*/
void	weapons_init(t_app *app)
{
	app->player.weapons[0].damage = 5;
	app->player.weapons[0].range = 5;
	app->player.weapons[0].fire_rate = 5;
	app->player.weapons[0].magazine = 10;
	app->player.weapons[1].damage = 50;
	app->player.weapons[1].range = 15;
	app->player.weapons[1].fire_rate = 1;
	app->player.weapons[1].magazine = 1;
	app->player.weapons[2].damage = 30;
	app->player.weapons[2].range = 2;
	app->player.weapons[2].fire_rate = 2;
	app->player.weapons[2].magazine = 6;
	app->player.weapons[3].damage = 60;
	app->player.weapons[3].range = 10;
	app->player.weapons[3].fire_rate = 1;
	app->player.weapons[3].magazine = 3;
	app->player.weapons[4].damage = 8;
	app->player.weapons[4].range = 12;
	app->player.weapons[4].fire_rate = 25;
	app->player.weapons[4].magazine = 20;
}

/**
 * Renders weapon related texts on the help menu sidebar when player edit
 * mode is turned on.
*/
static void	render_weapon_texts(t_app *app)
{
	char	*statics;

	render_text(app, (t_rect){40, 102, 100, 15}, "DAMAGE");
	statics = ft_itoa(app->player.weapons[app->player.selected_weapon].damage);
	render_text(app, (t_rect){220, 102, 100, 15}, statics);
	free(statics);
	render_text(app, (t_rect){40, 115, 100, 15}, "RANGE");
	statics = ft_itoa(app->player.weapons[app->player.selected_weapon].range);
	render_text(app, (t_rect){220, 115, 100, 15}, statics);
	free(statics);
	render_text(app, (t_rect){40, 128, 100, 15}, "RPS");
	statics = ft_itoa(app->player.weapons[app->player.selected_weapon].fire_rate);
	render_text(app, (t_rect){220, 128, 100, 15}, statics);
	free(statics);
	render_text(app, (t_rect){40, 141, 100, 15}, "MAGAZINE");
	statics = ft_itoa(app->player.weapons[app->player.selected_weapon].magazine);
	render_text(app, (t_rect){120, 141, 100, 15}, statics);
	free(statics);
}

/**
* Renders weapon staticbars on the help menu sidebar when player edit mode
 * is turned on.
*/
static void	render_weapon_statics(t_app *app)
{
	int		x;
	int		y;

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
	render_weapon_texts(app);
}

/**
 * Renders the weapon icons and selection frame around the icon if the weapon
 * is enabled.
*/
void	render_weapons(t_app *app)
{
	int		index;

	render_player_icons(app, app->assets.sprite,
		(t_point){40, 60}, MAX_WEAPONS + 1);
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
 * If left mouse click is within the icon rectangles, toggles the weapon's
 * selection on/off.
*/
void	select_weapons(t_app *app, t_point screen_pos)
{
	int	index;

	index = 0;
	while (index < MAX_WEAPONS)
	{
		if (check_mouse(screen_pos, (t_rect){(SMALL_ICON) * (index + 1)
				+ (10 * (index + 1)) - 3, 60, 35, 35}))
			app->player.weapons[index].enabled
				= ft_toggle(app->player.weapons[index].enabled);
		index++;
	}
}
