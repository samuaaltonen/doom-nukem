/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_sector_info.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 11:54:40 by ssulkuma          #+#    #+#             */
/*   Updated: 2023/02/07 16:38:51 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * @brief Renders active sector's information regarding the ceiling.
 * 
 * @param app
 * @param height
*/
static void	render_ceiling_info(t_app *app, char *height)
{
	toggle_active_color(app, app->ceiling_edit, "CEILING",
		(t_rect){114, 488, 200, 15});
	if (app->ceiling_edit && !app->slope_edit)
		toggle_active_color(app, 1, "HEIGHT", (t_rect){28, 562, 260, 15});
	else
		toggle_active_color(app, 0, "HEIGHT", (t_rect){28, 562, 260, 15});
	height = ft_ftoa(app->active_sector->ceil_height, 4);
	if (!height)
		return ;
	render_text(app, (t_rect){215, 561, 100, 15}, height);
	free(height);
	if (app->ceiling_edit && app->active_sector->ceil_slope_wall
		&& app->slope_edit)
		toggle_active_color(app, app->slope_edit, "SLOPE",
			(t_rect){28, 577, 260, 15});
	else
		toggle_active_color(app, 0, "SLOPE",
			(t_rect){28, 577, 260, 15});
	height = ft_ftoa(app->active_sector->ceil_slope_height, 4);
	if (!height)
		return ;
	if (app->active_sector->ceil_slope_wall)
		render_text(app, (t_rect){215, 576, 100, 15}, height);
	free(height);
}

/**
 * @brief Renders active sector's information regarding the floor.
 * 
 * @param app
 * @param height
*/
static void	render_floor_info(t_app *app, char *height)
{
	toggle_active_color(app, app->floor_edit, "FLOOR",
		(t_rect){122, 390, 200, 15});
	if (app->floor_edit && !app->slope_edit)
		toggle_active_color(app, 1, "HEIGHT", (t_rect){28, 465, 260, 15});
	else
		toggle_active_color(app, 0, "HEIGHT", (t_rect){28, 465, 260, 15});
	height = ft_ftoa(app->active_sector->floor_height, 4);
	if (!height)
		return ;
	render_text(app, (t_rect){215, 464, 100, 15}, height);
	free(height);
	if (app->floor_edit && app->active_sector->floor_slope_wall
		&& app->slope_edit)
		toggle_active_color(app, app->slope_edit, "SLOPE",
			(t_rect){28, 480, 260, 15});
	else
		toggle_active_color(app, 0, "SLOPE",
			(t_rect){28, 480, 260, 15});
	height = ft_ftoa(app->active_sector->floor_slope_height, 4);
	if (!height)
		return ;
	if (app->active_sector->floor_slope_wall)
		render_text(app, (t_rect){215, 479, 100, 15}, height);
	free(height);
}

/**
 * @brief Renders active sector's information regarding all the walls, light of
 * the sector and the sector interaction menu option.
 * 
 * @param app
 * @param mouse
*/
static void	render_walls_info(t_app *app, t_point mouse)
{
	int		id;
	char	*light;

	toggle_active_color(app, app->wall_edit, "WALL",
		(t_rect){125, 292, 200, 15});
	toggle_active_color(app, app->light_edit, "LIGHT",
		(t_rect){28, 365, 260, 15});
	light = ft_itoa(app->active_sector->light);
	if (!light)
		return ;
	render_text(app, (t_rect){235, 364, 100, 15}, light);
	free(light);
	if (!app->current_interaction)
		id = find_sector_interaction(app, 0, 1);
	else
		id = find_interaction(app);
	render_current_interaction_status(app, mouse, 600, id);
}

/**
 * @brief Renders the info texts when sector menu is turned on.
 * 
 * @param app
 * @param y
*/
static void	render_sector_help_texts(t_app *app, int y)
{
	render_text(app, (t_rect){20, y, 260, 100}, "TURN ON / OFF WALL CHANGE \
( V ) TURN ON / OFF FLOOR CHANGE ( F ) TURN ON / OFF CEILING CHANGE ( R )");
	render_text(app, (t_rect){20, y + 50, 260, 100}, "TEXTURE ( LEFT / RIGHT ) \
\n HEIGHT ( UP / DOWN (+ SHIFT) )");
	render_text(app, (t_rect){20, y + 85, 260, 50}, "CHANGE LIGHT ( + / - )");
	if (app->portal_selection)
		toggle_active_color(app, TRUE, "LINK PORTAL TO THIS SECTOR ( L )",
			(t_rect){20, y + 100, 260, 15});
	render_text(app, (t_rect){20, y + 120, 260, 100}, "TO CREATE A SLOPE, \
SELECT A CORNER AND PRESS 'Y' AND / OR 'H'.");
	if (app->active_sector->ceil_slope_wall
		|| app->active_sector->floor_slope_wall)
		render_text(app, (t_rect){20, y + 150, 260, 100}, "TOGGLE BETWEEN \
HEIGHT AND SLOPE HEIGHT CHANGE ( U )");
	render_text(app, (t_rect){20, y + 180, 260, 15}, "CHANGE PLAYER POSITION\
 ( P )");
	render_text(app, (t_rect){20, y + 200, 270, 50}, "TO DRAW NEW SECTORS WITH \
THESE HEIGHT, TEX AND LIGHT SETTINGS.");
	render_text(app, (t_rect){40, y + 650, 260, 15}, "DELETE SECTOR \
( BACKSPACE )");
}

/**
 * @brief Renders the sector specific information on the help menu sidebar when
 * there's an active sector, but no other edit mode is on.
 * 
 * @param app
 * @param mouse
 * @param y
*/
void	sector_edit_menu(t_app *app, t_point mouse, int y)
{
	render_sector_help_texts(app, y);
	render_interaction_button(app, (t_rect){84, y + 233, 120, 15}, mouse,
		"UPDATE TEMPLATE");
	render_ui_frame(app, (t_rect){67, y + 227, 150, 20}, 1, 0);
	render_arrows(app, (t_point){12, y + 290}, (t_point){265, y + 290});
	render_icons(app, (t_point){25, y + 280},
		app->active_sector->wall_list->tex, app->assets.sprite);
	render_arrows(app, (t_point){12, y + 388}, (t_point){265, y + 388});
	render_icons(app, (t_point){25, y + 378},
		app->active_sector->floor_tex, app->assets.sprite);
	render_arrows(app, (t_point){12, y + 486}, (t_point){265, y + 486});
	render_icons(app, (t_point){25, y + 478},
		app->active_sector->ceil_tex, app->assets.sprite);
	render_walls_info(app, mouse);
	render_floor_info(app, NULL);
	render_ceiling_info(app, NULL);
}
