/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 13:50:07 by ssulkuma          #+#    #+#             */
/*   Updated: 2022/12/08 17:20:04 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * The main help menu texts, shown when no specific edit mode is on.
*/
static void	main_menu(t_app *app, int y)
{
	if (!app->imported && !app->sectors)
		render_text(app, (t_rect){20, y, 260, 15}, "OPEN FILE ( O )");
	render_text(app, (t_rect){20, y + 15, 260, 15}, "SAVE FILE ( M )");
	toggle_active_color(app, app->list_creation, "CREATE SECTOR ( C )",
		(t_rect){20, y + 35, 260, 15});
	render_text(app, (t_rect){20, y + 55, 260, 100}, "LEFT CLICK MOUSE TO \
SELECT SECTOR. RIGHT CLICK TO UNSELECT. LEFT CLICK CORNER TO SELECT WALL ON \
RIGHT. TO CREATE A MEMBER SECTOR, PRESS 'C' WHEN SECTOR IS SELECTED.");
	render_text(app, (t_rect){20, y + 150, 260, 15}, "DIVIDE GRID ( Z / X )");
	render_text(app, (t_rect){20, y + 165, 260, 15}, "MOVE ( WASD )");
	render_text(app, (t_rect){20, y + 180, 250, 15}, "ZOOM ( SCROLL )");
}

/**
 * Renders the correct menu texts on the help menu sidebar depending what
 * editing mode is on.
*/
static void	help_menu_texts(t_app *app)
{
	t_point	screen_pos;

	SDL_GetMouseState(&screen_pos.x, &screen_pos.y);
	change_font(app, 20, TEXT);
	render_text(app, (t_rect){10, 10, 260, 20}, "LEVEL EDITOR");
	change_font(app, 11, TEXT);
	if (app->active_sector && !app->active && !app->object_menu
		&& !app->interaction_menu)
		sector_edit_menu(app, screen_pos, 40);
	else if (app->active && !app->interaction_menu && !app->object_menu
		&& !app->list_creation)
		wall_edit_menu(app, screen_pos);
	else if (app->interaction_menu)
		interaction_edit_menu(app, 40, screen_pos);
	else if (app->player_menu)
		player_edit_menu(app);
	else if (app->object_menu)
		object_edit_menu(app);
	else
		main_menu(app, 40);
}

/**
 * Renders the help menu sidebar to the left of the screen.
*/
void	render_help_menu(t_app *app)
{
	int		x;
	int		y;

	y = 0;
	while (y < WIN_H)
	{
		x = 0;
		while (x < HELP_MENU_W)
		{
			if (x > (HELP_MENU_W - 3) || x < 2 || y < 2 || y > (WIN_H - 3))
				put_pixel_to_surface(app->surface, x, y, TEXT);
			else
				put_pixel_to_surface(app->surface, x, y, BG_MENU);
			x++;
		}
		y++;
	}
	color_surface(app->assets.ui_frame, ACTIVE_TEXT);
	help_menu_texts(app);
	color_surface(app->assets.ui_frame, TEXT);
}
