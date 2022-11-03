/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 15:21:55 by dpalacio          #+#    #+#             */
/*   Updated: 2022/11/03 15:53:36 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# define DIRECTION_START_X -1.0
# define DIRECTION_START_Y 0.0
# define POSITION_START_X 3.0
# define POSITION_START_Y 12.0
# define ROTATION_SPEED 1.8f
# define MOVEMENT_SPEED 1.0f

/**
 * Movement direction enumeration.
 */
typedef enum e_movement {
	FORWARD = 0,
	BACKWARD = 1,
	LEFT = 2,
	RIGHT = 3,
	UP = 4,
	DOWN = 5
}	t_movement;

/**
 * Struct for player. Contains players position, direction and camera plane.
 */
typedef struct s_player
{
	t_vector2		pos;
	t_vector2		dir;
	t_vector2		cam;
	double			camera_length;
	double			height;
	double			elevation;
	double			horizon;
	int				current_sector;
}	t_player;

typedef struct s_move
{
	t_vector2	pos;
	double		elevation;
} t_move;

#endif
