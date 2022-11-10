/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 13:50:07 by ssulkuma          #+#    #+#             */
/*   Updated: 2022/11/08 16:07:45 by ssulkuma         ###   ########.fr       */
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
// static void	player_edit_menu(t_app *app)
// {
// 	toggle_active_color(app, app->player_edit, "PLAYER", (t_point){10, 320});
// 	render_text(app, (t_point){100, 310}, ft_ftoa(app->player.position.x, 2));
// 	render_text(app, (t_point){100, 330}, ft_ftoa(app->player.position.y, 2));
// }

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
	// else if ()
	// 	player_edit_menu(app);
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
}
