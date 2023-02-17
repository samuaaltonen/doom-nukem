/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 14:31:03 by dpalacio          #+#    #+#             */
/*   Updated: 2023/02/17 15:06:56 by saaltone         ###   ########.fr       */
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
# define MOUSE_SENSITIVITY_HORIZONTAL 0.001
# define MOUSE_SENSITIVITY_VERTICAL 0.001
# define HAND_TURN_SPEED 3.0
# define HAND_MOVE_SPEED 100.0
# define HAND_FIRE_SPEED 5000.0
# define HAND_SPEED 10
# define MAX_SECTOR_COUNT 4096
# define MIN_SECTOR_CORNERS 3
# define MAX_SECTOR_CORNERS 16
# define MAX_MEMBER_SECTORS 16
# define MAX_VISIBLE_SECTORS 92
# define MAX_VISIBLE_WALLS 256
# define MAX_VIEW_DISTANCE 1280.0
# define MAX_LINE_LENGTH 1048576.0
# define SMALL_SCALE 0.34375
# define SPRITE_ANGLES 90
# define MAX_SMALL_OBJECTS 8
# define MAX_BIG_OBJECTS 7
# define MAX_ENEMY_TYPES 3
# define MAX_DECOR_TYPES 9
# define MAX_PROJECTILES 8
# define MAX_OBJECT_TYPES 18
# define MAX_OBJECT_DISTANCE 128.0
# define MIN_FOG_DISTANCE 2.0
# define MAX_FOG_DISTANCE 40.0
# define ENEMY_COLLISION 0.25
# define PROJECTILE_COLLISION_X 0.25
# define PROJECTILE_COLLISION_Y 0.5
# define PROJECTILE_ENEMY 3
# define PROJECTILE_ROCKET 5
# define PROJECTILE_EXPLOSION 1
# define PICKUP_RANGE 0.5
# define WEAPON_SIZE 864.0
# define MAX_OBJECTS 128
# define MAX_TEMP_OBJECTS 64
# define MAX_INTERACTIONS 64
# define MAX_UNIQUE_INTERACTIONS 7
# define PARTIALLY_TRANSPARENT_TEXTURE_ID 8
# define FULLY_TRANSPARENT_TEXTURE_ID 9
# define MAX_GRAVITY -1.0
# define MIN_GRAVITY -50.0
# define DEFAULT_GRAVITY -20.0
# define RANDOM_GENERATOR_RANGE 1000000
# define MAX_LEVEL 999
# define LEVEL_IDENTIFIER "level-"
# define FILE_NAME_LENGTH 9
# define DEFAULT_LEVEL "level-0"

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
