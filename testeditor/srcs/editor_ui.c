/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_ui.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 14:09:02 by htahvana          #+#    #+#             */
/*   Updated: 2022/10/25 13:55:29 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * Draws the zoom slider to the right side of the screen.
*/
void	zoom_slider(t_app *app)
{
	int		x;
	int		y;
	int		zoom_point;

	y = app->surface->h / 4;
	zoom_point = y + (app->surface->h / 2) / 6 * app->zoom_range;
	while (y <= (app->surface->h - (app->surface->h / 4) + 10))
	{
		x = app->surface->w - 30;
		while (x <= (app->surface->w - 20))
		{
			if (x == (app->surface->w - 25) || y == app->surface->h / 4 || y == (app->surface->h - (app->surface->h / 4) + 10))
				put_pixel_to_surface(app->surface, x, y, 0xFFFFFF);
			if (y >= zoom_point && y <= zoom_point + 10)
				put_pixel_to_surface(app->surface, x, y, 0xFFFFFF);
			x++;
		}
		y++;
	}
}

void	move_divider(t_app *app, SDL_Keycode keycode)
{
	if (keycode == SDLK_z && app->divider > 0.2f)
		app->divider /= 2;
	else if (keycode == SDLK_x && app->divider < 0.75f)
		app->divider *= 2;
}

static void	help_menu_texts(t_app *app)
{
	load_font(app);
	change_font(app, 20, 0xFF111111);
	render_text(app, (t_point){10, 10}, "LEVEL EDITOR");
	change_font(app, 15, 0xFF111111);
	render_text(app, (t_point){10, 40}, "OPEN FILE ( O )");
	render_text(app, (t_point){10, 60}, "SAVE FILE ( M )");
	render_text(app, (t_point){10, 90}, "CREATE WALL ( C )");
	render_text(app, (t_point){10, 110}, "MAKE SURE TO DRAW SECTOR");
	render_text(app, (t_point){10, 130}, "CLOCKWISE. LEFT CLICK");
	render_text(app, (t_point){10, 150}, "MOUSE TO SELECT SECTOR.");
	render_text(app, (t_point){10, 170}, "RIGHT CLICK TO UNSELECT.");
	render_text(app, (t_point){10, 190}, "LEFT CLICK CORNER TO");
	render_text(app, (t_point){10, 210}, "SELECT WALL ON RIGHT.");
	render_text(app, (t_point){10, 230}, "WALL TEX ( 1 - 9 )");
	render_text(app, (t_point){10, 280}, "TOGGLE FLOOR ( F )");
	render_text(app, (t_point){10, 300}, "TOGGLE CEILING ( R )");
	render_text(app, (t_point){10, 320}, "F / C TEX ( LEFT / RIGHT )");
	render_text(app, (t_point){10, 340}, "F / C HEIGHT ( UP / DOWN )");
	render_text(app, (t_point){10, 370}, "CREATE PORTAL ( L )");
	render_text(app, (t_point){10, 390}, "SELECT WALL TO CREATE");
	render_text(app, (t_point){10, 410}, "PORTAL, PRESS 'L', SELECT");
	render_text(app, (t_point){10, 430}, "SECTOR TO LINK PORTAL TO,");
	render_text(app, (t_point){10, 450}, "PRESS 'L' AGAIN.");
	render_text(app, (t_point){10, 480}, "DIVIDE GRID ( Z / X )");
	render_text(app, (t_point){10, 510}, "MOVE ( WASD )");
	render_text(app, (t_point){10, 530}, "ZOOM ( SCROLL )");
	load_font(app);
}

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