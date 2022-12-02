/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <danielmdc94@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 15:21:55 by dpalacio          #+#    #+#             */
/*   Updated: 2022/12/02 13:12:10 by dpalacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# define DIRECTION_START_X 0.0
# define DIRECTION_START_Y 1.0
# define POSITION_START_X 0.5
# define POSITION_START_Y 0.5
# define ROTATION_SPEED 1.8
# define MOVEMENT_SPEED 5.0
# define HORIZON_UPPER_LIMIT 1.25
# define HORIZON_LOWER_LIMIT -0.25
# define MAX_HP 200

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
	int		fire_rate;
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
	t_vector2		cam;
	double			camera_length;
	double			height;
	double			elevation;
	double			horizon;
	int				current_sector;
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
} t_move;

#endif
