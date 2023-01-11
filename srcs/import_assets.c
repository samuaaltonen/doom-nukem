/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import_assets.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 14:39:23 by saaltone          #+#    #+#             */
/*   Updated: 2023/01/11 18:43:06 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * @brief Imports surface pixel data.
 * 
 * @param info 
 * @param data 
 * @param imported 
 * @return SDL_Surface* 
 */
static SDL_Surface	*import_surface(t_app *app, t_thread_data *thread,
	int asset_type, t_import_info *import_info)
{
	t_export_asset	asset_info;
	SDL_Surface		*surface;

	asset_info = import_info->header.asset_info[asset_type];
	if (asset_info.size > import_info->length - import_info->imported)
		exit_error(MSG_ERROR_IMPORT_SURFACE);
	surface = SDL_CreateRGBSurface(0, asset_info.width, asset_info.height,
			IMAGE_PIXEL_BITS, 0, 0, 0, 0);
	if (!surface)
		exit_error(MSG_ERROR_IMAGE_INIT);
	ft_memcpy(surface->pixels, import_info->data + import_info->imported,
		asset_info.size);
	import_info->imported += asset_info.size;
	import_update_progress(app, thread, import_info);
	return (surface);
}

/**
 * @brief Imports all game surfaces.
 * 
 * @param app 
 * @param thread 
 * @param info 
 */
static void	import_surfaces(t_app *app, t_thread_data *thread,
	t_import_info *info)
{
	app->assets.panels = import_surface(app, thread, EXPORT_PANELS, info);
	app->assets.bg = import_surface(app, thread, EXPORT_SKYBOX, info);
	app->assets.font.font = import_surface(app, thread, EXPORT_FONT, info);
	app->assets.ui_frame = import_surface(app, thread, EXPORT_UI_FRAME, info);
	app->assets.title_screen_image = import_surface(app, thread,
			EXPORT_TITLESCREEN, info);
	app->assets.crosshair = import_surface(app, thread, EXPORT_CROSSHAIR, info);
	app->assets.pointer = import_surface(app, thread, EXPORT_POINTER, info);
	app->assets.shield = import_surface(app, thread, EXPORT_SHIELD, info);
	app->assets.hp = import_surface(app, thread, EXPORT_HP, info);
	app->assets.pistol = import_surface(app, thread, EXPORT_PISTOL, info);
	app->assets.bullet = import_surface(app, thread, EXPORT_BULLET, info);
	app->assets.meter = import_surface(app, thread, EXPORT_METER, info);
	app->assets.object_icon = import_surface(app, thread, EXPORT_ICON, info);
	app->assets.weapon = import_surface(app, thread, EXPORT_WEAPON_HD, info);
	app->assets.sprites[SMALL_SPRITE] = import_surface(app, thread,
			EXPORT_PICKUP, info);
	app->assets.sprites[BIG_SPRITE] = import_surface(app, thread,
			EXPORT_OBJECT, info);
	app->assets.sprites[PROJECTILE_SPRITE] = import_surface(app, thread,
			EXPORT_SPRITE, info);
	app->assets.sprites[ENEMY_SPRITE_1] = import_surface(app, thread,
			EXPORT_MONSTER_1, info);
	app->assets.sprites[ENEMY_SPRITE_2] = import_surface(app, thread,
			EXPORT_MONSTER_2, info);
}

/**
 * @brief Imports wav data.
 * 
 * @param app 
 * @param thread 
 * @param asset_type 
 * @param import_info 
 * @return t_uint8* 
 */
static t_uint8	*import_wav(t_app *app, t_thread_data *thread,
	int asset_type, t_import_info *import_info)
{
	t_export_asset	asset_info;
	t_uint8			*audio_data;

	asset_info = import_info->header.asset_info[asset_type];
	if (asset_info.size > import_info->length - import_info->imported)
		exit_error(MSG_ERROR_IMPORT_AUDIO);
	audio_data = (t_uint8*)malloc(asset_info.size);
	if (!audio_data)
		exit_error(MSG_ERROR_ALLOC);
	ft_memcpy(audio_data, import_info->data + import_info->imported,
		asset_info.size);
	import_info->imported += asset_info.size;
	import_update_progress(app, thread, import_info);
	return (audio_data);
}

/**
 * @brief Imports game sound files.
 * 
 * @param app 
 * @param thread 
 * @param info 
 */
static void	import_wavs(t_app *app, t_thread_data *thread,
	t_import_info *info)
{
	app->audio.data[AUDIO_MUSIC] = import_wav(app, thread,
		EXPORT_MUSIC, info);
	app->audio.data_lengths[AUDIO_MUSIC]
		= info->header.asset_info[EXPORT_MUSIC].size;
	app->audio.data[AUDIO_LASER] = import_wav(app, thread,
		EXPORT_SOUND_LASER, info);
	app->audio.data_lengths[AUDIO_LASER]
		= info->header.asset_info[EXPORT_SOUND_LASER].size;
	app->audio.data[AUDIO_SHOT] = import_wav(app, thread,
		EXPORT_SOUND_SHOT, info);
	app->audio.data_lengths[AUDIO_SHOT]
		= info->header.asset_info[EXPORT_SOUND_SHOT].size;
	app->audio.data[AUDIO_RELOAD] = import_wav(app, thread,
		EXPORT_SOUND_RELOAD, info);
	app->audio.data_lengths[AUDIO_RELOAD]
		= info->header.asset_info[EXPORT_SOUND_RELOAD].size;
	app->audio.data[AUDIO_BUMP] = import_wav(app, thread,
		EXPORT_SOUND_BUMP, info);
	app->audio.data_lengths[AUDIO_BUMP]
		= info->header.asset_info[EXPORT_SOUND_BUMP].size;
}

/**
 * @brief Imports game assets from the level data.
 * 
 * @param app 
 * @param thread 
 * @param info 
 */
void	import_assets(t_app *app, t_thread_data *thread, t_import_info *info)
{
	import_surfaces(app, thread, info);
	import_wavs(app, thread, info);
	if (!SDL_LoadWAV_RW(SDL_RWFromConstMem(app->audio.data[AUDIO_MUSIC],
		app->audio.data_lengths[AUDIO_MUSIC]), 1,
		&app->audio.wav_spec, &app->audio.music, &app->audio.music_length))
		exit_error(MSG_ERROR_LOAD_WAV);
}
