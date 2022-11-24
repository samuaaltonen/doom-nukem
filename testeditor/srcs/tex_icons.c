/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex_icons.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 15:36:43 by ssulkuma          #+#    #+#             */
/*   Updated: 2022/11/23 15:53:19 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * Toggles the color of the wall, floor and ceiling header based on,
 * if they're active or not.
*/
void	toggle_active_color(t_app *app, int active, char *text, t_rect point)
{
	if (active == 1)
		change_font(app, 11, ACTIVE_TEXT);
	else if (active == 2)
		change_font(app, 11, 0xFFFF00FF);
	else
		change_font(app, 11, TEXT);
	render_text(app, point, text);
	change_font(app, 11, TEXT);
}

/**
 * Sets correct coordinate points and size for the icon rectangles.
*/
void	set_icon_rect(t_rect *rect, t_point point, t_point size)
{
	rect->x = point.x;
	rect->y = point.y;
	rect->w = size.x;
	rect->h = size.y;
}

/**
 * Blits texture icons to the surface.
*/
static void	place_texture_icons(t_app *app)
{
	render_arrows(app, (t_point){12, 330}, (t_point){265, 330});
	if (app->active)
		render_icons(app, (t_point){25, 320}, app->active->tex,
			app->assets.sprite);
	else
		render_icons(app, (t_point){25, 320},
			app->active_sector->wall_list->tex, app->assets.sprite);
	render_arrows(app, (t_point){12, 428}, (t_point){265, 428});
	render_icons(app, (t_point){25, 418},
		app->active_sector->floor_tex, app->assets.sprite);
	render_arrows(app, (t_point){12, 526}, (t_point){265, 526});
	render_icons(app, (t_point){25, 516},
		app->active_sector->ceil_tex, app->assets.sprite);
}

/**
 * Renders wall, floor and ceiling texture icons when a sector is selected.
*/
void	render_texture_icons(t_app *app)
{
	if (app->active_sector)
	{
		if (app->active)
			toggle_active_color(app, 2, "WALL", (t_rect){125, 292, 200, 15});
		else
			toggle_active_color(app, app->wall_edit, "WALL",
				(t_rect){125, 292, 200, 15});
		toggle_active_color(app, app->floor_edit, "FLOOR", (t_rect){122, 390, 200, 15});
		toggle_active_color(app, app->ceiling_edit, "CEILING",
			(t_rect){114, 488, 200, 15});
		place_texture_icons(app);
	}
}
