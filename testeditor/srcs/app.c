/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 14:36:18 by htahvana          #+#    #+#             */
/*   Updated: 2022/10/19 16:45:00 by htahvana         ###   ########.fr       */
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

	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0 || TTF_Init() < 0)
		exit_error(MSG_ERROR_SDL_INIT);
	app->win = SDL_CreateWindow(WIN_NAME, 0, 0, WIN_W, WIN_H, SDL_WINDOW_SHOWN);
	if (!app->win)
		exit_error(MSG_ERROR_WINDOW);
	app->surface = SDL_GetWindowSurface(app->win);
	if (!app->surface)
		exit_error(MSG_ERROR_WINDOW_SURFACE);
	app->font = TTF_OpenFont(FONT_FILE, 22);
	if (!app->font)
		exit_error(MSG_ERROR_FONT);
	aspect_ratio = ((double)app->surface->h / (double)app->surface->w) * -100;
	app->view_pos = (t_vector2){-50.0, 50.0};
	app->zoom_area = (t_vector2){100.0,aspect_ratio};
	app->view_size = (t_vector2){app->view_pos.x + app->zoom_area.x, app->view_pos.y + app->zoom_area.y};
	app->divider = 1.0f;
	app->zoom_range = 5;
	app->sectorcount = 0;
	app->sectors = NULL;
	SDL_ShowCursor(SDL_ENABLE);
	//SDL_WarpMouseInWindow(app->win, WIN_W / 2, WIN_H / 2);
}

/**
 * Rendering function to be called in loop hook. Calls individual renderers and
 * draws resulting image(s) to the window.
 */
void	app_render(t_app *app)
{
	
	flush_surface(app->surface);
	/* SDL_Surface	*converted_surface; */
	SDL_Surface *text_surface;
	text_surface = TTF_RenderText_Solid(app->font, "app->conf->fps_info", (SDL_Color){255, 255, 255, 0});
	handle_movement(app);
	app->view_size.x = app->view_pos.x + app->zoom_area.x;
	app->view_size.y = app->view_pos.y + app->zoom_area.y;
	render_grid(app, 0.5f, 0x424242);
	render_grid(app, 1.0f, 0x888888);
	zoom_slider(app);
	render_fill_active_sector(app);
	render_sectors(app);
	if(app->active)
		render_sector(app, app->active);
	if(app->list_ongoing)
		draw_line(app, &app->active_last->point, &app->mouse_click, 0xAABBCC);
	SDL_BlitSurface(text_surface, NULL, app->surface, NULL);
	SDL_FreeSurface(text_surface);
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
		app_render(app);
	}

}