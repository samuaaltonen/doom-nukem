/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_interaction_explanations_extra.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 15:22:38 by ssulkuma          #+#    #+#             */
/*   Updated: 2023/01/13 15:35:59 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * @brief Explanation texts and statics for end level interaction.
 * 
 * @param app
 * @param start_y
 * @param statics
*/
void	end_level_explanation(t_app *app, int start_y, char *statics)
{
	render_text(app, (t_rect){20, start_y + 155, 270, 200},
		"INTERACTING WITH OBJECT ENDS THE LEVEL.");
	render_text(app, (t_rect){20, start_y + 195, 100, 20}, "END LEVEL");
	render_text(app, (t_rect){140, start_y + 195, 30, 20}, ">>");
	statics = ft_ftoa(app->current_interaction->variable, 1);
	if (!statics)
		return ;
	render_text(app, (t_rect){220, start_y + 195, 100, 20}, statics);
	free(statics);
	render_up_and_down_arrows(app, (t_point){227, 221}, (t_point){227, 251}, 8);
}

/**
 * @brief Explanation texts and statics for sound interaction.
 * 
 * @param app
 * @param start_y
 * @param statics
*/
void	sound_explanation(t_app *app, int start_y, char *statics)
{
	render_text(app, (t_rect){20, start_y + 155, 270, 200},
		"INTERACTING WITH OBJECT PLAYS A SOUND.");
	render_text(app, (t_rect){20, start_y + 195, 110, 20}, "AUDIO TRACK");
	render_text(app, (t_rect){140, start_y + 195, 30, 20}, ">>");
	statics = ft_ftoa(app->current_interaction->variable, 1);
	if (!statics)
		return ;
	render_text(app, (t_rect){220, start_y + 195, 100, 20}, statics);
	free(statics);
	render_up_and_down_arrows(app, (t_point){227, 221}, (t_point){227, 251}, 8);
}

/**
 * @brief Explanation texts and statics for text popup interaction.
 * 
 * @param app
 * @param start_y
 * @param statics
*/
void	text_popup_explanation(t_app *app, int start_y, char *statics)
{
	render_text(app, (t_rect){20, start_y + 155, 270, 200},
		"INTERACTING WITH OBJECT OPENS A TEXT POP-UP.");
	render_text(app, (t_rect){20, start_y + 195, 110, 20}, "LINE NUMBER");
	render_text(app, (t_rect){140, start_y + 195, 30, 20}, ">>");
	statics = ft_ftoa(app->current_interaction->variable, 1);
	if (!statics)
		return ;
	render_text(app, (t_rect){220, start_y + 195, 100, 20}, statics);
	free(statics);
	render_up_and_down_arrows(app, (t_point){227, 221}, (t_point){227, 251}, 8);
}
