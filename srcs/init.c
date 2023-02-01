/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 16:04:22 by dpalacio          #+#    #+#             */
/*   Updated: 2023/02/01 19:30:15 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * Initializes application struct.
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
 * Initializes configuration struct.
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

void	define_bullets(t_app *app)
{
	app->bullet_def[0].speed = 5.f;
	app->bullet_def[0].damage = 25.f;
	app->bullet_def[0].size = (t_vector2){0.5f,0.5f};
	app->bullet_def[1].speed = 5.f;
	app->bullet_def[1].damage = 25.f;
	app->bullet_def[1].size = (t_vector2){0.5f,0.5f};
	app->bullet_def[2].speed = 8.f;
	app->bullet_def[2].damage = 25.f;
	app->bullet_def[2].size = (t_vector2){0.5f,0.5f};
	app->bullet_def[3].speed = 8.f;
	app->bullet_def[3].damage = 25.f;
	app->bullet_def[3].size = (t_vector2){0.5f,0.5f};
	app->bullet_def[4].speed = 100.f;
	app->bullet_def[4].damage = 1.f;
	app->bullet_def[4].size = (t_vector2){0.5f,0.5f};
	app->bullet_def[5].speed = 8.f;
	app->bullet_def[5].damage = 25.f;
	app->bullet_def[5].size = (t_vector2){0.5f,0.5f};
	app->bullet_def[6].speed = 10.f;
	app->bullet_def[6].damage = 25.f;
	app->bullet_def[6].size = (t_vector2){0.5f,0.5f};
	app->bullet_def[7].speed = 50.f;
	app->bullet_def[7].damage = 25.f;
	app->bullet_def[7].size = (t_vector2){0.5f,0.5f};
}

void	define_enemy_0(t_app *app)
{
	app->enemy_def[0].state_count = 4;
	app->enemy_def[0].range = 3.f;
	app->enemy_def[0].speed = 2.f;
	app->enemy_def[0].attack_speed = 2.f;
	app->enemy_def[0].states[0][0] = 0.f;
	app->enemy_def[0].states[0][1] = 1.f;
	app->enemy_def[0].states[0][2] = 1.f;
	app->enemy_def[0].states[1][0] = 1.f;
	app->enemy_def[0].states[1][1] = 3.f;
	app->enemy_def[0].states[1][2] = 2.5f;
	app->enemy_def[0].states[2][0] = 3.f;
	app->enemy_def[0].states[2][1] = 5.f;
	app->enemy_def[0].states[2][2] = 2.f;
	app->enemy_def[0].states[3][0] = 5.f;
	app->enemy_def[0].states[3][1] = 8.f;
	app->enemy_def[0].states[3][2] = 5.f;
}

void	define_enemy_1(t_app *app)
{
	app->enemy_def[1].state_count = 4;
	app->enemy_def[1].range = 1.f;
	app->enemy_def[1].speed = 5.f;
	app->enemy_def[1].attack_speed = 4.f;
	app->enemy_def[1].states[0][0] = 0.f;
	app->enemy_def[1].states[0][1] = 1.f;
	app->enemy_def[1].states[0][2] = 1.f;
	app->enemy_def[1].states[1][0] = 1.f;
	app->enemy_def[1].states[1][1] = 6.f;
	app->enemy_def[1].states[1][2] = 5.f;
	app->enemy_def[1].states[2][0] = 6.f;
	app->enemy_def[1].states[2][1] = 8.f;
	app->enemy_def[1].states[2][2] = 2.f;
	app->enemy_def[1].states[3][0] = 9.f;
	app->enemy_def[1].states[3][1] = 12.f;
	app->enemy_def[1].states[3][2] = 5.f;
}

void	define_enemy_2(t_app *app)
{
	app->enemy_def[2].state_count = 4;
	app->enemy_def[2].range = 5.f;
	app->enemy_def[2].speed = 3.f;
	app->enemy_def[2].attack_speed = 1.5f;
	app->enemy_def[2].states[0][0] = 0.f;
	app->enemy_def[2].states[0][1] = 1.f;
	app->enemy_def[2].states[0][2] = 1.f;
	app->enemy_def[2].states[1][0] = 1.f;
	app->enemy_def[2].states[1][1] = 2.f;
	app->enemy_def[2].states[1][2] = 1.5f;
	app->enemy_def[2].states[2][0] = 2.f;
	app->enemy_def[2].states[2][1] = 4.f;
	app->enemy_def[2].states[2][2] = 2.f;
	app->enemy_def[2].states[3][0] = 4.f;
	app->enemy_def[2].states[3][1] = 5.f;
	app->enemy_def[2].states[3][2] = 1.f;
}

void	define_enemies(t_app *app)
{
	define_bullets(app);
	define_enemy_0(app);
	define_enemy_1(app);
	define_enemy_2(app);
}

void	init_enemies(t_app *app)
{
	int				i;
	t_enemy_state	*enemy;
	int				enemy_count;

	ft_bzero(&app->enemies, sizeof(app->enemies));
	enemy = &(app->enemies[0]);
	i = -1;
	enemy_count = 0;
	while (++i < MAX_OBJECTS)
	{
		if (app->objects[i].type >= MONSTER1
			&& app->objects[i].type < MONSTER1 + MAX_ENEMY_TYPES)
		{
			enemy->id = i;
			enemy->hp = 50.f;
			enemy->pos = app->objects[i].position;
			enemy->dead = FALSE;
			enemy->agressive = FALSE;
			enemy++;
			enemy_count++;
		}
		else
			enemy->id = -1;
	}
}

void	init_bullets(t_app *app)
{
	int	i;

	i = -1;

	ft_bzero(app->bullets, sizeof(t_bullet) * MAX_TEMP_OBJECTS);
	while (++i < MAX_TEMP_OBJECTS)
		app->bullets[i].type = -1;
}
