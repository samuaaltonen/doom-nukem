/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_interaction_explanations.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 15:32:28 by ssulkuma          #+#    #+#             */
/*   Updated: 2023/01/13 15:37:05 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * @brief Explanation texts and statics for light level change interaction.
 * 
 * @param app
 * @param start_y
 * @param statics
*/
static void	light_explanation(t_app *app, int start_y, char *statics)
{
	render_text(app, (t_rect){20, start_y + 155, 270, 200},
		"INTERACTING WITH OBJECT CHANGE SELECTED SECTOR'S LIGHT LEVEL.");
	statics = ft_ftoa(app->active_sector->light, 1);
	if (!statics)
		return ;
	render_text(app, (t_rect){25, start_y + 195, 100, 20}, statics);
	free(statics);
	render_text(app, (t_rect){140, start_y + 195, 30, 20}, ">>");
	statics = ft_ftoa(app->current_interaction->variable, 1);
	if (!statics)
		return ;
	render_text(app, (t_rect){220, start_y + 195, 100, 20}, statics);
	free(statics);
	render_up_and_down_arrows(app, (t_point){227, 221}, (t_point){227, 251}, 8);
}

/**
 * @brief Explanation texts and statics for floor and ceiling height change
 * interaction.
 * 
 * @param app
 * @param start_y
 * @param statics
*/
static void	floor_and_ceiling_height_explanation(t_app *app, int start_y,
																char *statics)
{
	render_text(app, (t_rect){20, start_y + 155, 270, 200},
		"INTERACTING WITH OBJECT CHANGE SELECTED SECTOR'S FLOOR AND CEILING \
HEIGHT.");
	statics = ft_ftoa(app->active_sector->floor_height, 4);
	if (!statics)
		return ;
	render_text(app, (t_rect){20, start_y + 210, 100, 20}, statics);
	free(statics);
	statics = ft_ftoa(app->active_sector->ceil_height, 4);
	if (!statics)
		return ;
	render_text(app, (t_rect){20, start_y + 225, 100, 20}, statics);
	free(statics);
	render_text(app, (t_rect){140, start_y + 218, 30, 20}, ">>");
	statics = ft_ftoa(app->current_interaction->variable, 4);
	if (!statics)
		return ;
	render_text(app, (t_rect){220, start_y + 218, 100, 20}, statics);
	free(statics);
	render_up_and_down_arrows(app, (t_point){235, 243}, (t_point){235, 273}, 8);
}

/**
 * @brief Explanation texts and statics for ceiling height change interaction.
 * 
 * @param app
 * @param start_y
 * @param statics
*/
static void	ceiling_height_explanation(t_app *app, int start_y, char *statics)
{
	render_text(app, (t_rect){20, start_y + 155, 270, 200},
		"INTERACTING WITH OBJECT CHANGE SELECTED SECTOR'S CEILING HEIGHT.");
	statics = ft_ftoa(app->active_sector->ceil_height, 4);
	if (!statics)
		return ;
	render_text(app, (t_rect){20, start_y + 210, 100, 20}, statics);
	free(statics);
	render_text(app, (t_rect){140, start_y + 210, 30, 20}, ">>");
	statics = ft_ftoa(app->current_interaction->variable, 4);
	if (!statics)
		return ;
	render_text(app, (t_rect){220, start_y + 210, 100, 20}, statics);
	free(statics);
	render_up_and_down_arrows(app, (t_point){235, 236}, (t_point){235, 266}, 8);
}

/**
 * @brief Explanation texts and statics for floor height change interaction.
 * 
 * @param app
 * @param start_y
 * @param statics
*/
static void	floor_height_explanation(t_app *app, int start_y, char *statics)
{
	render_text(app, (t_rect){20, start_y + 155, 270, 200},
		"INTERACTING WITH OBJECT CHANGE SELECTED SECTOR'S FLOOR HEIGHT.");
	statics = ft_ftoa(app->active_sector->floor_height, 4);
	if (!statics)
		return ;
	render_text(app, (t_rect){20, start_y + 195, 100, 20}, statics);
	free(statics);
	render_text(app, (t_rect){140, start_y + 195, 30, 20}, ">>");
	statics = ft_ftoa(app->current_interaction->variable, 4);
	if (!statics)
		return ;
	render_text(app, (t_rect){220, start_y + 195, 100, 20}, statics);
	free(statics);
	render_up_and_down_arrows(app, (t_point){235, 221}, (t_point){235, 251}, 8);
}

/**
 * @brief For each specific interaction event, renders explanation text what it
 * changes and the variable value it changes to.
 * 
 * @param app
 * @param start_y
*/
void	render_interaction_explanations(t_app *app, int start_y)
{
	char	*statics;

	statics = NULL;
	if (app->current_interaction->event_id == 1)
		floor_height_explanation(app, start_y, statics);
	else if (app->current_interaction->event_id == 2)
		ceiling_height_explanation(app, start_y, statics);
	else if (app->current_interaction->event_id == 3)
		floor_and_ceiling_height_explanation(app, start_y, statics);
	else if (app->current_interaction->event_id == 4)
		light_explanation(app, start_y, statics);
	else if (app->current_interaction->event_id == 5)
		text_popup_explanation(app, start_y, statics);
	else if (app->current_interaction->event_id == 6)
		sound_explanation(app, start_y, statics);
	else if (app->current_interaction->event_id == 7)
		end_level_explanation(app, start_y, statics);
}
