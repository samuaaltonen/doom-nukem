/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 14:36:18 by htahvana          #+#    #+#             */
/*   Updated: 2023/01/25 16:32:05 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * @brief Initializes application struct.
 * 
 * @param app
 * @return int
 */
int	app_init(t_app **app)
{
	*app = (t_app *)malloc(sizeof(t_app));
	if (!(*app))
		return (FALSE);
	ft_bzero(*app, sizeof(t_app));
	(*app)->gravity = DEFAULT_GRAVITY;
	return (TRUE);
}

/**
 * @brief Prepares the application to be rendered:
 * Creates window, loads assets, adds event hooks and sets
 * initial player position / direction.
 * 
 * @param app
 */
void	app_prepare(t_app *app)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0)
		exit_error(MSG_ERROR_SDL_INIT);
	app->win = SDL_CreateWindow(WIN_NAME, 0, 0, WIN_W, WIN_H, SDL_WINDOW_SHOWN);
	if (!app->win)
		exit_error(MSG_ERROR_WINDOW);
	app->surface = SDL_GetWindowSurface(app->win);
	if (!app->surface)
		exit_error(MSG_ERROR_WINDOW_SURFACE);
	app->aspect_ratio = ((double)app->surface->h / (double)app->surface->w)
		* -100;
	app->view_size = (t_vector2){100.0, app->aspect_ratio};
	app->view_start = (t_vector2){-app->view_size.x / 2, -app->view_size.y / 2};
	app->view_end = (t_vector2){app->view_start.x + app->view_size.x,
		app->view_start.y + app->view_size.y};
	app->divider = 1.0f;
	app->zoom_range = 5;
	app->player_edit = TRUE;
	app->player.health = 200;
	app->player.armor = 100;
	app->movement_speed = 4;
	load_assets(app);
	load_font(app);
	weapons_init(app);
	SDL_ShowCursor(SDL_ENABLE);
}

/**
 * @brief Renders the optional lines and points based on if something has been
 * clicked active, or a certain menu is turned on.
 * 
 * @param app
*/
static void	app_render_helper(t_app *app)
{
	if (app->active)
	{
		render_sector(app, app->active);
		render_point(app, app->active->point, 3, POINT);
	}
	if (app->interaction_menu && app->current_interaction)
		render_target_sector_lines(app);
	if (app->interaction_menu && app->current_interaction
		&& app->current_interaction->interaction_link > -1)
		render_interaction_link_lines(app);
	render_sector_points(app);
	if (app->list_creation && !app->list_ongoing)
		render_point(app, app->mouse_track, 3, POINT);
	if (app->list_ongoing)
	{
		if (check_last_point(app) || valid_point(app))
			draw_line(app, &app->active_last->point, &app->mouse_track, LINE_A);
		else
			draw_line(app, &app->active_last->point, &app->mouse_track, LINE_B);
	}
}

/**
 * @brief Rendering function to be called in loop hook. Calls individual
 * renderers and draws resulting image(s) to the window.
 * 
 * @param app
 */
void	app_render(t_app *app)
{
	flush_surface(app->surface);
	handle_movement(app);
	app->view_end.x = app->view_start.x + app->view_size.x;
	app->view_end.y = app->view_start.y + app->view_size.y;
	render_fill_active_sector(app);
	render_divider(app);
	render_sectors(app);
	app_render_helper(app);
	render_objects(app);
	render_player(app);
	zoom_slider(app);
	render_help_menu(app);
	if (app->object_new)
		draw_object_icon(app, app->mouse_track, app->current_object->type);
	SDL_UpdateWindowSurface(app->win);
}

/**
 * @brief Main game loop. Polls SDL event queue until it is empty and then 
 * proceeds to next frame.
 * 
 * @param app
 */
void	app_loop(t_app *app)
{
	SDL_Event	event;

	while (TRUE)
	{
		while (SDL_PollEvent(&event))
			dispatch_event(app, &event);
		app_render(app);
	}
}
