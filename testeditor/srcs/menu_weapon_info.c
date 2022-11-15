/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_weapon_info.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:32:37 by ssulkuma          #+#    #+#             */
/*   Updated: 2022/11/15 16:39:51 by ssulkuma         ###   ########.fr       */
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
	change_font(app, 11, TEXT);
	render_text(app, (t_point){40, 100}, "DAMAGE");
	render_text(app, (t_point){220, 100},
		ft_itoa(app->player.weapons[app->player.selected_weapon - 1].damage));
	render_text(app, (t_point){40, 115}, "RANGE");
	render_text(app, (t_point){220, 115},
		ft_itoa(app->player.weapons[app->player.selected_weapon - 1].range));
	render_text(app, (t_point){40, 130}, "RPS");
	render_text(app, (t_point){220, 130},
		ft_itoa(app->player.weapons[app->player.selected_weapon - 1].fire_rate));
	render_text(app, (t_point){40, 145}, "MAGAZINE");
	render_text(app, (t_point){120, 145},
		ft_itoa(app->player.weapons[app->player.selected_weapon - 1].magazine));
	change_font(app, 15, TEXT);
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
			if (x < app->player.weapons[app->player.selected_weapon - 1].damage
				+ 120 && y < 110)
				put_pixel_to_surface(app->surface, x, y, 0x000000);
			if (x < app->player.weapons[app->player.selected_weapon - 1].range
				+ 120 && y > 113 && y < 123)
				put_pixel_to_surface(app->surface, x, y, 0x000000);
			if (x < app->player.weapons[app->player.selected_weapon - 1].range
				+ 120 && y > 126 && y < 136)
				put_pixel_to_surface(app->surface, x, y, 0x000000);
			x++;
		}
		y++;
	}
	render_weapon_texts(app);
}
