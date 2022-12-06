/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_sector_info.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 11:54:40 by ssulkuma          #+#    #+#             */
/*   Updated: 2022/12/06 13:51:43 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * Renders the height and light statics on the help menu sidebar.
*/
static void	render_statics(t_app *app, t_point screen_pos)
{
	int		id;

	render_text(app, (t_rect){215, 464, 100, 15},
		ft_ftoa(app->active_sector->floor_height, 4));
	render_text(app, (t_rect){215, 561, 100, 15},
		ft_ftoa(app->active_sector->ceil_height, 4));
	if (app->active_sector->floor_slope_wall)
		render_text(app, (t_rect){215, 479, 100, 15},
			ft_ftoa(app->active_sector->floor_slope_height, 4));
	if (app->active_sector->ceil_slope_wall)
		render_text(app, (t_rect){215, 576, 100, 15},
			ft_ftoa(app->active_sector->ceil_slope_height, 4));
	render_text(app, (t_rect){235, 364, 100, 15}, ft_itoa(app->active_sector->light));
	id = find_sector_interaction(app);
	render_current_interaction_status(app, screen_pos, 600, id);
}

/**
 * Renders the light, height, slope header, toggling the color based
 * on the acitivy mode.
*/
void	render_sector_info(t_app *app, t_point screen_pos)
{
	if ((app->floor_edit) && !app->slope_edit)
		toggle_active_color(app, 1, "HEIGHT", (t_rect){28, 465, 260, 15});
	else
		toggle_active_color(app, 0, "HEIGHT", (t_rect){28, 465, 260, 15});
	if (app->floor_edit && app->active_sector->floor_slope_wall
		&& app->slope_edit)
		toggle_active_color(app, app->slope_edit, "SLOPE", (t_rect){28, 480, 260, 15});
	else
		toggle_active_color(app, app->slope_edit, "SLOPE", (t_rect){28, 480, 260, 15});
	if ((app->ceiling_edit) && !app->slope_edit)
		toggle_active_color(app, 1, "HEIGHT", (t_rect){28, 562, 260, 15});
	else
		toggle_active_color(app, 0, "HEIGHT", (t_rect){28, 562, 260, 15});
	if (app->ceiling_edit && app->active_sector->ceil_slope_wall
		&& app->slope_edit)
		toggle_active_color(app, app->slope_edit, "SLOPE", (t_rect){28, 577, 260, 15});
	else
		toggle_active_color(app, app->slope_edit, "SLOPE", (t_rect){28, 577, 260, 15});
	toggle_active_color(app, app->light_edit, "LIGHT", (t_rect){28, 365, 260, 15});
	render_statics(app, screen_pos);
}

/**
 * Loops through the interaction array to find if the current sector
 * has an interaction or not. Returns array id if it finds one and
 * -1 if not.
*/
int	find_sector_interaction(t_app *app)
{
	int		index;

	index = 0;
	while (index <= app->interaction_count)
	{
		if (app->interactions[index].activation_sector == app->active_sector
			&& !app->interactions[index].activation_wall
			&& !app->interactions[index].activation_object)
		{
			return (index);
		}
		index++;
	}
	return (-1);
}
