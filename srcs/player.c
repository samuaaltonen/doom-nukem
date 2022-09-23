/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 15:21:33 by saaltone          #+#    #+#             */
/*   Updated: 2022/08/08 17:24:27 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * Checks wall collisions for given position.
 */
static int	is_collision(t_app *app, t_vector2 pos)
{
	(void)app;
	(void)pos;
	/* if (pos.x >= app->map_size.x || pos.y >= app->map_size.y)
		return (1);
	if (pos.x < 0 || pos.y < 0)
		return (1);
	if (app->map[(int)pos.y][(int)pos.x][0] > 'A'
		&& app->map[(int)pos.y][(int)pos.x][0] != DOOR_MAP_ID_MOVING)
		return (1); */
	return (0);
}

/**
 * Updates player's position if possible.
 */
static void	update_position(t_app *app, t_vector2 new)
{
	if (!is_collision(app, (t_vector2){new.x - COLLISION_OFFSET,
			app->player.pos.y - COLLISION_OFFSET})
		&& !is_collision(app, (t_vector2){new.x - COLLISION_OFFSET,
			app->player.pos.y + COLLISION_OFFSET})
		&& !is_collision(app, (t_vector2){new.x + COLLISION_OFFSET,
			app->player.pos.y - COLLISION_OFFSET})
		&& !is_collision(app, (t_vector2){new.x + COLLISION_OFFSET,
			app->player.pos.y + COLLISION_OFFSET}))
		app->player.pos.x = new.x;
	if (!is_collision(app, (t_vector2){app->player.pos.x - COLLISION_OFFSET,
			new.y - COLLISION_OFFSET})
		&& !is_collision(app, (t_vector2){app->player.pos.x - COLLISION_OFFSET,
			new.y + COLLISION_OFFSET})
		&& !is_collision(app, (t_vector2){app->player.pos.x + COLLISION_OFFSET,
			new.y - COLLISION_OFFSET})
		&& !is_collision(app, (t_vector2){app->player.pos.x + COLLISION_OFFSET,
			new.y + COLLISION_OFFSET}))
		app->player.pos.y = new.y;
}

/**
 * Rotates player direction by given angle.
 */
void	player_rotate(t_app *app, double angle)
{
	t_matrix2	rotation;

	rotation = (t_matrix2){
		(t_vector2){cos(angle), sin(angle)},
		(t_vector2){-sin(angle), cos(angle)}
	};
	app->player.dir = ft_vector_multiply_matrix(app->player.dir, rotation);
	app->player.cam = ft_vector_multiply_matrix(app->player.cam, rotation);
	app->conf->skybox_offset = fmod(app->conf->skybox_offset + 720.f, 720.f)
		+ angle * RADIAN_IN_DEG;
}

/**
 * Moves player to given direction if there is no collision.
 */
void	player_move(t_app *app, t_movement movement, double speed)
{
	t_vector2	perpendicular;
	t_vector2	new;

	if (!(movement == FORWARD || movement == BACKWARD
			|| movement == LEFT || movement == RIGHT))
		return ;
	if (movement == FORWARD)
		new = (t_vector2){app->player.pos.x + app->player.dir.x * speed,
			app->player.pos.y + app->player.dir.y * speed};
	if (movement == BACKWARD)
		new = (t_vector2){app->player.pos.x - app->player.dir.x * speed,
			app->player.pos.y - app->player.dir.y * speed};
	if (movement == LEFT || movement == RIGHT)
	{
		perpendicular = ft_vector_perpendicular(app->player.dir);
		if (movement == LEFT)
			new = (t_vector2){app->player.pos.x - perpendicular.x * speed,
				app->player.pos.y - perpendicular.y * speed};
		if (movement == RIGHT)
			new = (t_vector2){app->player.pos.x + perpendicular.x * speed,
				app->player.pos.y + perpendicular.y * speed};
	}
	update_position(app, new);
}
