/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 16:04:22 by dpalacio          #+#    #+#             */
/*   Updated: 2023/02/20 15:20:25 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * @brief Initializes application struct.
 * 
 * @param app 
 */
void	app_init(t_app **app)
{
	*app = (t_app *)malloc(sizeof(t_app));
	if (!(*app))
		exit_error(MSG_ERROR_ALLOC);
	ft_bzero(*app, sizeof(t_app));
	(*app)->gravity = DEFAULT_GRAVITY;
	(*app)->textmodal.trigger_after = -1;
	(*app)->change_level = -1;
}

/**
 * @brief Initializes configuration struct.
 * 
 * @param app 
 */
void	config_init(t_app *app)
{
	app->conf = (t_conf *)malloc(sizeof(t_conf));
	if (!(app->conf))
		exit_error(MSG_ERROR_ALLOC);
	ft_bzero(app->conf, sizeof(t_conf));
	clock_gettime(CLOCK_REALTIME, &app->conf->fps_clock);
	app->conf->fov = FOV;
	app->conf->mouse_active = 1;
	app->status = STATUS_TITLESCREEN;
	app->conf->fps_avg = 0;
	app->conf->fps_total = 0;
	app->conf->frames_total = 0;
	ft_strcpy(app->conf->fps_info, "FPS                 ");
}

/**
 * @brief Initializes SDL related things.
 * 
 * @param app 
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
	app->audio.wav_spec.channels = DEFAULT_AUDIO_CHANNELS;
	app->audio.wav_spec.format = DEFAULT_AUDIO_FORMAT;
	app->audio.wav_spec.freq = DEFAULT_AUDIO_FREQUENCEY;
	app->audio.wav_spec.samples = DEFAULT_AUDIO_SAMPLES;
	app->audio.device_id = SDL_OpenAudioDevice(NULL, 0, &app->audio.wav_spec,
			NULL, SDL_AUDIO_ALLOW_FORMAT_CHANGE);
	if (!app->audio.device_id)
		exit_error(MSG_ERROR);
	SDL_ShowCursor(SDL_DISABLE);
}

/**
 * @brief Initializes bullets.
 * 
 * @param app 
 */
void	init_bullets(t_app *app)
{
	int	i;

	i = -1;
	ft_bzero(app->bullets, sizeof(t_bullet) * MAX_TEMP_OBJECTS);
	while (++i < MAX_TEMP_OBJECTS)
		app->bullets[i].type = -1;
}
