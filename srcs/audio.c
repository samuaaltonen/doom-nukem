/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <danielmdc94@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 13:35:37 by dpalacio          #+#    #+#             */
/*   Updated: 2023/01/24 17:03:18 by dpalacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * @brief Queues music data to audio device.
 * 
 * @param app 
 */
void	play_music(t_app *app)
{
	if (SDL_GetQueuedAudioSize(app->audio.device_id) == 0 && app->audio.music)
	{
		SDL_FreeWAV(app->audio.music);
		if (!SDL_LoadWAV_RW(SDL_RWFromConstMem(app->audio.data[AUDIO_MUSIC],
					app->audio.data_lengths[AUDIO_MUSIC]), 1,
				&app->audio.wav_spec,
				&app->audio.music,
				&app->audio.music_length))
			exit_error(MSG_ERROR_LOAD_WAV);
		SDL_QueueAudio(app->audio.device_id, app->audio.music,
			app->audio.music_length);
		SDL_PauseAudioDevice(app->audio.device_id, 0);
	}
}

/**
 * @brief Mixes sound data with music and queues the result to audio device.
 * 
 * @param app 
 * @param audio_type 
 */
void	play_sound(t_app *app, int audio_type)
{
	t_uint32	size;
	t_uint8		*ptr;

	if (!app->audio.music)
		return ;
	if (!SDL_LoadWAV_RW(SDL_RWFromConstMem(app->audio.data[audio_type],
				app->audio.data_lengths[audio_type]), 1,
			&app->audio.wav_spec, &app->audio.sound, &app->audio.sound_length))
		exit_error(MSG_ERROR_LOAD_WAV);
	if (!app->audio.sound)
		exit_error(MSG_ERROR);
	size = SDL_GetQueuedAudioSize(app->audio.device_id);
	if (size <= app->audio.sound_length)
	{
		SDL_FreeWAV(app->audio.sound);
		return ;
	}
	ptr = app->audio.music + app->audio.music_length - size;
	SDL_ClearQueuedAudio(app->audio.device_id);
	SDL_MixAudioFormat(ptr, app->audio.sound, app->audio.wav_spec.format,
		app->audio.sound_length, SDL_MIX_MAXVOLUME);
	SDL_QueueAudio(app->audio.device_id, ptr, size);
	SDL_PauseAudioDevice(app->audio.device_id, 0);
	SDL_FreeWAV(app->audio.sound);
}

void	pause_audio(t_app *app)
{
	SDL_PauseAudioDevice(app->audio.device_id, 1);
}

void	unpause_audio(t_app *app)
{
	SDL_PauseAudioDevice(app->audio.device_id, 0);
}

void	stop_audio(t_app *app)
{
	SDL_ClearQueuedAudio(app->audio.device_id);
}
