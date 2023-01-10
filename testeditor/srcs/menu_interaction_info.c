/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_interaction_info.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 14:45:38 by ssulkuma          #+#    #+#             */
/*   Updated: 2023/01/10 15:35:46 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * Displays the name of the interaction and edit interaction button.
*/
static void	has_interaction(t_app *app, t_point screen_pos, int y, int id)
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
		render_text(app, (t_rect){105, y, 200, 20}, "TEXT POP-UP");
	if (app->interactions[id].event_id == 6)
		render_text(app, (t_rect){125, y, 200, 20}, "SOUND");
	if (app->interactions[id].event_id == 7)
		render_text(app, (t_rect){102, y, 200, 20}, "END LEVEL");
	render_ui_frame(app, (t_rect){47, y + 18, 190, 16}, 1, 0);
	render_interaction_button(app, (t_rect){80, y + 20, 200, 20},
		screen_pos, "EDIT INTERACTION");
	render_ui_frame(app, (t_rect){47, y + 43, 190, 16}, 1, 0);
	render_interaction_button(app, (t_rect){80, y + 45, 200, 20},
		screen_pos, "ADD INTERACTION");
	render_arrows(app, (t_point){25, y}, (t_point){255, y});
}

/**
 * Displays the interaction on the selected object/wall/sector and button
 * to the interaction menu.
*/
void	render_current_interaction_status(t_app *app, t_point screen_pos,
																int y, int id)
{
	if (id > -1 && app->interactions[id].event_id != 0)
		has_interaction(app, screen_pos, y, id);
	else
	{
		render_text(app, (t_rect){80, y, 200, 20}, "NO INTERACTIONS");
		render_ui_frame(app, (t_rect){42, y + 18, 190, 16}, 1, 0);
		render_interaction_button(app, (t_rect){80, y + 20, 200, 20},
			screen_pos, "ADD INTERACTION");
	}
}

/**
 * Renders interaction menu buttons, toggling the color of them.
*/
void	render_interaction_button(t_app *app, t_rect button,
									t_point mouse, char *text)
{
	if (mouse.x > button.x && mouse.x < button.x + button.w
		&& mouse.y > button.y && mouse.y < button.y + button.h)
		change_font(app, 11, ACTIVE_TEXT);
	render_text(app, (t_rect){button.x, button.y, button.x + button.w,
		button.y + button.h}, text);
	change_font(app, 11, TEXT);
}

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
	change_font(app, 11, TEXT);
	if (app->current_interaction)
	{
		render_interaction_explanations(app, start_y);
		render_ui_frame(app, (t_rect){60, start_y + 297, 170, 16}, 1, 0);
		render_link_interaction_info(app, start_y, screen_pos);
		render_interaction_button(app, (t_rect){85, start_y + 300, 150, 15},
			screen_pos, "SAVE INTERACTION");
	}
}
