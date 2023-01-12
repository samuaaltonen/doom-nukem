/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_sector_info.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 11:54:40 by ssulkuma          #+#    #+#             */
/*   Updated: 2023/01/12 15:56:33 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * Renders active sector's information regarding the ceiling.
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
 * Renders active sector's information regarding the floor.
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
 * Renders active sector's information regarding all the walls, light of the
 * sector and the sector interaction menu option.
*/
static void	render_walls_info(t_app *app, t_point screen_pos)
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
	render_current_interaction_status(app, screen_pos, 600, id);
}

/**
 * Renders the sector specific information on the help menu sidebar when
 * there's an active sector, but no other edit mode is on.
*/
void	sector_edit_menu(t_app *app, t_point screen_pos, int y)
{
	render_text(app, (t_rect){20, y, 260, 100}, "TOGGLE ALL WALLS ( V )\nTOG\
GLE FLOOR ( F )\nTOGGLE CEILING ( R )\nTOGGLE LIGHT ( T )\nTOGGLE SLOPE ( U )");
	render_text(app, (t_rect){20, y + 70, 260, 50}, "TEX ( LEFT / RIGHT )\n \
HEIGHT ( UP / DOWN )");
	toggle_active_color(app, app->portal_selection, "CREATE PORTAL ( L )",
		(t_rect){20, y + 105, 260, 15});
	render_text(app, (t_rect){20, y + 120, 260, 150}, "SELECT WALL TO CREATE \
PORTAL, PRESS 'L', SELECT SECTOR TO LINK PORTAL TO, PRESS 'L' AGAIN. DOUBLE \
PRESS 'L' TO REMOVE PORTAL.");
	render_text(app, (t_rect){20, y + 195, 260, 15}, "CREATE OBJECT ( N )");
	render_text(app, (t_rect){20, y + 215, 260, 15}, "DELETE SECTOR ( DEL )");
	render_arrows(app, (t_point){12, y + 290}, (t_point){265, y + 290});
	render_icons(app, (t_point){25, y + 280},
		app->active_sector->wall_list->tex, app->assets.sprite);
	render_arrows(app, (t_point){12, y + 388}, (t_point){265, y + 388});
	render_icons(app, (t_point){25, y + 378},
		app->active_sector->floor_tex, app->assets.sprite);
	render_arrows(app, (t_point){12, y + 486}, (t_point){265, y + 486});
	render_icons(app, (t_point){25, y + 478},
		app->active_sector->ceil_tex, app->assets.sprite);
	render_walls_info(app, screen_pos);
	render_floor_info(app, NULL);
	render_ceiling_info(app, NULL);
}
