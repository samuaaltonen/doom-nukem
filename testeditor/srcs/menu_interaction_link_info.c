/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_interaction_link_info.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 14:36:50 by ssulkuma          #+#    #+#             */
/*   Updated: 2023/01/10 17:25:42 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * Displays the event type for the linked interaction.
*/
static void	display_link_event(t_app *app, int id, int start_y)
{
	if (app->interactions[id].event_id == 1)
		render_text(app, (t_rect){25, start_y + 255, 160, 20}, "FLOOR HEIGHT");
	if (app->interactions[id].event_id == 2)
		render_text(app, (t_rect){25, start_y + 255, 160, 20}, "CEILING \
HEIGHT");
	if (app->interactions[id].event_id == 3)
		render_text(app, (t_rect){25, start_y + 255, 160, 40}, "FLOOR AND \
CEILING HEIGHT");
	if (app->interactions[id].event_id == 4)
		render_text(app, (t_rect){25, start_y + 255, 160, 20}, "LIGHT");
	if (app->interactions[id].event_id == 5)
		render_text(app, (t_rect){25, start_y + 255, 160, 20}, "TEXT POP-UP");
	if (app->interactions[id].event_id == 6)
		render_text(app, (t_rect){25, start_y + 255, 160, 20}, "SOUND");
	if (app->interactions[id].event_id == 7)
		render_text(app, (t_rect){25, start_y + 255, 160, 20}, "END LEVEL");
}

/**
 * 
*/
static int	get_current_interaction_count(t_app *app, int interaction)
{
	int		count;
	int		id;

	count = 0;
	id = 0;
	while (id < MAX_INTERACTIONS)
	{
		if (app->interactions[id].event_id != 0)
			count++;
		if (id == interaction)
			break ;
		id++;
	}
	return (count);
}

/**
 * Renders the information regarding the linked interactions.
*/
void	render_link_interaction_info(t_app *app, int start_y, t_point mouse)
{
	char	*statics;

	if (app->interaction_count > 0 && app->current_interaction)
	{
		if (!app->link_interaction)
		{
			render_text(app, (t_rect){20, start_y + 245, 170, 40}, "LINK \
INTERACTION TO ANOTHER EXISTING ONE BY PRESSING 'LINK'");
			render_ui_frame(app, (t_rect){190, start_y + 253, 60, 16}, 1, 0);
			render_interaction_button(app, (t_rect){204, start_y + 255, 60, 15},
				mouse, "LINK");
		}
		else if (app->link_interaction)
		{
			render_arrows(app, (t_point){185, start_y + 253}, (t_point){260, start_y + 253});
			statics = ft_itoa(get_current_interaction_count(app,
				(int)app->current_interaction->editable));
			if (!statics)
				return ;
			render_text(app, (t_rect){200, start_y + 255, 100, 20}, statics);
			free(statics);
			render_text(app, (t_rect){220, start_y + 255, 100, 20}, "/");
			statics = ft_itoa(app->interaction_count);
			if (!statics)
				return ;
			render_text(app, (t_rect){235, start_y + 255, 100, 20}, statics);
			free(statics);
			display_link_event(app, (int)app->current_interaction->editable, start_y);
			render_ui_frame(app, (t_rect){187, start_y + 273, 73, 16}, 1, 0);
			render_interaction_button(app, (t_rect){201, start_y + 275, 70, 15},
				mouse, "REMOVE");
		}
	}
}
