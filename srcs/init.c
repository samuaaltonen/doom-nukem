/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <danielmdc94@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 16:04:22 by dpalacio          #+#    #+#             */
/*   Updated: 2022/10/24 14:54:41 by dpalacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * Initializes application struct.
 */
void	app_init(t_app **app)
{
	*app = (t_app *)malloc(sizeof(t_app));
	ft_bzero(*app, sizeof(t_app));
	if (!(*app))
		exit_error(NULL);
}

/**
 * Initializes configuration struct.
 */
int	config_init(t_app *app)
{
	if (!app)
		return (0);
	app->conf = (t_conf *)malloc(sizeof(t_conf));
	if (!(app->conf))
		return (0);
	ft_bzero(app->conf, sizeof(t_conf));
	clock_gettime(CLOCK_REALTIME, &app->conf->fps_clock);
	app->conf->fov = FOV;
	app->conf->skybox_offset = 360.f;
	app->conf->movement_speed = MOVEMENT_SPEED;
	app->conf->rotation_speed = ROTATION_SPEED;
	app->conf->mouse_active = 1;
	app->status = STATUS_TITLESCREEN;
	ft_strcpy(app->conf->fps_info, "FPS                 ");
	init_thread_info(app);
	return (1);
}


/**
 * Prepares the application to be rendered:
 * Creates window, adds event hooks and sets
 * initial player position / direction.
 */
void	sdl_init(t_app *app)
{
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0)
		exit_error(MSG_ERROR_SDL_INIT);
	app->win = SDL_CreateWindow(WIN_NAME, 0, 0, WIN_W, WIN_H, SDL_WINDOW_SHOWN);
	if (!app->win)
		exit_error(MSG_ERROR_WINDOW);
	app->surface = SDL_GetWindowSurface(app->win);
	if (!app->surface)
		exit_error(MSG_ERROR_WINDOW_SURFACE);
}

/**
 * Loads all game assets
 */
void    load_assets(t_app *app)
{
	app->assets.button_texture = SDL_LoadBMP(BUTTON_TX);
	app->assets.title_screen_image = SDL_LoadBMP(TITLESCREEN_TX);
	app->assets.sprite = SDL_LoadBMP(PANELS_TX);
	app->assets.bg = SDL_LoadBMP(SKYBOX_TX);
    load_font(app);
}

/**
 * Loads the font or resets it
 */
void	load_font(t_app *app)
{
	if (!app->assets.font.font)
		app->assets.font.font = SDL_LoadBMP(FONT_TX);
	if (!app->assets.font.font)
		exit_error("Could not load font");
	change_font(app, 16, 0xFF000000);
}
