/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_interaction_tools.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 15:22:38 by ssulkuma          #+#    #+#             */
/*   Updated: 2022/12/08 17:55:32 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * Interaction explanations for event id 6 (sound) and event id 7 (end level).
*/
static void	render_interaction_explanation_4(t_app *app, int start_y)
{
	if (app->current_interaction->event_id == 6)
	{
		render_text(app, (t_rect){20, start_y + 155, 270, 200},
			"INTERACTING WITH OBJECT PLAYS A SOUND.");
		render_text(app, (t_rect){20, start_y + 195, 110, 20}, "AUDIO TRACK");
		render_text(app, (t_rect){140, start_y + 195, 30, 20}, ">>");
		render_text(app, (t_rect){220, start_y + 195, 100, 20},
			ft_ftoa(app->current_interaction->variable, 1));
		render_up_and_down_arrows(app, (t_point){227, 221},
			(t_point){227, 251}, 8);
	}
	if (app->current_interaction->event_id == 7)
	{
		render_text(app, (t_rect){20, start_y + 155, 270, 200},
			"INTERACTING WITH OBJECT ENDS THE LEVEL.");
		render_text(app, (t_rect){20, start_y + 195, 100, 20}, "END LEVEL");
		render_text(app, (t_rect){140, start_y + 195, 30, 20}, ">>");
		render_text(app, (t_rect){220, start_y + 195, 100, 20},
			ft_ftoa(app->current_interaction->variable, 1));
		render_up_and_down_arrows(app, (t_point){227, 221},
			(t_point){227, 251}, 8);
	}
}

/**
 * Interaction explanations for event id 4 (light) and event id 5 (text pop-up).
*/
static void	render_interaction_explanation_3(t_app *app, int start_y)
{
	if (app->current_interaction->event_id == 4)
	{
		render_text(app, (t_rect){20, start_y + 155, 270, 200},
			"INTERACTING WITH OBJECT CHANGE SELECTED SECTOR'S LIGHT LEVEL.");
		render_text(app, (t_rect){25, start_y + 195, 100, 20},
			ft_ftoa(app->active_sector->light, 1));
		render_text(app, (t_rect){140, start_y + 195, 30, 20}, ">>");
		render_text(app, (t_rect){220, start_y + 195, 100, 20},
			ft_ftoa(app->current_interaction->variable, 1));
		render_up_and_down_arrows(app, (t_point){227, 221},
			(t_point){227, 251}, 8);
	}
	if (app->current_interaction->event_id == 5)
	{
		render_text(app, (t_rect){20, start_y + 155, 270, 200},
			"INTERACTING WITH OBJECT OPENS A TEXT POP-UP.");
		render_text(app, (t_rect){20, start_y + 195, 110, 20}, "LINE NUMBER");
		render_text(app, (t_rect){140, start_y + 195, 30, 20}, ">>");
		render_text(app, (t_rect){220, start_y + 195, 100, 20},
			ft_ftoa(app->current_interaction->variable, 1));
		render_up_and_down_arrows(app, (t_point){227, 221},
			(t_point){227, 251}, 8);
	}
}

/**
 * Interaction explanations for event id 3 (floor and ceiling height).
*/
static void	render_interaction_explanation_2(t_app *app, int start_y)
{
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
		render_up_and_down_arrows(app, (t_point){235, 243},
			(t_point){235, 273}, 8);
	}
}

/**
 * Interaction explanations for event id 1 (floor height) and event id 2
 * (ceiling height).
*/
static void	render_interaction_explanation_1(t_app *app, int start_y)
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
		render_up_and_down_arrows(app, (t_point){235, 221},
			(t_point){235, 251}, 8);
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
		render_up_and_down_arrows(app, (t_point){235, 236},
			(t_point){235, 266}, 8);
	}
}

/**
 * For each specific interaction event, renders explanation text what it
 * changes and the variable value it changes to.
*/
void	render_interaction_explanations(t_app *app, int start_y)
{
	render_interaction_explanation_1(app, start_y);
	render_interaction_explanation_2(app, start_y);
	render_interaction_explanation_3(app, start_y);
	render_interaction_explanation_4(app, start_y);
}
