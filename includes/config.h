/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 14:31:03 by dpalacio          #+#    #+#             */
/*   Updated: 2022/12/08 16:04:42 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

# include "doomnukem.h"

# define WIN_NAME "Doom Nukem"
# define WIN_W 1280
# define WIN_H 720
# define THREAD_COUNT 6
# define IMAGE_PIXEL_BYTES 4
# define IMAGE_PIXEL_BITS 32
# define COLLISION_OFFSET 0.25
# define FOV 66
# define TEX_SIZE 64
# define SKYBOX_W 1024 // Optimal size 4x2.5 of window size (5120x1800)
# define SKYBOX_H 1024
# define MOUSE_SENSITIVITY_HORIZONTAL 0.3
# define MOUSE_SENSITIVITY_VERTICAL 0.2
# define MAX_SECTOR_CORNERS 16
# define MAX_MEMBER_SECTORS 8
# define MAX_VISIBLE_SECTORS 64
# define MAX_VISIBLE_WALLS 256
# define MAX_VIEW_DISTANCE 256.f
# define MAX_LINE_LENGTH 1048576.0
# define MAX_OBJECTS 64
# define MAX_UNIQUE_OBJECTS 64
# define MAX_INTERACTIONS 64
# define MAX_UNIQUE_INTERACTIONS 7
# define MAX_DECOR 10
# define PARTIALLY_TRANSPARENT_PORTAL_TEXTURE_ID 1
# define DECOR_SIZE 1.0
# define INTERACTION_ACTION_DISTANCE 1.5
# define MAX_CONCURRENT_ANIMATIONS 16
# define ANIMATION_DURATION_LIGHT 0.5 // seconds per light level
# define ANIMATION_DURATION_HEIGHT 0.25 // seconds per meter
# define ANIMATION_DURATION_TEXT 0.015625 // seconds per char
# define ANIMATION_DURATION_TEXT_END 3.5 // seconds after full text displayed
# define MAX_TEXT_LINES 16
# define MAX_TEXT_LINE_LENGTH 1024

/**
 * Struct for threads about their specific identifiers and locks for signaling.
 */
typedef struct s_thread_data
{
	void			*app;
	int				id;
	t_bool			has_work;
	pthread_t		thread;
	pthread_cond_t	cond;
	pthread_mutex_t	lock;
}	t_thread_data;

/**
 * Struct for configuration variables of the application.
 */
typedef struct s_conf
{
	int				toggle_loop;
	int				toggle_help;
	int				fps;
	int				fps_avg;
	int				frames_total;
	int				fps_total;
	int				fps_chunk;
	struct timespec	fps_clock;
	char			fps_info[20];
	double			delta_time;
	double			skybox_offset;
	int				fov;
	int				keystates;
	int				buttonstates;
	int				mouse_active;
	double			movement_speed;
	double			rotation_speed;
}	t_conf;

#endif
