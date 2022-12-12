/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 14:51:24 by dpalacio          #+#    #+#             */
/*   Updated: 2022/12/08 15:17:32 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define MSG_ERROR "Error occured"
# define MSG_ERROR_WINDOW "Could not open a window."
# define MSG_ERROR_WINDOW_SURFACE "Could not get window surface."
# define MSG_ERROR_SDL_INIT "Could not initialize SDL."
# define MSG_ERROR_ALLOC "Could not allocate memory."
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
# define MSG_ERROR_TEXTURE_FILE_ACCESS "Could not open/close a texture file."
# define MSG_ERROR_TEXTURE_LOAD_FAILED "Texture files are invalid."
# define MSG_ERROR_FONT "Could not open font file."
# define MSG_ERROR_MOUSE "Could not set mouse cursor relative to the window."
# define MSG_ERROR_FILE_READ "Could not read from a file."

#endif
