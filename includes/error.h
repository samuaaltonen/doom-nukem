/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 14:51:24 by dpalacio          #+#    #+#             */
/*   Updated: 2023/01/16 18:27:08 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define MSG_ERROR "Error occured"
# define MSG_ERROR_WINDOW "Could not open a window."
# define MSG_ERROR_WINDOW_SURFACE "Could not get window surface."
# define MSG_ERROR_SDL_INIT "Could not initialize SDL."
# define MSG_ERROR_ALLOC "Could not allocate memory."
# define MSG_ERROR_LOAD_WAV "Could not load wav data."
# define MSG_ERROR_IMAGE_INIT "Image initialization failed."
# define MSG_ERROR_AUDIO_DEVICE "Could not use audio device. Please check \
audio driver. When PulseAudio/Alsa is used (linux), check that \
following environment variable are set: \nexport SDL_AUDIODRIVER=alsa \
\nexport AUDIODEV pulse\n\nAlso make sure following packages are installed:\n\
libasound2-dev libpulse-dev (if you just installed these packages, also remake \
sdl)"
# define MSG_ERROR_THREADS "Could not create a thread."
# define MSG_ERROR_THREADS_SIGNAL "Error with waking up a thread or \
locking/unlocking a mutex."
# define MSG_ERROR_THREADS_MUTEX "Error with locking/unlocking a mutex."
# define MSG_ERROR_TEXTURE_FILE_ACCESS "Could not open/close a texture file."
# define MSG_ERROR_TEXTURE_LOAD_FAILED "Texture files are invalid."
# define MSG_ERROR_MOUSE "Could not set mouse cursor relative to the window."
# define MSG_ERROR_FILE_OPEN "Could not open a file."
# define MSG_ERROR_FILE_READ "Could not read from a file."

# define MSG_ERROR_IMPORT "Level file is invalid."
# define MSG_ERROR_IMPORT_SECTOR "Level file is invalid. Could not import \
sectors."
# define MSG_ERROR_IMPORT_PLAYER "Level file is invalid. Could not import \
player."
# define MSG_ERROR_IMPORT_OBJECT "Level file is invalid. Could not import \
objects."
# define MSG_ERROR_IMPORT_INTERACTION "Level file is invalid. Could not import \
interactions."
# define MSG_ERROR_IMPORT_SURFACE "Level file is invalid. Could not import \
image assets."
# define MSG_ERROR_IMPORT_AUDIO "Level file is invalid. Could not import \
audio assets."
# define MSG_ERROR_IMPORT_TEXT "Level file is invalid. Could not import \
text data."

# define MSG_ERROR_VALIDATION_SECTOR "Level file has invalid sector data."
# define MSG_ERROR_VALIDATION_ASSETS "Level file has invalid asset data."
# define MSG_ERROR_VALIDATION_INTERACTION "Level file has invalid interaction \
data."
# define MSG_ERROR_VALIDATION_PLAYER "Level file has invalid player data."
# define MSG_ERROR_VALIDATION_OBJECT "Level file has invalid object data."

#endif
