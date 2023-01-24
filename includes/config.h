/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 14:31:03 by dpalacio          #+#    #+#             */
/*   Updated: 2023/01/19 18:54:38 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

# define WIN_NAME "Doom Nukem"
# define WIN_W 1280
# define WIN_H 720
# define THREAD_COUNT 5
# define THREAD_DEADLOCK_CHECK 10000000
# define FOV 83
# define MOUSE_SENSITIVITY_HORIZONTAL 0.2
# define MOUSE_SENSITIVITY_VERTICAL 0.2
# define MAX_SECTOR_COUNT 4096
# define MIN_SECTOR_CORNERS 3
# define MAX_SECTOR_CORNERS 16
# define MAX_MEMBER_SECTORS 16
# define MAX_VISIBLE_SECTORS 64
# define MAX_VISIBLE_WALLS 256
# define MAX_VIEW_DISTANCE 1280.0
# define MAX_LINE_LENGTH 1048576.0
# define SMALL_SCALE 0.34375
# define SPRITE_ANGLES 90
# define MAX_SMALL_OBJECTS 7
# define MAX_BIG_OBJECTS 7
# define MAX_ENEMY_TYPES 3
# define MAX_DECOR_TYPES 4
# define MAX_PROJECTILES 8
# define MAX_OBJECT_TYPES 17
# define MAX_OBJECT_DISTANCE 128.0
# define MAX_FOG_DISTANCE 40.0
/* object type defines for now
	< MAX_SMALL_OBJECTS = small objects
	< MAX_SMALL_OBJECTS + MAX_BIG_OBJECTS = big objects
	< MAX_SMALL_OBJECTS + MAX_BIG_OBJECTS + MAX_ENEMY_TYPES = enemy
	>= MAX_SMALL_OBJECTS + MAX_BIG_OBJECTS + MAX_ENEMY_TYPES = bullets
*/
# define ENEMY_COLLISION 0.25f
# define PROJECTILE_COLLISION_X 0.25f
# define PROJECTILE_COLLISION_Y 0.5f
# define PICKUP_RANGE 0.5f
# define MAX_OBJECTS 128
# define MAX_TEMP_OBJECTS 64
# define MAX_INTERACTIONS 64
# define MAX_UNIQUE_INTERACTIONS 7
# define PARTIALLY_TRANSPARENT_TEXTURE_ID 3
# define FULLY_TRANSPARENT_TEXTURE_ID 4
# define MAX_GRAVITY -1.0
# define MIN_GRAVITY -50.0
# define DEFAULT_GRAVITY -20.0

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
	int				fov;
	int				keystates;
	int				buttonstates;
	int				mouse_active;
}	t_conf;

#endif
