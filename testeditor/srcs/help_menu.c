/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 13:50:07 by ssulkuma          #+#    #+#             */
/*   Updated: 2022/11/03 13:50:45 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * Renders the help menu texts on the help menu.
*/
static void	help_menu_texts(t_app *app)
{
	change_font(app, 20, TEXT);
	render_text(app, (t_point){10, 10}, "LEVEL EDITOR");
	change_font(app, 15, TEXT);
	render_text(app, (t_point){10, 40}, "OPEN FILE ( O )");
	render_text(app, (t_point){10, 60}, "SAVE FILE ( M )");
	render_text(app, (t_point){10, 90}, "CREATE WALL ( C )");
	render_text(app, (t_point){10, 110}, "MAKE SURE TO DRAW SECTOR");
	render_text(app, (t_point){10, 130}, "CLOCKWISE. LEFT CLICK");
	render_text(app, (t_point){10, 150}, "MOUSE TO SELECT SECTOR.");
	render_text(app, (t_point){10, 170}, "RIGHT CLICK TO UNSELECT.");
	render_text(app, (t_point){10, 190}, "LEFT CLICK CORNER TO");
	render_text(app, (t_point){10, 210}, "SELECT WALL ON RIGHT.");
	render_text(app, (t_point){10, 230}, "TOGGLE ALL WALLS ( V )");
	render_text(app, (t_point){10, 280}, "TOGGLE FLOOR ( F )");
	render_text(app, (t_point){10, 300}, "TOGGLE CEILING ( R )");
	render_text(app, (t_point){10, 320}, "TEX ( LEFT / RIGHT )");
	render_text(app, (t_point){10, 340}, "F / C HEIGHT ( UP / DOWN )");
	render_text(app, (t_point){10, 370}, "CREATE PORTAL ( L )");
	render_text(app, (t_point){10, 390}, "SELECT WALL TO CREATE");
	render_text(app, (t_point){10, 410}, "PORTAL, PRESS 'L', SELECT");
	render_text(app, (t_point){10, 430}, "SECTOR TO LINK PORTAL TO,");
	render_text(app, (t_point){10, 450}, "PRESS 'L' AGAIN.");
	render_text(app, (t_point){10, 480}, "DIVIDE GRID ( Z / X )");
	render_text(app, (t_point){10, 510}, "MOVE ( WASD )");
	render_text(app, (t_point){10, 530}, "ZOOM ( SCROLL )");
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
	render_texture_icons(app);
}
