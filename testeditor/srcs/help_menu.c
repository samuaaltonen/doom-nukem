/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 13:50:07 by ssulkuma          #+#    #+#             */
/*   Updated: 2022/11/15 14:29:08 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * Renders the sector specific information on the help menu sidebar.
*/
static void	sector_edit_menu(t_app *app)
{
	change_font(app, 15, TEXT);
	render_text(app, (t_point){10, 40}, "TOGGLE ALL WALLS ( V )");
	render_text(app, (t_point){10, 60}, "TOGGLE FLOOR ( F )");
	render_text(app, (t_point){10, 80}, "TOGGLE CEILING ( R )");
	render_text(app, (t_point){10, 100}, "TOGGLE LIGHT ( T )");
	render_text(app, (t_point){10, 120}, "TOGGLE SLOPE ( U )");
	render_text(app, (t_point){10, 150}, "TEX ( LEFT / RIGHT )");
	render_text(app, (t_point){10, 170}, "HEIGHT ( UP / DOWN )");
	toggle_active_color(app, app->portal_selection, "CREATE PORTAL ( L )",
		(t_point){10, 200});
	render_text(app, (t_point){10, 220}, "SELECT WALL TO CREATE");
	render_text(app, (t_point){10, 240}, "PORTAL, PRESS 'L', SELECT");
	render_text(app, (t_point){10, 260}, "SECTOR TO LINK PORTAL TO,");
	render_text(app, (t_point){10, 280}, "PRESS 'L' AGAIN.");
	render_text(app, (t_point){10, 300}, "DOUBLE PRESS 'L' TO");
	render_text(app, (t_point){10, 320}, "REMOVE PORTAL.");
	render_text(app, (t_point){10, 350}, "CREATE SLOPE ( Y / H )");
	render_text(app, (t_point){10, 370}, "DELETE SECTOR ( DEL )");
	render_texture_icons(app);
	render_sector_info(app);
}

/**
 * Renders player specific information on the help menu sidebar.
*/
static void	player_edit_menu(t_app *app)
{
	change_font(app, 15, TEXT);
	render_text(app, (t_point){10, 40}, "WEAPONS");
	render_arrows(app, (t_point){25, 67}, (t_point){250, 67});
	render_icons(app, app->assets.sprite, (t_point){40, 60}, MAX_WEAPONS);
	color_surface(app->assets.ui_frame, ACTIVE_TEXT);
	render_ui_frame(app, (t_rect){(ICON_SIZE / 2) * app->player.selected_weapon
		+ (10 * app->player.selected_weapon) - 3, 59, 35, 35}, 1, 0);
	render_text(app, (t_point){10, 160}, "ARMOR");
	render_arrows(app, (t_point){25, 187}, (t_point){250, 187});
	render_icons(app, app->assets.sprite, (t_point){40, 180}, MAX_ARMOR);
	render_ui_frame(app, (t_rect){(ICON_SIZE / 2) * app->player.selected_armor
		+ (10 * app->player.selected_armor) - 3, 179, 35, 35}, 1, 0);
	render_text(app, (t_point){10, 260}, "HEALTH");
	if (app->player.health < 1)
		app->player.health = 1;
	if (app->player.health > 200)
		app->player.health = 200;
	render_text(app, (t_point){112, 260}, ft_itoa(app->player.health));
	render_text(app, (t_point){140, 260}, " / 200");
	render_text(app, (t_point){25, 282}, "<");
	render_healthbar(app);
	render_text(app, (t_point){250, 282}, ">");
	render_text(app, (t_point){10, 320}, "START INVENTORY");
	render_icons(app, app->assets.sprite, (t_point){40, 340}, 5);
	render_icons(app, app->assets.sprite, (t_point){40, 380}, 5);
	toggle_active_color(app, app->player_edit, "PLAYER", (t_point){10, 450});
	render_text(app, (t_point){100, 440}, ft_ftoa(app->player.position.x, 3));
	render_text(app, (t_point){100, 460}, ft_ftoa(app->player.position.y, 3));
	change_font(app, 11, TEXT);
	render_text(app, (t_point){40, 100}, "DAMAGE");
	render_text(app, (t_point){40, 115}, "RANGE");
	render_text(app, (t_point){40, 130}, "MAGAZINE");
	render_text(app, (t_point){40, 220}, "OFFENCE");
	render_text(app, (t_point){40, 235}, "DEFENCE");
}

/**
 * Renders object specific information on the help menu sidebar.
*/
// static void	object_edit_menu(t_app *app)
// {
// }

/**
 * Renders the help menu texts on the help menu.
*/
static void	help_menu_texts(t_app *app)
{
	change_font(app, 20, TEXT);
	render_text(app, (t_point){10, 10}, "LEVEL EDITOR");
	if (app->active_sector)
		sector_edit_menu(app);
	else if (app->player_menu)
		player_edit_menu(app);
	// else if ()
	// 	object_edit_menu(app);
	else
	{
		change_font(app, 15, TEXT);
		render_text(app, (t_point){10, 40}, "OPEN FILE ( O )");
		render_text(app, (t_point){10, 60}, "SAVE FILE ( M )");
		toggle_active_color(app, app->list_creation, "CREATE WALL ( C )",
			(t_point){10, 90});
		render_text(app, (t_point){10, 120}, "LEFT CLICK MOUSE TO");
		render_text(app, (t_point){10, 140}, "SELECT SECTOR. RIGHT");
		render_text(app, (t_point){10, 160}, "CLICK TO UNSELECT.");
		render_text(app, (t_point){10, 180}, "LEFT CLICK CORNER TO");
		render_text(app, (t_point){10, 200}, "SELECT WALL ON RIGHT.");
		render_text(app, (t_point){10, 230}, "DIVIDE GRID ( Z / X )");
		render_text(app, (t_point){10, 260}, "MOVE ( WASD )");
		render_text(app, (t_point){10, 280}, "ZOOM ( SCROLL )");
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
			put_pixel_to_surface(app->surface, x, y, BG_LIGHT);
			x++;
		}
		y++;
	}
	help_menu_texts(app);
	color_surface(app->assets.ui_frame, UI_FRAME);
}
