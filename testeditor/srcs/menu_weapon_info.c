/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_weapon_info.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:32:37 by ssulkuma          #+#    #+#             */
/*   Updated: 2022/11/23 10:57:33 by ssulkuma         ###   ########.fr       */
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
 * Renders weapon related texts on the help menu sidebar.
*/
static void	render_weapon_texts(t_app *app)
{
	render_text(app, (t_rect){40, 102, 100, 15}, "DAMAGE");
	render_text(app, (t_rect){220, 102, 100, 15},
		ft_itoa(app->player.weapons[app->player.selected_weapon].damage));
	render_text(app, (t_rect){40, 115, 100, 15}, "RANGE");
	render_text(app, (t_rect){220, 115, 100, 15},
		ft_itoa(app->player.weapons[app->player.selected_weapon].range));
	render_text(app, (t_rect){40, 128, 100, 15}, "RPS");
	render_text(app, (t_rect){220, 128, 100, 15},
		ft_itoa(app->player.weapons[app->player.selected_weapon].fire_rate));
	render_text(app, (t_rect){40, 141, 100, 15}, "MAGAZINE");
	render_text(app, (t_rect){120, 141, 100, 15},
		ft_itoa(app->player.weapons[app->player.selected_weapon].magazine));
}

/**
* Renders weapon staticbars on the help menu sidebar.
*/
void	render_weapon_statics(t_app *app)
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
			if (x < app->player.weapons[app->player.selected_weapon].range
				+ 120 && y > 126 && y < 136)
				put_pixel_to_surface(app->surface, x, y, TEXT);
			x++;
		}
		y++;
	}
	render_weapon_texts(app);
}
