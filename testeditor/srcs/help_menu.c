/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 13:50:07 by ssulkuma          #+#    #+#             */
/*   Updated: 2022/11/23 15:59:33 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * Renders the sector specific information on the help menu sidebar.
*/
static void	sector_edit_menu(t_app *app)
{
	render_text(app, (t_rect){20, 40, 260, 100}, "TOGGLE ALL WALLS ( V )\nTOG\
GLE FLOOR ( F )\nTOGGLE CEILING ( R )\nTOGGLE LIGHT ( T )\nTOGGLE SLOPE ( U )");
	render_text(app, (t_rect){20, 110, 260, 50}, "TEX ( LEFT / RIGHT )\nHEIGHT\
 ( UP / DOWN )");
	toggle_active_color(app, app->portal_selection, "CREATE PORTAL ( L )",
		(t_rect){20, 145, 260, 15});
	render_text(app, (t_rect){20, 160, 260, 150}, "SELECT WALL TO CREATE PORTAL\
, PRESS 'L', SELECT SECTOR TO LINK PORTAL TO, PRESS 'L' AGAIN. DOUBLE PRESS 'L'\
 TO REMOVE PORTAL.");
	render_text(app, (t_rect){20, 235, 260, 15}, "CREATE OBJECT ( N )");
	render_text(app, (t_rect){20, 255, 260, 15}, "CREATE SLOPE ( Y / H )");
	render_text(app, (t_rect){20, 270, 260, 15}, "DELETE SECTOR ( DEL )");
	render_texture_icons(app);
	render_sector_info(app);
}

/**
 * Renders player specific information on the help menu sidebar.
*/
static void	player_edit_menu(t_app *app)
{
	change_font(app, 15, TEXT);
	render_text(app, (t_rect){10, 40, 50, 20}, "WEAPONS");
	render_arrows(app, (t_point){25, 67}, (t_point){250, 67});
	render_player_icons(app, app->assets.sprite, (t_point){40, 60}, MAX_WEAPONS + 1);
	render_ui_frame(app, (t_rect){(ICON_SIZE / 2) * (app->player.selected_weapon + 1)
		+ (10 * (app->player.selected_weapon + 1)) - 3, 59, 35, 35}, 1, 0);
	render_weapon_statics(app);
	change_font(app, 15, TEXT);
	render_text(app, (t_rect){10, 165, 50, 20}, "ARMOR");
	render_arrows(app, (t_point){25, 193}, (t_point){250, 193});
	render_player_icons(app, app->assets.sprite, (t_point){40, 185}, MAX_ARMOR + 1);
	render_ui_frame(app, (t_rect){(ICON_SIZE / 2) * (app->player.selected_armor + 1)
		+ (10 * (app->player.selected_armor + 1)) - 3, 184, 35, 35}, 1, 0);
	render_armor_statics(app);
	if (app->player.health < 1)
		app->player.health = 1;
	if (app->player.health > 200)
		app->player.health = 200;
	change_font(app, 15, TEXT);
	render_text(app, (t_rect){10, 265, 50, 20}, "HEALTH");
	render_text(app, (t_rect){112, 265, 50, 20}, ft_itoa(app->player.health));
	render_text(app, (t_rect){140, 265, 80, 20}, " / 200");
	change_font(app, 11, TEXT);
	render_text(app, (t_rect){25, 287, 50, 20}, "<");
	render_text(app, (t_rect){250, 287, 50, 20}, ">");
	render_healthbar(app);
	render_inventory(app);
}

/**
 * Renders object specific information on the help menu sidebar.
*/
static void	object_edit_menu(t_app *app)
{
	change_font(app, 15, TEXT);
	render_text(app, (t_rect){10, 40, 50, 20}, "OBJECTS");
	change_font(app, 11, TEXT);
	render_arrows(app, (t_point){10, 67}, (t_point){265, 67});
	render_icons(app, (t_point){25, 60}, 17, app->assets.sprite);
	render_object_statics(app);
}

/**
 * Renders the help menu texts on the help menu.
*/
static void	help_menu_texts(t_app *app)
{
	int	y;

	y = 40;
	change_font(app, 20, TEXT);
	render_text(app, (t_rect){10, 10, 260, 20}, "LEVEL EDITOR");
	change_font(app, 11, TEXT);
	if (app->active_sector)
		sector_edit_menu(app);
	else if (app->player_menu)
		player_edit_menu(app);
	else if (app->object_menu)
		object_edit_menu(app);
	else
	{
		if (!app->imported)
			render_text(app, (t_rect){20, y, 260, 15}, "OPEN FILE ( O )");
		render_text(app, (t_rect){20, y + 15, 260, 15}, "SAVE FILE ( M )");
		toggle_active_color(app, app->list_creation, "CREATE SECTOR ( C )",
			(t_rect){20, y + 35, 260, 15});
		render_text(app, (t_rect){20, y + 55, 260, 100}, "LEFT CLICK MOUSE TO \
SELECT SECTOR. RIGHT CLICK TO UNSELECT. LEFT CLICK CORNER TO SELECT WALL ON \
RIGHT. TO CREATE A MEMBER SECTOR, PRESS 'C' WHEN SECTOR IS SELECTED.");
		render_text(app, (t_rect){20, y + 150, 260, 15}, "DIVIDE GRID \
( Z / X )");
		render_text(app, (t_rect){20, y + 165, 260, 15}, "MOVE ( WASD )");
		render_text(app, (t_rect){20, y + 180, 250, 15}, "ZOOM ( SCROLL )");
	}
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
