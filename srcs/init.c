/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <danielmdc94@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 16:04:22 by dpalacio          #+#    #+#             */
/*   Updated: 2022/11/21 14:44:00 by dpalacio         ###   ########.fr       */
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
	app->conf->fps_avg = 0;
	app->conf->fps_total = 0;
	app->conf->frames_total = 0;
	ft_strcpy(app->conf->fps_info, "FPS                 ");
	return (1);
}

/**
 * Prepares the application to be rendered:
 * Creates window and opens an audio device
 */
void	sdl_init(t_app *app)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_AUDIO) < 0)
		exit_error(MSG_ERROR_SDL_INIT);
	SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");
	app->win = SDL_CreateWindow(WIN_NAME, 0, 0, WIN_W, WIN_H, SDL_WINDOW_SHOWN);
	if (!app->win)
		exit_error(MSG_ERROR_WINDOW);
	app->surface = SDL_GetWindowSurface(app->win);
	if (!app->surface)
		exit_error(MSG_ERROR_WINDOW_SURFACE);
	app->audio.device_id = SDL_OpenAudioDevice(NULL, 0, &app->audio.wav_spec, NULL, SDL_AUDIO_ALLOW_FORMAT_CHANGE);
	if (!app->audio.device_id)
		exit_error(MSG_ERROR);
	SDL_ShowCursor(SDL_DISABLE);
}

/**
 * Loads all game assets
 */
void    load_assets(t_app *app)
{
	app->assets.ui_frame = SDL_LoadBMP(UI_FRAME_PATH);
	app->assets.title_screen_image = SDL_LoadBMP(TITLESCREEN_PATH);
	app->assets.crosshair = SDL_LoadBMP(CROSSHAIR_PATH);
	app->assets.pointer = SDL_LoadBMP(POINTER_PATH);
	app->assets.shield = SDL_LoadBMP(SHIELD_PATH);
		app->assets.heart = SDL_LoadBMP(HEART_PATH);
	app->assets.sprite = SDL_LoadBMP(PANELS_PATH);
	app->assets.bg = SDL_LoadBMP(SKYBOX_PATH);
    load_font(app);
}

/**
 * Loads the font or resets it
 */
void	load_font(t_app *app)
{
	if (!app->assets.font.font)
		app->assets.font.font = SDL_LoadBMP(FONT_PATH);
	if (!app->assets.font.font)
		exit_error("Could not load font");
	change_font(app, 16, 0xFF000000);
}
