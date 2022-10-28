/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex_icons.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 15:36:43 by ssulkuma          #+#    #+#             */
/*   Updated: 2022/10/27 15:41:21 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * Toggles the color of the wall, floor and ceiling header based on,
 * if they're active or not.
*/
static void	toggle_active_color(t_app *app, int active, char *text, int x)
{
	load_font(app);
	if (active == 1)
	{
		change_font(app, 15, ACTIVE_TEXT);
		render_text(app, (t_point){x, 600}, text);
	}
	else if (active == 2)
	{
		change_font(app, 15, 0xFF00FFFF);
		render_text(app, (t_point){x, 600}, text);
	}
	else
	{
		change_font(app, 15, TEXT);
		render_text(app, (t_point){x, 600}, text);
	}
}

/**
 * Sets correct coordinate points and size for the icon rectangles.
*/
static void	set_icon_rect(t_rect *rect, t_point point)
{
	rect->x = point.x;
	rect->y = point.y;
	rect->w = ICON_SIZE;
	rect->h = ICON_SIZE;
}

/**
 * Renders wall, floor and ceiling texture icons when a sector is selected.
*/
void	render_texture_icons(t_app *app)
{
	t_rect		src;
	t_rect		wall_icon;
	t_rect		floor_icon;
	t_rect		ceiling_icon;

	if (app->active_sector)
	{
		if (app->active)
			toggle_active_color(app, 2, "WALL", 34);
		else
			toggle_active_color(app, app->wall_edit, "WALL", 34);
		toggle_active_color(app, app->floor_edit, "FLOOR", 108);
		toggle_active_color(app, app->ceiling_edit, "CEILING", 182);
		if (app->active)
			set_icon_rect(&src, (t_point){(ICON_SIZE * app->active->tex), 0});
		else
			set_icon_rect(&src, (t_point){(ICON_SIZE * app->active_sector->wall_list->tex), 0});
		set_icon_rect(&wall_icon, (t_point){34, 620});
		blit_surface(app->assets.sprite, &src, app->surface, &wall_icon);
		set_icon_rect(&src, (t_point){(ICON_SIZE * app->active_sector->floor_tex), 0});
		set_icon_rect(&floor_icon, (t_point){108, 620});
		blit_surface(app->assets.sprite, &src, app->surface, &floor_icon);
		set_icon_rect(&src, (t_point){(ICON_SIZE * app->active_sector->ceil_tex), 0});
		set_icon_rect(&ceiling_icon, (t_point){182, 620});
		blit_surface(app->assets.sprite, &src, app->surface, &ceiling_icon);
	}
}