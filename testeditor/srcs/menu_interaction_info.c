/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_interaction_info.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 14:45:38 by ssulkuma          #+#    #+#             */
/*   Updated: 2023/01/13 11:32:22 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * Renders the menu texts for the interaction menu.
*/
static void	render_interaction_menu(t_app *app, t_point mouse, int start_y)
{
	if (app->current_interaction)
	{
		render_ui_frame(app, (t_rect){10, start_y + 20
			+ (app->current_interaction->event_id * 15), 260, 16}, 1, 0);
	}
	else
		render_ui_frame(app, (t_rect){10, start_y + 20, 260, 16}, 1, 0);
	change_font(app, 11, TEXT);
	render_interaction_button(app, (t_rect){90, start_y + 25, 113, 15},
		mouse, "NO INTERACTION");
	render_interaction_button(app, (t_rect){100, start_y + 40, 93, 15},
		mouse, "FLOOR HEIGHT");
	render_interaction_button(app, (t_rect){90, start_y + 55, 110, 15},
		mouse, "CEILING HEIGHT");
	render_interaction_button(app, (t_rect){50, start_y + 70, 183, 15},
		mouse, "FLOOR AND CEILING HEIGHT");
	render_interaction_button(app, (t_rect){125, start_y + 85, 40, 15},
		mouse, "LIGHT");
	render_interaction_button(app, (t_rect){102, start_y + 100, 70, 15},
		mouse, "TEXT POP-UP");
	render_interaction_button(app, (t_rect){125, start_y + 115, 40, 15},
		mouse, "SOUND");
	render_interaction_button(app, (t_rect){110, start_y + 130, 82, 15},
		mouse, "END LEVEL");
	change_font(app, 15, TEXT);
}

/**
 * Renders the key requirement UI on the help menu side bar.
*/
static void	render_key_option(t_app *app, int start_y)
{
	change_font(app, 11, TEXT);
	render_text(app, (t_rect){20, start_y + 305, 120, 20}, "REQUIRES KEY");
	render_text(app, (t_rect){170, start_y + 305, 30, 20}, "NO");
	render_text(app, (t_rect){220, start_y + 305, 30, 20}, "YES");
	if (!app->current_interaction->requires_key)
		render_ui_frame(app, (t_rect){158, start_y + 300, 40, 20}, 1, 0);
	else
		render_ui_frame(app, (t_rect){213, start_y + 300, 40, 20}, 1, 0);
}

/**
 * Renders the interaction menu on the help menu sidebar. Draws the menu grid.
*/
void	interaction_edit_menu(t_app *app, int start_y, t_point screen_pos)
{
	int		x;
	int		y;

	change_font(app, 15, TEXT);
	render_text(app, (t_rect){10, start_y, 100, 20}, "INTERACTIONS");
	change_font(app, 11, TEXT);
	y = start_y + 19;
	while (++y < start_y + 141)
	{
		x = 9;
		while (++x < 270)
		{
			if (y == start_y + 20 || y % 15 == 0 || x == 10 || x == 269)
				put_pixel_to_surface(app->surface, x, y, TEXT);
		}
	}
	render_interaction_menu(app, screen_pos, start_y);
	render_key_option(app, start_y);
	if (!app->current_interaction)
		return ;
	render_interaction_explanations(app, start_y);
	render_ui_frame(app, (t_rect){60, start_y + 327, 170, 16}, 1, 0);
	render_link_interaction_info(app, start_y, screen_pos);
	render_interaction_button(app, (t_rect){85, start_y + 330, 150, 15},
		screen_pos, "SAVE INTERACTION");
}
