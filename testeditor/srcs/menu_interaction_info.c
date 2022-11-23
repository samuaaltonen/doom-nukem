/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_interaction_info.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 14:45:38 by ssulkuma          #+#    #+#             */
/*   Updated: 2022/11/22 17:58:44 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * Renders interaction menu buttons, toggling the color of them.
*/
static void	render_interaction_button(t_app *app, t_rect button,
										t_point mouse, char *text)
{
	if (mouse.x > button.x && mouse.x < button.x + button.w
		&& mouse.y > button.y && mouse.y < button.y + button.h)
		change_font(app, 11, ACTIVE_TEXT);
	render_text(app, (t_rect){button.x, button.y, button.x + button.w, button.y + button.h}, text);
	change_font(app, 11, TEXT);
}

static void	render_interaction_menu(t_app *app, t_point mouse, int start_y)
{
	render_ui_frame(app, (t_rect){10, start_y + 20 + (app->event_id * 15),
		260, 16}, 1, 0);
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
		mouse, "SOUND");
	render_interaction_button(app, (t_rect){110, start_y + 100, 70, 15},
		mouse, "END LEVEL");
	render_interaction_button(app, (t_rect){125, start_y + 115, 40, 15},
		mouse, "LIGHT");
	render_interaction_button(app, (t_rect){102, start_y + 130, 82, 15},
		mouse, "TEXT POP-UP");
	change_font(app, 15, TEXT);
}

/**
 * Renders the interaction menu on the help menu sidebar.
*/
void	render_interaction_texts(t_app *app, int start_y)
{
	int		x;
	int		y;
	t_point	mouse;

	SDL_GetMouseState(&mouse.x, &mouse.y);
	change_font(app, 15, TEXT);
	render_text(app, (t_rect){10, start_y, 100, 20}, "INTERACTIONS");
	change_font(app, 11, TEXT);
	y = start_y + 20;
	while (y < start_y + 141)
	{
		x = 10;
		while (x < 270)
		{
			if (y == start_y + 20 || y % 15 == 0 || x == 10 || x == 269)
				put_pixel_to_surface(app->surface, x, y, TEXT);
			x++;
		}
		y++;
	}
	render_interaction_menu(app, mouse, start_y);
}
