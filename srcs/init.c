/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 16:04:22 by dpalacio          #+#    #+#             */
/*   Updated: 2023/01/03 14:28:52 by htahvana         ###   ########.fr       */
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
	app->audio.device_id = SDL_OpenAudioDevice(NULL, 0, &app->audio.wav_spec,
		NULL, SDL_AUDIO_ALLOW_FORMAT_CHANGE);
	if (!app->audio.device_id)
		exit_error(MSG_ERROR);
	SDL_ShowCursor(SDL_DISABLE);
}

void	define_enemies(t_app *app)
{
	app->enemy_def[0].state_count = 4;
	app->enemy_def[0].range = 3.f;
	app->enemy_def[0].speed = 2.f;
	app->enemy_def[0].states[0][0] = 0.f;
	app->enemy_def[0].states[0][1] = 1.f;
	app->enemy_def[0].states[0][2] = 1.f;
	app->enemy_def[0].states[1][0] = 1.f;
	app->enemy_def[0].states[1][1] = 3.f;
	app->enemy_def[0].states[1][2] = 5.f;
	app->enemy_def[0].states[2][0] = 3.f;
	app->enemy_def[0].states[2][1] = 5.f;
	app->enemy_def[0].states[2][2] = 2.f;
	app->enemy_def[0].states[3][0] = 5.f;
	app->enemy_def[0].states[3][1] = 8.f;
	app->enemy_def[0].states[3][2] = 5.f;

	app->enemy_def[1].state_count = 4;
	app->enemy_def[1].range = 1.f;
	app->enemy_def[1].speed = 5.f;
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

/* 	app->enemy_def[2].state_count = 3;
	app->enemy_def[2].states[0][0] = 0;
	app->enemy_def[2].states[0][1] = 1;
	app->enemy_def[2].states[1][0] = 1;
	app->enemy_def[2].states[1][1] = 2;
	app->enemy_def[2].states[2][0] = 3;
	app->enemy_def[2].states[2][1] = 2;
	app->enemy_def[2].states[3][0] = 0;
	app->enemy_def[2].states[3][1] = 0; */
}

void	init_enemies(t_app *app)
{
	int				i;
	t_enemy_state	*enemy;
	int				enemy_count;

	enemy = &(app->enemies[0]);
	i = -1;
	enemy_count = 0;
	while(++i < MAX_OBJECTS)
	{
		if(app->objects[i].type >= MONSTER1 && app->objects[i].type < MONSTER1 + MAX_ENEMY_TYPES)
		{
			enemy->id = i;
			enemy->pos = app->objects[i].position;
			enemy->dead = FALSE;
			enemy->agressive = FALSE;
			enemy++;
			enemy_count++;
		}
		else
			enemy->id = -1;
	}
	ft_printf("%i enemy count \n", enemy_count);
}

void	init_projectiles(t_app *app)
{
	int	i;

	i = -1;

	ft_bzero(app->projectiles, sizeof(t_projectile) * MAX_TEMP_OBJECTS);
	while (++i < MAX_TEMP_OBJECTS)
		app->projectiles[i].type = -1;
}

/**
 * Loads all game assets
 */
void	load_assets(t_app *app)
{
	app->assets.ui_frame = SDL_LoadBMP(UI_FRAME_PATH);
	app->assets.title_screen_image = SDL_LoadBMP(TITLESCREEN_PATH);
	app->assets.crosshair = SDL_LoadBMP(CROSSHAIR_PATH);
	app->assets.pointer = SDL_LoadBMP(POINTER_PATH);
	app->assets.shield = SDL_LoadBMP(SHIELD_PATH);
	app->assets.hp = SDL_LoadBMP(HP_PATH);
	app->assets.pistol = SDL_LoadBMP(PISTOL_PATH);
	app->assets.bullet = SDL_LoadBMP(BULLET_PATH);
	app->assets.meter = SDL_LoadBMP(METER_PATH);
	app->assets.sprite = SDL_LoadBMP(PANELS_PATH);
	app->assets.bg = SDL_LoadBMP(SKYBOX_PATH);

	//temp 2d object array in 0, 2d object array in 1, 2d per enemy arrays from then on
	app->assets.sprites[0] = SDL_LoadBMP(PICKUP_PATH);
	app->assets.sprites[1] = SDL_LoadBMP(OBJECT_PATH);
	app->assets.sprites[2] = SDL_LoadBMP(SPRITE_PATH);
	app->assets.sprites[3] = SDL_LoadBMP(MONSTER_1_PATH);
	app->assets.sprites[4] = SDL_LoadBMP(MONSTER_2_PATH);
	load_font(app);
	load_texts(app);
	load_music(app, MUSIC_PATH);
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
