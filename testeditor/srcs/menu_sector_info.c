/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_sector_info.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 11:54:40 by ssulkuma          #+#    #+#             */
/*   Updated: 2022/11/08 16:17:20 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * Renders the height and light statics on the help menu sidebar.
*/
static void	render_statics(t_app *app)
{
	render_text(app, (t_point){100, 495}, ft_itoa(app->active_sector->light));
	render_text(app, (t_point){100, 515},
		ft_ftoa(app->active_sector->floor_height, 4));
	render_text(app, (t_point){200, 515},
		ft_ftoa(app->active_sector->ceil_height, 4));
	if (app->active_sector->floor_slope_wall)
		render_text(app, (t_point){100, 535},
			ft_ftoa(app->active_sector->floor_slope_height, 4));
	if (app->active_sector->ceil_slope_wall)
		render_text(app, (t_point){200, 535},
			ft_ftoa(app->active_sector->ceil_slope_height, 4));
}

/**
 * Renders the light, height, slope header, toggling the color based
 * on the acitivy mode.
*/
void	render_sector_info(t_app *app)
{
	toggle_active_color(app, app->light_edit, "LIGHT", (t_point){22, 495});
	if ((app->floor_edit || app->ceiling_edit) && !app->slope_edit)
		toggle_active_color(app, 1, "HEIGHT", (t_point){22, 515});
	else
		toggle_active_color(app, 0, "HEIGHT", (t_point){22, 515});
	if (app->floor_edit && app->active_sector->floor_slope_wall
		&& app->slope_edit)
		toggle_active_color(app, app->slope_edit, "SLOPE", (t_point){22, 535});
	else if (app->ceiling_edit && app->active_sector->ceil_slope_wall
		&& app->slope_edit)
		toggle_active_color(app, app->slope_edit, "SLOPE", (t_point){22, 535});
	else
		toggle_active_color(app, app->slope_edit, "SLOPE", (t_point){22, 535});
	render_statics(app);
}