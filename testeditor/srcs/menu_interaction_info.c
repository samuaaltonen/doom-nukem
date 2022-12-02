/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_interaction_info.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 14:45:38 by ssulkuma          #+#    #+#             */
/*   Updated: 2022/12/01 16:30:29 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

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

void	render_up_and_down_arrows(t_app *app, t_point up, t_point down, int size)
{
	int		x;
	int		y;
	int		index;

	y = up.y - 1;
	index = 0;
	while (++y < up.y + size)
	{
		x = up.x - 1;
		while (++x < up.x + size)
		{
			if (x <= up.x + index && x >= up.x + size - index)
				put_pixel_to_surface(app->surface, x, y, TEXT);
		}
		index++;
	}
	y = down.y - 1;
	index = 0;
	while (++y < down.y + size)
	{
		x = down.x - 1;
		while (++x < down.x + size)
		{
			if (x > down.x + index && x < down.x + size - index)
				put_pixel_to_surface(app->surface, x, y, TEXT);
		}
		index++;
	}
}

static void	render_interaction_menu(t_app *app, t_point mouse, int start_y)
{
	if (app->current_interaction)
	{
		render_ui_frame(app, (t_rect){10, start_y + 20 +
			(app->current_interaction->event_id * 15), 260, 16}, 1, 0);
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
 * For each specific interaction event, renders explanation text what it
 * changes and the variable value it changes to.
*/
static void	render_interaction_explanation(t_app *app, int start_y)
{
	if (app->current_interaction->event_id == 1)
	{
		render_text(app, (t_rect){20, start_y + 155, 270, 200},
			"INTERACTING WITH OBJECT CHANGE SELECTED SECTOR'S FLOOR HEIGHT.");
		render_text(app, (t_rect){20, start_y + 195, 100, 20},
			ft_ftoa(app->active_sector->floor_height, 4));
		render_text(app, (t_rect){140, start_y + 195, 30, 20}, ">>");
		render_text(app, (t_rect){220, start_y + 195, 100, 20},
			ft_ftoa(app->current_interaction->variable, 4));
		render_up_and_down_arrows(app, (t_point){235, 221}, (t_point){235, 251}, 8);
	}
	if (app->current_interaction->event_id == 2)
	{
		render_text(app, (t_rect){20, start_y + 155, 270, 200},
			"INTERACTING WITH OBJECT CHANGE SELECTED SECTOR'S CEILING HEIGHT.");
		render_text(app, (t_rect){20, start_y + 210, 100, 20},
			ft_ftoa(app->active_sector->ceil_height, 4));
		render_text(app, (t_rect){140, start_y + 210, 30, 20}, ">>");
		render_text(app, (t_rect){220, start_y + 210, 100, 20},
			ft_ftoa(app->current_interaction->variable, 4));
		render_up_and_down_arrows(app, (t_point){235, 236}, (t_point){235, 266}, 8);
	}
	if (app->current_interaction->event_id == 3)
	{
		render_text(app, (t_rect){20, start_y + 155, 270, 200},
			"INTERACTING WITH OBJECT CHANGE SELECTED SECTOR'S FLOOR AND \
CEILING HEIGHT.");
		render_text(app, (t_rect){20, start_y + 210, 100, 20},
			ft_ftoa(app->active_sector->floor_height, 4));
		render_text(app, (t_rect){20, start_y + 225, 100, 20},
			ft_ftoa(app->active_sector->ceil_height, 4));
		render_text(app, (t_rect){140, start_y + 218, 30, 20}, ">>");
		render_text(app, (t_rect){220, start_y + 218, 100, 20},
			ft_ftoa(app->current_interaction->variable, 4));
		render_up_and_down_arrows(app, (t_point){235, 243}, (t_point){235, 273}, 8);
	}
	if (app->current_interaction->event_id == 4)
	{
		render_text(app, (t_rect){20, start_y + 155, 270, 200},
			"INTERACTING WITH OBJECT CHANGE SELECTED SECTOR'S LIGHT LEVEL.");
		render_text(app, (t_rect){25, start_y + 195, 100, 20},
			ft_ftoa(app->active_sector->light, 1));
		render_text(app, (t_rect){140, start_y + 195, 30, 20}, ">>");
		render_text(app, (t_rect){220, start_y + 195, 100, 20},
			ft_ftoa(app->current_interaction->variable, 1));
		render_up_and_down_arrows(app, (t_point){227, 221}, (t_point){227, 251}, 8);
	}
	if (app->current_interaction->event_id == 5)
	{
		render_text(app, (t_rect){20, start_y + 155, 270, 200},
			"INTERACTING WITH OBJECT OPENS A TEXT POP-UP.");
		render_text(app, (t_rect){20, start_y + 195, 110, 20}, "LINE NUMBER");
		render_text(app, (t_rect){140, start_y + 195, 30, 20}, ">>");
		render_text(app, (t_rect){220, start_y + 195, 100, 20},
			ft_ftoa(app->current_interaction->variable, 1));
		render_up_and_down_arrows(app, (t_point){227, 221}, (t_point){227, 251}, 8);
	}
	if (app->current_interaction->event_id == 6)
	{
		render_text(app, (t_rect){20, start_y + 155, 270, 200},
			"INTERACTING WITH OBJECT PLAYS A SOUND.");
		render_text(app, (t_rect){20, start_y + 195, 110, 20}, "AUDIO TRACK");
		render_text(app, (t_rect){140, start_y + 195, 30, 20}, ">>");
		render_text(app, (t_rect){220, start_y + 195, 100, 20},
			ft_ftoa(app->current_interaction->variable, 1));
		render_up_and_down_arrows(app, (t_point){227, 221}, (t_point){227, 251}, 8);
	}
	if (app->current_interaction->event_id == 7)
	{
		render_text(app, (t_rect){20, start_y + 155, 270, 200},
			"INTERACTING WITH OBJECT ENDS THE LEVEL.");
		render_text(app, (t_rect){20, start_y + 195, 100, 20}, "END LEVEL");
		render_text(app, (t_rect){140, start_y + 195, 30, 20}, ">>");
		render_text(app, (t_rect){220, start_y + 195, 100, 20},
			ft_ftoa(app->current_interaction->variable, 1));
		render_up_and_down_arrows(app, (t_point){227, 221}, (t_point){227, 251}, 8);
	}
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
	change_font(app, 11, TEXT);
	if (app->current_interaction)
	{
		render_interaction_explanation(app, start_y);
		render_ui_frame(app, (t_rect){60, start_y + 258, 170, 16}, 1, 0);
		render_interaction_button(app, (t_rect){85, start_y + 260, 150, 15},
			mouse, "SAVE INTERACTION");
	}
}

/**
 * Loops through the interaction array to find if the active wall's decor
 * has an interaction or not. Returns array id if it finds one and
 * -1 if not.
*/
int	find_decor_interaction(t_app *app)
{
	int		index;

	index = 0;
	while (index <= app->interaction_count)
	{
		if (app->interactions[index].activation_wall == app->active
			&& app->interactions[index].activation_sector == app->active_sector)
		{
			return (index);
		}
		index++;
	}
	return (-1);
}

int	find_interaction(t_app *app)
{
	int		index;

	index = 0;
	while (index <= app->interaction_count)
	{
		if (&(app->interactions[index]) == app->current_interaction)
			return (index);
		index++;
	}
	return (-1);
}
