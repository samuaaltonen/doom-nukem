/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 13:50:07 by ssulkuma          #+#    #+#             */
/*   Updated: 2022/12/06 14:18:02 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * Renders the sector specific information on the help menu sidebar.
*/
static void	sector_edit_menu(t_app *app, t_point screen_pos)
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
	render_sector_info(app, screen_pos);
}

/**
 * Renders player specific information on the help menu sidebar.
*/
static void	player_edit_menu(t_app *app)
{
	change_font(app, 15, TEXT);
	render_text(app, (t_rect){10, 40, 50, 20}, "WEAPONS");
	change_font(app, 11, TEXT);
	render_weapons(app);
	if (app->player.armor < 1)
		app->player.armor = 1;
	if (app->player.armor > 200)
		app->player.armor = 200;
	change_font(app, 15, TEXT);
	render_text(app, (t_rect){10, 165, 50, 20}, "ARMOR");
	render_text(app, (t_rect){112, 165, 50, 20}, ft_itoa(app->player.armor));
	render_text(app, (t_rect){140, 165, 80, 20}, " / 200");
	change_font(app, 11, TEXT);
	render_text(app, (t_rect){25, 187, 50, 20}, "<");
	render_text(app, (t_rect){250, 187, 50, 20}, ">");
	render_statusbar(app, (t_point){39, 185}, app->player.armor, TEXT);
	if (app->player.health < 1)
		app->player.health = 1;
	if (app->player.health > 200)
		app->player.health = 200;
	change_font(app, 15, TEXT);
	render_text(app, (t_rect){10, 225, 50, 20}, "HEALTH");
	render_text(app, (t_rect){112, 225, 50, 20}, ft_itoa(app->player.health));
	render_text(app, (t_rect){140, 225, 80, 20}, " / 200");
	change_font(app, 11, TEXT);
	render_text(app, (t_rect){25, 247, 50, 20}, "<");
	render_text(app, (t_rect){250, 247, 50, 20}, ">");
	render_statusbar(app, (t_point){39, 245}, app->player.health, ACTIVE_TEXT);
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
	render_icons(app, (t_point){25, 60}, app->current_object->type,
		app->assets.sprite);
	render_object_statics(app);
}

/**
 * Renders wall specific information on the help menu sidebar.
*/
static void	wall_edit_menu(t_app *app, t_point screen_pos)
{
	int		index;

	toggle_active_color(app, 1, "WALL", (t_rect){125, 32, 200, 15});
	render_arrows(app, (t_point){12, 70}, (t_point){265, 70});
	render_icons(app, (t_point){25, 60}, app->active->tex, app->assets.sprite);
	render_text(app, (t_rect){122, 122, 200, 15}, "DECOR");
	render_up_and_down_arrows(app, (t_point){263, 160}, (t_point){10, 165}, 8);
	render_icons(app, (t_point){25, 150}, app->active->decor, app->assets.sprite);
	if (app->active->decor != -1)
	{
		index = find_decor_interaction(app);
		render_current_interaction_status(app, screen_pos, 220, index);
		toggle_active_color(app, app->decor_edit, "DECOR OFFSET",
			(t_rect){25, 270, 200, 20});
		render_text(app, (t_rect){25, 285, 260, 100}, "ACTIVATE DECOR OFFSET \
WITH 'G' AND USE ARROW KEYS TO CHANGE. \n \n  X\n  Y");
		render_text(app, (t_rect){60, 322, 50, 15},
			ft_ftoa(app->active->decor_offset.x, 4));
		render_text(app, (t_rect){60, 337, 50, 15},
			ft_ftoa(app->active->decor_offset.y, 4));
	}
}

void	render_current_interaction_status(t_app *app, t_point screen_pos, int y, int id)
{
	if (id > -1 && app->interactions[id].event_id != 0)
		{
			if (app->interactions[id].event_id == 1)
				render_text(app, (t_rect){100, y, 200, 20}, "FLOOR HEIGHT");
			if (app->interactions[id].event_id == 2)
				render_text(app, (t_rect){90, y, 200, 20}, "CEILING HEIGHT");
			if (app->interactions[id].event_id == 3)
				render_text(app, (t_rect){50, y, 220, 20}, "FLOOR AND CEILING HEIGHT");
			if (app->interactions[id].event_id == 4)
				render_text(app, (t_rect){125, y, 200, 20}, "LIGHT");
			if (app->interactions[id].event_id == 5)
				render_text(app, (t_rect){110, y, 200, 20}, "TEXT POP-UP");
			if (app->interactions[id].event_id == 6)
				render_text(app, (t_rect){125, y, 200, 20}, "SOUND");
			if (app->interactions[id].event_id == 7)
				render_text(app, (t_rect){102, y, 200, 20}, "END LEVEL");
			render_ui_frame(app, (t_rect){47, y + 18, 190, 16}, 1, 0);
			render_interaction_button(app, (t_rect){80, y + 20, 200, 20},
				screen_pos, "EDIT INTERACTION");
		}
		else
		{
			render_text(app, (t_rect){85, y, 200, 20}, "NO INTERACTION");
			render_ui_frame(app, (t_rect){42, y + 18, 190, 16}, 1, 0);
			render_interaction_button(app, (t_rect){80, y + 20, 200, 20},
				screen_pos, "ADD INTERACTION");
		}
}

/**
 * Renders the help menu texts on the help menu.
*/
static void	help_menu_texts(t_app *app)
{
	int		y;
	t_point	screen_pos;

	y = 40;
	SDL_GetMouseState(&screen_pos.x, &screen_pos.y);
	change_font(app, 20, TEXT);
	render_text(app, (t_rect){10, 10, 260, 20}, "LEVEL EDITOR");
	change_font(app, 11, TEXT);
	if (app->active_sector && !app->active && !app->object_menu && !app->interaction_menu)
		sector_edit_menu(app, screen_pos);
	else if (app->active && !app->interaction_menu && !app->object_menu
		&& !app->list_creation)
		wall_edit_menu(app, screen_pos);
	else if (app->interaction_menu)
		render_interaction_texts(app, 40);
	else if (app->player_menu)
		player_edit_menu(app);
	else if (app->object_menu)
		object_edit_menu(app);
	else
	{
		if (!app->imported && !app->sectors)
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
