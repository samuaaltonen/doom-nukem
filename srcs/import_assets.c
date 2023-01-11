/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import_assets.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 14:39:23 by saaltone          #+#    #+#             */
/*   Updated: 2023/01/11 18:56:30 by saaltone         ###   ########.fr       */
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
void	import_assets(t_app *app, t_thread_data *thread, t_import_info *info)
{
	import_surfaces(app, thread, info);
	if (app->assets.font.font)
		change_font(app, 16, BLACK);
	import_wavs(app, thread, info);
	if (!SDL_LoadWAV_RW(SDL_RWFromConstMem(app->audio.data[AUDIO_MUSIC],
				app->audio.data_lengths[AUDIO_MUSIC]), 1,
			&app->audio.wav_spec, &app->audio.music, &app->audio.music_length))
		exit_error(MSG_ERROR_LOAD_WAV);
	import_texts(app, thread, info);
}
