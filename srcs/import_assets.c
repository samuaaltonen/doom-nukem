/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import_assets.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 14:39:23 by saaltone          #+#    #+#             */
/*   Updated: 2023/01/23 17:02:33 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * @brief Imports game assets from the level data.
 * 
 * @param app 
 * @param thread 
 * @param info 
 */
void	import_assets(t_app *app, t_import_info *info)
{
	if (app->assets_imported)
		return ;
	if (info->length - info->imported <= 0)
		exit_error(MSG_ERROR_LOAD_ASSETS);
	import_surfaces(app, info);
	if (app->assets.font.font)
		change_font(app, 16, BLACK);
	import_wavs(app, info);
	if (!SDL_LoadWAV_RW(SDL_RWFromConstMem(app->audio.data[AUDIO_MUSIC],
				app->audio.data_lengths[AUDIO_MUSIC]), 1,
			&app->audio.wav_spec, &app->audio.music, &app->audio.music_length))
		exit_error(MSG_ERROR_LOAD_WAV);
	import_texts(app, info);
	app->assets_imported = TRUE;
}
