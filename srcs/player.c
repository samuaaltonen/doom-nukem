 /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 15:21:33 by saaltone          #+#    #+#             */
/*   Updated: 2022/10/11 14:11:58 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * Checks wall collisions for given position.
 */
/* static int	is_collision(t_app *app, t_vector2 pos)
{
	(void)app;
	(void)pos;
	if (pos.x >= app->map_size.x || pos.y >= app->map_size.y)
		return (1);
	if (pos.x < 0 || pos.y < 0)
		return (1);
	if (app->map[(int)pos.y][(int)pos.x][0] > 'A'
		&& app->map[(int)pos.y][(int)pos.x][0] != DOOR_MAP_ID_MOVING)
		return (1);
	return (0);
} */

static t_bool	is_wall_collision(t_app *app, t_move new)
{
	int	i;
	int	wall_id;

	i = 0;
	while (i < app->sectors[app->player.current_sector].corner_count)
	{
		if(ft_line_side(get_wall_line(app, app->player.current_sector,i), new.pos) != 0)
		{
			wall_id = app->sectors[app->player.current_sector].wall_types[i];
			if(wall_id < 0 || (new.elevation + 0.2f < app->sectors[wall_id].floor_height ||
				app->sectors[wall_id].ceiling_height - app->sectors[wall_id].floor_height < 0.6f))
				return (FALSE);
			else
			{
				app->player.elevation = app->player.elevation + (app->sectors[wall_id].floor_height - app->sectors[app->player.current_sector].floor_height);
				app->player.current_sector = wall_id;
				return (TRUE);
			}
		}
		i++;
	}
	return (TRUE);

}

/**
 * Updates player's position if possible.
 */
void	update_position(t_app *app)
{
	t_vector2 new;

	if (ft_vector_length(app->player.move_vector) > MOVEMENT_SPEED)
		app->player.move_vector = ft_vector_resize(app->player.move_vector, MOVEMENT_SPEED);
	new = app->player.move_vector;
	app->player.move_vector = ft_vec2_lerp(app->player.move_vector, (t_vector2){0.f,0.f}, MOVE_DECEL * app->conf->delta_time);
	new.x = new.x * MOVE_ACCEL;
	new.y = new.y * MOVE_ACCEL;
	//ft_printf("movevector x%f,y%f, delta%f, len%f, velocity%f, keystates%.32b\n", app->player.move_vector.x, app->player.move_vector.y, app->conf->delta_time, ft_vector_length(app->player.move_vector),app->player.velocity, app->conf->keystates);
	new = (t_vector2){app->player.pos.x + new.x, app->player.pos.y + new.y};
	if(!is_wall_collision(app, (t_move){new, app->player.elevation}))
		return ;
	app->player.pos.y = new.y;
	app->player.pos.x = new.x;
}


/**
 * Rotates player direction by given angle.
 */
void	player_rotate(t_app *app, double angle)
{
	t_matrix2	rotation;

	rotation = (t_matrix2){
		(t_vector2){cos(angle), -sin(angle)},
		(t_vector2){sin(angle), cos(angle)}
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
	if (!(movement == FORWARD || movement == BACKWARD
			|| movement == LEFT || movement == RIGHT || movement == UP
			|| movement == DOWN))
		return ;
	if (movement == FORWARD)
	{
		app->player.move_vector = ft_vector2_add(app->player.move_vector, (t_vector2){app->player.dir.x * app->conf->delta_time, app->player.dir.y * app->conf->delta_time});
		//ft_vector3_limit(&(app->player.move_vector), MOVEMENT_SPEED);
		/* new = (t_vector2){app->player.pos.x + app->player.dir.x * speed,
			app->player.pos.y + app->player.dir.y * speed}; */
	}
	if (movement == BACKWARD)
	{
		app->player.move_vector = ft_vector2_add(app->player.move_vector, (t_vector2){-app->player.dir.x * app->conf->delta_time,-app->player.dir.y  * app->conf->delta_time});
		//ft_vector3_limit(&(app->player.move_vector), MOVEMENT_SPEED);
	/* 	new = (t_vector2){app->player.pos.x - app->player.dir.x * speed,
			app->player.pos.y - app->player.dir.y * speed}; */
	}
		
	if (movement == LEFT || movement == RIGHT)
	{
		perpendicular = ft_vector_perpendicular(app->player.dir);
		if (movement == LEFT)
		{
			app->player.move_vector = ft_vector2_sub(app->player.move_vector, (t_vector2){perpendicular.x * app->conf->delta_time,perpendicular.y * app->conf->delta_time});
			//ft_vector3_limit(&(app->player.move_vector), MOVEMENT_SPEED);
			/* new = (t_vector2){app->player.pos.x - perpendicular.x * speed,
				app->player.pos.y - perpendicular.y * speed}; */
		}
		if (movement == RIGHT)
		{
			app->player.move_vector = ft_vector2_add(app->player.move_vector, (t_vector2){perpendicular.x * app->conf->delta_time,perpendicular.y * app->conf->delta_time});
			//ft_vector3_limit(&(app->player.move_vector), MOVEMENT_SPEED);
			/* new = (t_vector2){app->player.pos.x + perpendicular.x * speed,
				app->player.pos.y + perpendicular.y * speed}; */
		}
	}
	//new = (t_vector2){app->player.pos.x + app->player.move_vector.x, app->player.pos.y + app->player.move_vector.y};
	//----DEBUG FLY
	if (movement == UP)
		app->player.elevation += speed;
	if (movement == DOWN)
		app->player.elevation -= speed;
	//----
	//update_position(app, new);
}
