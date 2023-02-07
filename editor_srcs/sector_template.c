/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector_template.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 15:13:27 by ssulkuma          #+#    #+#             */
/*   Updated: 2023/02/07 16:31:22 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * @brief The default values for the sector template.
 * 
 * @param app
*/
void	sector_template_init(t_app *app)
{
	app->template.ceil_height = 3.0;
	app->template.floor_height = 0.0;
	app->template.ceil_tex = 10;
	app->template.floor_tex = 10;
	app->template.wall_tex = 11;
	app->template.light = 0;
}

/**
 * @brief Updates the sector template values with the active sector's.
 * 
 * @param app
*/
void	update_sector_template(t_app *app)
{
	app->template.ceil_height = app->active_sector->ceil_height;
	app->template.floor_height = app->active_sector->floor_height;
	app->template.ceil_tex = app->active_sector->ceil_tex;
	app->template.floor_tex = app->active_sector->floor_tex;
	app->template.wall_tex = app->active_sector->wall_list->tex;
	app->template.light = app->active_sector->light;
}
