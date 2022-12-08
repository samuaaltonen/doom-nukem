/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 14:31:03 by dpalacio          #+#    #+#             */
/*   Updated: 2022/12/08 19:41:02 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

# include "doomnukem.h"

# define WIN_NAME "Doom Nukem"
# define WIN_W 1280
# define WIN_H 720
# define THREAD_COUNT 1
# define IMAGE_PIXEL_BYTES 4
# define IMAGE_PIXEL_BITS 32
# define COLLISION_OFFSET 0.25
# define FOV 66
# define TEX_SIZE 64
# define TEX_PICKUP 44
# define TEX_OBJECT 128
# define SKYBOX_W 1024 // Optimal size 4x2.5 of window size (5120x1800 for 1280x720)
# define SKYBOX_H 1024
# define MOUSE_SENSITIVITY_HORIZONTAL 0.3
# define MOUSE_SENSITIVITY_VERTICAL 0.2
# define MAX_SECTOR_CORNERS 16
# define MAX_MEMBER_SECTORS 8
# define MAX_VISIBLE_SECTORS 64
# define MAX_VISIBLE_WALLS 256
# define MAX_VIEW_DISTANCE 256.f
# define MAX_LINE_LENGTH 1048576.0
# define SPRITE_ANGLES 90
# define MAX_SMALL_OBJECTS 5
# define MAX_BIG_OBJECTS 5
# define MAX_ENEMY_TYPES 1
# define MAX_PROJECTILES 5
# define MAX_OBJECT_DISTANCE 15.f
/* object type defines for now
	< MAX_SMALL_OBJECTS = small objects
	< MAX_SMALL_OBJECTS + MAX_BIG_OBJECTS = big objects
	< MAX_SMALL_OBJECTS + MAX_BIG_OBJECTS + MAX_ENEMY_TYPES = enemy
	>= MAX_SMALL_OBJECTS + MAX_BIG_OBJECTS + MAX_ENEMY_TYPES = projectiles
*/
# define MAX_ENEMY_STATES 3
# define MAX_OBJECTS 64
# define MAX_TEMP_OBJECTS 64
# define MAX_INTERACTIONS 64
# define MAX_UNIQUE_INTERACTIONS 7
# define MAX_DECOR 10
# define PARTIALLY_TRANSPARENT_PORTAL_TEXTURE_ID 1
# define DECOR_SIZE 1.0

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
