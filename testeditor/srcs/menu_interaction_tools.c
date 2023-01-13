/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_interaction_tools.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 11:00:43 by ssulkuma          #+#    #+#             */
/*   Updated: 2023/01/13 11:14:03 by ssulkuma         ###   ########.fr       */
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
