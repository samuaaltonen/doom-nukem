/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_armor_info.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:34:07 by ssulkuma          #+#    #+#             */
/*   Updated: 2022/11/23 10:58:56 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * Sets armor values.
*/
void	armor_init(t_app *app)
{
	app->player.armor[0].defence = 20;
	app->player.armor[0].offence = 5;
	app->player.armor[1].defence = 25;
	app->player.armor[1].offence = 2;
	app->player.armor[2].defence = 30;
	app->player.armor[2].offence = 0;
	app->player.armor[3].defence = 0;
	app->player.armor[3].offence = 15;
	app->player.armor[4].defence = 10;
	app->player.armor[4].offence = 8;
}

/**
 * Renders armor related texts on the help menu sidebar.
*/
static void	render_armor_texts(t_app *app)
{
	render_text(app, (t_rect){40, 227, 50, 15}, "DEFENCE");
	render_text(app, (t_rect){220, 227, 50, 15},
		ft_itoa(app->player.armor[app->player.selected_armor].defence));
	render_text(app, (t_rect){40, 240, 50, 15}, "OFFENCE");
	render_text(app, (t_rect){220, 240, 50, 15},
		ft_itoa(app->player.armor[app->player.selected_armor].offence));
}

/**
 * Renders armor staticbars on the help menu sidebar.
*/
void	render_armor_statics(t_app *app)
{
	int		x;
	int		y;

	y = 225;
	while (y < 250)
	{
		x = 120;
		while (x < 220)
		{
			if (x < app->player.armor[app->player.selected_armor].defence
				+ 120 && y < 235)
				put_pixel_to_surface(app->surface, x, y, TEXT);
			if (x < app->player.armor[app->player.selected_armor].offence
				+ 120 && y > 238 && y < 248)
				put_pixel_to_surface(app->surface, x, y, TEXT);
			x++;
		}
		y++;
	}
	render_armor_texts(app);
}
