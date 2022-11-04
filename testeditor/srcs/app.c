/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 14:36:18 by htahvana          #+#    #+#             */
/*   Updated: 2022/11/04 15:03:20 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * Initializes application struct.
 */
int	app_init(t_app **app)
{
	*app = (t_app *)malloc(sizeof(t_app));
	ft_bzero(*app, sizeof(t_app));
	if (!(*app))
		return (0);
	return (1);
}

/**
 * Prepares the application to be rendered:
 * Creates window, loads assets, adds event hooks and sets
 * initial player position / direction.
 */
void	app_prepare(t_app *app)
{
	double		aspect_ratio;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0 || TTF_Init() < 0)
		exit_error(MSG_ERROR_SDL_INIT);
	app->win = SDL_CreateWindow(WIN_NAME, 0, 0, WIN_W, WIN_H, SDL_WINDOW_SHOWN);
	if (!app->win)
		exit_error(MSG_ERROR_WINDOW);
	app->surface = SDL_GetWindowSurface(app->win);
	if (!app->surface)
		exit_error(MSG_ERROR_WINDOW_SURFACE);
	aspect_ratio = ((double)app->surface->h / (double)app->surface->w) * -100;
	app->view_pos = (t_vector2){-50.0, 50.0};
	app->zoom_area = (t_vector2){100.0, aspect_ratio};
	app->view_size = (t_vector2){app->view_pos.x + app->zoom_area.x,
		app->view_pos.y + app->zoom_area.y};
	app->divider = 1.0f;
	app->zoom_range = 5;
	app->sectorcount = 0;
	app->sectors = NULL;
	app->player_edit = 0;
	app->player.sector = -1;
	load_assets(app);
	load_font(app);
	SDL_ShowCursor(SDL_ENABLE);
}

/**
 * Rendering function to be called in loop hook. Calls individual renderers and
 * draws resulting image(s) to the window.
 */
void	app_render(t_app *app)
{
	flush_surface(app->surface);
	handle_movement(app);
	app->view_size.x = app->view_pos.x + app->zoom_area.x;
	app->view_size.y = app->view_pos.y + app->zoom_area.y;
	render_fill_active_sector(app);
	render_divider(app);
	render_sectors(app);
	if (app->active)
	{
		render_sector(app, app->active);
		render_selection_point(app, app->active, 3);
	}
	render_sector_points(app);
	if (app->list_ongoing)
	{
		if (valid_point(app))
			draw_line(app, &app->active_last->point, &app->mouse_track, LINE_A);
		else
			draw_line(app, &app->active_last->point, &app->mouse_track, LINE_B);
	}
	render_player(app);
	zoom_slider(app);
	render_help_menu(app);
	SDL_UpdateWindowSurface(app->win);
}

/**
 * Main game loop. Polls SDL event queue until it is empty and then 
 * proceeds to next frame.
 */
void	app_loop(t_app *app)
{
	SDL_Event	event;

	while (TRUE)
	{
		while (SDL_PollEvent(&event))
			dispatch_event(app, &event);
		ft_printf("x=%f, y=%f modes:c%i,o%i,p%i,r%i,f%i,s%i\n", app->mouse_track.x, app->mouse_track.y, app->list_creation, app->list_ongoing, app->portal_selection, app->ceiling_edit, app->floor_edit, app->slope_edit);
		ft_printf("PLAYER pos x= %f pos y= %f dir x= %f dir y= %f sector= %d\n", app->player.position.x, app->player.position.y, app->player.direction.x, app->player.direction.y, app->player.sector);
		if (app->active_sector)
		{
			ft_printf("inside = %i, floor: h:%f,tex:%i,o:%i, ceil: h:%f,tex:%i,o:%i, light:%i\n has members: ", app->active_sector, app->active_sector->floor_height, app->active_sector->floor_tex, app->active_sector->floor_tex_offset, app->active_sector->ceil_height, app->active_sector->ceil_tex, app->active_sector->ceil_tex_offset, app->active_sector->light);
			for (int i = 0; i < 4 && app->active_sector->member_sectors[i]; ++i)
				ft_printf("%i ", get_sector_id(app, app->active_sector->member_sectors[i]));
			ft_printf("\n");
			if (app->active_sector->parent_sector)
				ft_printf("parent id %i, ", app->active_sector->parent_sector);
			if (app->active_sector->ceil_slope_wall)
				ft_printf("ceiling slopes from %i to %i, height %f, ", app->active_sector->ceil_slope_wall, app->active_sector->ceil_slope_opposite, app->active_sector->ceil_slope_height);
			if (app->active_sector->floor_slope_wall)
				ft_printf("floor slopes from %i to %i, height %f", app->active_sector->floor_slope_wall, app->active_sector->floor_slope_opposite, app->active_sector->floor_slope_height);
			ft_printf("\n");
		}
		if (app->active)
			ft_printf("selected point x:%f, y:%f, tex:%i, type:%i\n", app->active->point.x, app->active->point.y, app->active->tex, app->active->type);
		app_render(app);
	}
}
