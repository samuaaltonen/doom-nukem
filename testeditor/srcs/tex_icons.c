/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex_icons.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 15:36:43 by ssulkuma          #+#    #+#             */
/*   Updated: 2022/11/18 14:47:10 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * Toggles the color of the wall, floor and ceiling header based on,
 * if they're active or not.
*/
void	toggle_active_color(t_app *app, int active, char *text, t_point point)
{
	load_font(app);
	if (active == 1)
	{
		change_font(app, 15, ACTIVE_TEXT);
		render_text(app, point, text);
	}
	else if (active == 2)
	{
		change_font(app, 15, 0xFFFF00FF);
		render_text(app, point, text);
	}
	else
	{
		change_font(app, 15, TEXT);
		render_text(app, point, text);
	}
	change_font(app, 15, TEXT);
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
	t_rect		src;
	t_rect		wall_icon;
	t_rect		floor_icon;
	t_rect		ceiling_icon;

	if (app->active)
		set_icon_rect(&src, (t_point){(ICON_SIZE * app->active->tex), 0}, (t_point){ICON_SIZE, ICON_SIZE});
	else
		set_icon_rect(&src, (t_point){(ICON_SIZE
				* app->active_sector->wall_list->tex), 0}, (t_point){ICON_SIZE, ICON_SIZE});
	set_icon_rect(&wall_icon, (t_point){22, 420}, (t_point){ICON_SIZE, ICON_SIZE});
	blit_surface(app->assets.sprite, &src, app->surface, &wall_icon);
	set_icon_rect(&src, (t_point){(ICON_SIZE
			* app->active_sector->floor_tex), 0}, (t_point){ICON_SIZE, ICON_SIZE});
	set_icon_rect(&floor_icon, (t_point){108, 420}, (t_point){ICON_SIZE, ICON_SIZE});
	blit_surface(app->assets.sprite, &src, app->surface, &floor_icon);
	set_icon_rect(&src, (t_point){(ICON_SIZE
			* app->active_sector->ceil_tex), 0}, (t_point){ICON_SIZE, ICON_SIZE});
	set_icon_rect(&ceiling_icon, (t_point){194, 420}, (t_point){ICON_SIZE, ICON_SIZE});
	blit_surface(app->assets.sprite, &src, app->surface, &ceiling_icon);
}

/**
 * Renders wall, floor and ceiling texture icons when a sector is selected.
*/
void	render_texture_icons(t_app *app)
{
	if (app->active_sector)
	{
		if (app->active)
			toggle_active_color(app, 2, "WALL", (t_point){32, 400});
		else
			toggle_active_color(app, app->wall_edit, "WALL",
				(t_point){32, 400});
		toggle_active_color(app, app->floor_edit, "FLOOR", (t_point){113, 400});
		toggle_active_color(app, app->ceiling_edit, "CEILING",
			(t_point){190, 400});
		place_texture_icons(app);
	}
}
