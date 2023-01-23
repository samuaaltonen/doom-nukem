/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 13:10:34 by saaltone          #+#    #+#             */
/*   Updated: 2023/01/23 16:21:27 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H
# define MSG_USAGE "Please provide level number as an argument. \
Usage:\n./editor [level-number]"
# define MSG_ERROR "Error occured"
# define MSG_ERROR_WINDOW "Could not open a window."
# define MSG_ERROR_WINDOW_SURFACE "Could not get window surface."
# define MSG_ERROR_SDL_INIT "Could not initialize SDL."
# define MSG_ERROR_ALLOC "Could not allocate memory."
# define MSG_ERROR_IMAGE_LOAD "Loading BMP image failed."
# define MSG_ERROR_THREADS "Could not create a thread."
# define MSG_ERROR_THREADS_JOIN "Could not join threads."
# define MSG_ERROR_TEXTURE_FILE_ACCESS "Could not open/close a texture file."
# define MSG_ERROR_TEXTURE_LOAD_FAILED "Texture files are invalid."
# define MSG_ERROR_MOUSE "Could not set mouse cursor relative to the window."
# define MSG_ERROR_FILE_OPEN "Could not open a file."
# define MSG_ERROR_FILE_READ "Could not read from a file."
# define MSG_ERROR_FILE_WRITE "Could not write to a file."
# define MSG_ERROR_LEVEL_NUMBER "Level number is invalid (allowed numbers are\
 0 - 999)."
# define MSG_ERROR_LEVEL_DATA "Level data is invalid."
# define MSG_ERROR_LOAD_IMAGE "Could not load BMP file or the size is invalid."
# define MSG_ERROR_LOAD_FONT "Could not open font file or the size is invalid."
#endif