/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <danielmdc94@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 15:21:55 by dpalacio          #+#    #+#             */
/*   Updated: 2022/10/19 15:23:49 by dpalacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# include "doomnukem.h"

# define DIRECTION_START_X 0.0
# define DIRECTION_START_Y 1.0
# define POSITION_START_X 0.0
# define POSITION_START_Y 0.0
# define ROTATION_SPEED 1.8f
# define MOVEMENT_SPEED 3.2f

/**
 * Movement direction enumeration.
 */
typedef enum e_movement {
	FORWARD = 0,
	BACKWARD = 1,
	LEFT = 2,
	RIGHT = 3
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
	int				current_sector;
}	t_player;

#endif