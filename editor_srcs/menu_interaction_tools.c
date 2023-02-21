/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_interaction_tools.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 11:00:43 by ssulkuma          #+#    #+#             */
/*   Updated: 2023/02/21 14:54:42 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * @brief Displays the name of the interaction and edit interaction button.
 * 
 * @param app
 * @param mouse
 * @param start_y
 * @param id
*/
static void	has_interaction(t_app *app, t_point mouse, int start_y, int id)
{
	if (app->interactions[id].event_id == 1)
		render_text(app, (t_rect){100, start_y, 200, 20}, "FLOOR HEIGHT");
	if (app->interactions[id].event_id == 2)
		render_text(app, (t_rect){90, start_y, 200, 20}, "CEILING HEIGHT");
	if (app->interactions[id].event_id == 3)
		render_text(app, (t_rect){50, start_y, 220, 20}, "FLOOR AND CEILING \
HEIGHT");
	if (app->interactions[id].event_id == 4)
		render_text(app, (t_rect){125, start_y, 200, 20}, "LIGHT");
	if (app->interactions[id].event_id == 5)
		render_text(app, (t_rect){105, start_y, 200, 20}, "TEXT POP-UP");
	if (app->interactions[id].event_id == 6)
		render_text(app, (t_rect){125, start_y, 200, 20}, "SOUND");
	if (app->interactions[id].event_id == 7)
		render_text(app, (t_rect){102, start_y, 200, 20}, "END LEVEL");
	render_ui_frame(app, (t_rect){47, start_y + 18, 190, 16}, 1, 0);
	render_interaction_button(app, (t_rect){80, start_y + 20, 200, 20},
		mouse, "EDIT INTERACTION");
	render_ui_frame(app, (t_rect){47, start_y + 43, 190, 16}, 1, 0);
	render_interaction_button(app, (t_rect){80, start_y + 45, 200, 20},
		mouse, "ADD INTERACTION");
	render_arrows(app, (t_point){25, start_y}, (t_point){255, start_y});
}

/**
 * @brief Displays the interaction on the selected object/wall/sector and button
 * to the interaction menu.
 * 
 * @param app
 * @param mouse
 * @param start_y
 * @param id
*/
void	render_current_interaction_status(t_app *app, t_point mouse,
													int start_y, int id)
{
	if (id > -1 && id < MAX_INTERACTIONS && app->interactions[id].event_id != 0)
		has_interaction(app, mouse, start_y, id);
	else
	{
		render_text(app, (t_rect){80, start_y, 200, 20}, "NO INTERACTIONS");
		render_ui_frame(app, (t_rect){42, start_y + 18, 190, 16}, 1, 0);
		render_interaction_button(app, (t_rect){80, start_y + 20, 200, 20},
			mouse, "ADD INTERACTION");
	}
}

/**
 * @brief Renders interaction menu buttons, toggling the color of them.
 * 
 * @param app
 * @param button
 * @param mouse
 * @param text
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
