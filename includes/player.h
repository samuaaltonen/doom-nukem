/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 15:21:55 by dpalacio          #+#    #+#             */
/*   Updated: 2022/12/21 15:34:39 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# define DIRECTION_START_X 0.0
# define DIRECTION_START_Y 1.0
# define POSITION_START_X 0.5
# define POSITION_START_Y 0.5
# define ROTATION_SPEED 1.8
# define MOVEMENT_SPEED 6.0
# define RUNNING_SPEED 10.0
# define MOVE_RANGE 0.05
# define MOVE_ACCEL 90.0
# define MOVE_DECEL 5.0
# define MOVE_MIN 0.0001
# define GRAVITY -20.0
# define JUMP_FORCE 5.0
# define JETPACK 1.0
# define JETPACK_FALL 0.01
# define JETPACK_ASCENT 4.0
# define JETPACK_DESCENT -4.0
# define MAX_STEP 0.3
# define MAX_ANGLE 45.0
# define HORIZON_UPPER_LIMIT 1.25
# define HORIZON_LOWER_LIMIT -0.25
# define PLAYER_HEIGHT 0.5
# define COLLISION_OFFSET 0.25
# define MAX_HP 200
# define REGEN_TIME 5

/**
 * Movement direction enumeration.
 */
typedef enum e_movement
{
	FORWARD = 0,
	BACKWARD = 1,
	LEFTWARD = 2,
	RIGHTWARD = 3,
	UPWARD = 4,
	DOWNWARD = 5
}	t_movement;

typedef enum e_collision
{
	COLLISION_WALL,
	COLLISION_PORTAL,
	COLLISION_NONE
}	t_collision;

typedef struct s_inventory
{
	int			ammo;
	int			special_ammo;
	int			potion;
	int			antidote;
	int			key;
	t_bool		jetpack;
}	t_inventory;

typedef struct s_weapon
{
	t_bool	enabled;
	int		damage;
	int		range;
	double	fire_rate;
	int		magazine;
	int		ammo;
}	t_weapon;

/**
 * Struct for player. Contains players position, direction and camera plane.
 */
typedef struct s_player
{
	t_vector2		pos;
	t_vector2		dir;
	t_vector2		move_vector;
	t_vector2		move_pos;
	double			move_speed;
	t_bool			is_decelerating;
	t_vector2		cam;
	double			camera_length;
	double			elevation;
	double			elevation_velocity;
	double			horizon;
	int				current_sector;
	t_bool			flying;
	t_bool			jetpack;
	t_bool			jetpack_boost;
	double			jump_timer;
	double			step_timer;
	int				hp;
	int				weapons;
	t_weapon		equiped_weapon;
	int				shield;
	t_inventory		inventory;
}	t_player;

typedef struct s_export_player
{
	t_vector2		position;
	t_vector2		direction;
	int				sector;
	int				health;
	int				weapons;
	int				armor;
	t_inventory		inventory;
}	t_export_player;

typedef struct s_move
{
	t_vector2	pos;
	double		elevation;
}	t_move;

#endif
