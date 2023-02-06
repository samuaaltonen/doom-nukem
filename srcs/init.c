/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 16:04:22 by dpalacio          #+#    #+#             */
/*   Updated: 2023/02/06 19:41:04 by saaltone         ###   ########.fr       */
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
		exit_error(NULL);
	ft_bzero(*app, sizeof(t_app));
	(*app)->gravity = DEFAULT_GRAVITY;
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
 * @brief Defines bullet values.
 * 
 * @param app 
 */
void	define_bullets(t_app *app)
{
	app->bullet_def[0].speed = 5.f;
	app->bullet_def[0].damage = 25.f;
	app->bullet_def[0].size = (t_vector2){0.5f, 0.5f};
	app->bullet_def[1].speed = 5.f;
	app->bullet_def[1].damage = 25.f;
	app->bullet_def[1].size = (t_vector2){0.5f, 0.5f};
	app->bullet_def[2].speed = 8.f;
	app->bullet_def[2].damage = 25.f;
	app->bullet_def[2].size = (t_vector2){0.5f, 0.5f};
	app->bullet_def[3].speed = 8.f;
	app->bullet_def[3].damage = 25.f;
	app->bullet_def[3].size = (t_vector2){0.5f, 0.5f};
	app->bullet_def[4].speed = 100.f;
	app->bullet_def[4].damage = 1.f;
	app->bullet_def[4].size = (t_vector2){0.5f, 0.5f};
	app->bullet_def[5].speed = 8.f;
	app->bullet_def[5].damage = 25.f;
	app->bullet_def[5].size = (t_vector2){0.5f, 0.5f};
	app->bullet_def[6].speed = 10.f;
	app->bullet_def[6].damage = 25.f;
	app->bullet_def[6].size = (t_vector2){0.5f, 0.5f};
	app->bullet_def[7].speed = 50.f;
	app->bullet_def[7].damage = 25.f;
	app->bullet_def[7].size = (t_vector2){0.5f, 0.5f};
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
