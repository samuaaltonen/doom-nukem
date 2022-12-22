/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 14:31:03 by dpalacio          #+#    #+#             */
/*   Updated: 2022/12/23 00:26:15 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

# define WIN_NAME "Doom Nukem"
# define WIN_W 1280
# define WIN_H 720
# define THREAD_COUNT 6
# define IMAGE_PIXEL_BYTES 4
# define IMAGE_PIXEL_BITS 32
# define FOV 83
# define TEX_SIZE 128
# define TEX_PICKUP 44
# define TEX_OBJECT 128
# define SKYBOX_W 1536
# define SKYBOX_H 1088
# define MOUSE_SENSITIVITY_HORIZONTAL 0.2
# define MOUSE_SENSITIVITY_VERTICAL 0.2
# define MAX_SECTOR_CORNERS 16
# define MAX_MEMBER_SECTORS 16
# define MAX_VISIBLE_SECTORS 64
# define MAX_VISIBLE_WALLS 256
# define MAX_VIEW_DISTANCE 1280.0
# define MAX_LINE_LENGTH 1048576.0
# define SMALL_SCALE 0.34375
# define SPRITE_ANGLES 90
# define MAX_SMALL_OBJECTS 5
# define MAX_BIG_OBJECTS 3
# define MAX_ENEMY_TYPES 2
# define MAX_PROJECTILES 3
# define MAX_OBJECT_DISTANCE 128.0
/* object type defines for now
	< MAX_SMALL_OBJECTS = small objects
	< MAX_SMALL_OBJECTS + MAX_BIG_OBJECTS = big objects
	< MAX_SMALL_OBJECTS + MAX_BIG_OBJECTS + MAX_ENEMY_TYPES = enemy
	>= MAX_SMALL_OBJECTS + MAX_BIG_OBJECTS + MAX_ENEMY_TYPES = projectiles
*/
# define MAX_ENEMY_STATES 2
# define MAX_OBJECTS 128
# define MAX_TEMP_OBJECTS 64
# define MAX_INTERACTIONS 64
# define MAX_UNIQUE_INTERACTIONS 7
# define MAX_DECOR 10
# define PARTIALLY_TRANSPARENT_TEXTURE_ID 0
# define FULLY_TRANSPARENT_TEXTURE_ID 1

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

typedef struct s_level_header
{
	int	version;
	int	sector_count;
	int	object_count;
	int	interaction_count;
}	t_level_header;

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
	int				fov;
	t_level_header	header;
	int				keystates;
	int				buttonstates;
	int				mouse_active;
}	t_conf;

#endif
