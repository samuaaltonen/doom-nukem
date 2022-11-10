/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 14:31:03 by dpalacio          #+#    #+#             */
/*   Updated: 2022/11/10 15:05:07 by htahvana         ###   ########.fr       */
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
# define MAX_RAY_DISTANCE 25.0
# define TEX_SIZE 64
# define MOUSE_SENSITIVITY 20.0
# define MAX_POLYGON_CORNERS 8
# define MAX_SECTOR_CORNERS 16
# define MAX_MEMBER_SECTORS 8
# define MAX_VISIBLE_SECTORS 64
# define MAX_VISIBLE_WALLS 256
# define MAX_VIEW_DISTANCE 100.0
# define MAX_LINE_LENGTH 1048576.0

/**
 * Struct for threads about their specific drawing areas.
 */
typedef struct s_thread_data
{
	void			*app;
	int				id;
}	t_thread_data;

/**
 * Struct for configuration variables of the application.
 */
typedef struct s_conf
{
	int				toggle_loop;
	int				toggle_help;
	int				fps;
	struct timespec	fps_clock;
	char			fps_info[20];
	double			delta_time;
	double			skybox_offset;
	int				fov;
	int				keystates;
	int				mouse_active;
	double			movement_speed;
	double			rotation_speed;
}	t_conf;

#endif
