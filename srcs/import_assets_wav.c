/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import_assets_wav.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 18:46:21 by saaltone          #+#    #+#             */
/*   Updated: 2023/01/11 18:46:43 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

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
	audio_data = (t_uint8 *)malloc(asset_info.size);
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
void	import_wavs(t_app *app, t_thread_data *thread, t_import_info *info)
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
