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

static t_bool point_on_segment(t_vector2 point, t_line line)
{
	double epsilon = 0.01f;
	double len = ft_point_distance(line.a, line.b);

	double dista = ft_point_distance(point, line.a);
	double distb = ft_point_distance(point, line.b);
	if(dista + distb >= len-epsilon && dista + distb <= len+epsilon)
		return (TRUE);
	return (FALSE);
}

static int circle_collision(t_app *app, t_line wall)
{
	t_vector2 line_intersection;
	t_vector2 new_intersection;
	t_vector2 closest_start;
	t_vector2 closest_end;
	t_vector2 move_point;
	move_point = ft_vector2_add(app->player.pos, app->player.move_vector);
	t_line move_line = (t_line){app->player.pos,move_point};
	double radius = 1.f;
	t_vector2 collision;
	(void)collision;

	new_intersection = ft_closest_point(move_point, wall);
	closest_start = ft_closest_point(wall.a, move_line);
	closest_end = ft_closest_point(wall.b, move_line);
	if ((ft_point_distance(wall.a, move_point) < radius || ft_point_distance(wall.b, move_point) < radius)
			|| (ft_line_intersection(move_line, wall, &line_intersection))
			|| (ft_point_distance(new_intersection, move_point) < radius && point_on_segment(new_intersection, wall))
			|| (ft_point_distance(closest_start, wall.a) < radius && point_on_segment(closest_start, move_line))
			|| (ft_point_distance(closest_end, wall.b) < radius && point_on_segment(closest_start, move_line)))
	{
		
		//collision = ft_vector2_sub(line_intersection, ft_vector_resize(ft_vector_resize() ,radius)
		ft_printf("vector resize distance %f n",ft_vector_length(ft_vector_resize(move_point, 1.f)));
		return (1);
	}
		line_intersection.x = 0.f;
		line_intersection.y = 0.f;
	return (-1);
}
//a - r || vec aC || || vec p 1 c || * vec v || vec v ||
/**
 * @brief Checks if players new position is on the otherside of any wall,
 * 	recurses into the new sector if it's a portal,
 * 	returns -1 if the player can't be in the new position
 * 
 * @param app 
 * @param new 
 * @param wall_id 
 * @return int 
 */
static int	wall_collision_recursive(t_app *app, t_move new, int wall_id)
{
	int	i;
	int member_id;
	int counter;

	i = -1;

	while (++i < app->sectors[wall_id].corner_count)
	{
		ft_printf("Circle collision %i\n", circle_collision(app,get_wall_line(app, wall_id, i)));
		if(ft_line_side(get_wall_line(app, wall_id,i), new.pos) != 0)
		{
			//ft_printf("recursion'\n");
			wall_id = app->sectors[wall_id].wall_types[i];
			if(wall_id < 0 || (new.elevation + MAX_STEP < app->sectors[wall_id].floor_height ||
				app->sectors[wall_id].ceiling_height < new.elevation + TALL))
				return (-1);
			else
			{
				wall_id = wall_collision_recursive(app, new, wall_id);
				if(wall_id < 0)
					return (-1);
				else
				{
					app->player.current_sector = wall_id;
					if(new.elevation != app->sectors[wall_id].floor_height)
						app->player.flying = TRUE;
					return(wall_id);
				}
			} 
		}
	}

	//member sector walls
	counter = 0;
	while(app->sectors[wall_id].member_sectors[counter] >= 0)
	{
		i = -1;
		member_id = app->sectors[wall_id].member_sectors[counter];
		while (++i < app->sectors[member_id].corner_count)
		{
			if(ft_line_side(get_wall_line(app, member_id ,i), new.pos) != 0)
				break;
		}
		if(i == app->sectors[member_id].corner_count)
		{
			wall_id = wall_collision_recursive(app, new, member_id);
			if(wall_id < 0 || (new.elevation + MAX_STEP < app->sectors[wall_id].floor_height ||
				app->sectors[wall_id].ceiling_height < new.elevation + TALL))
				return (-1);
			else
			{
				app->player.current_sector = wall_id;
				if(new.elevation != app->sectors[wall_id].floor_height)
					app->player.flying = TRUE;
				return(wall_id);
			}
		}
		counter++;
	}
	return (wall_id);
}


static t_bool ceil_collision(t_app *app)
{
	if(app->sectors[app->player.current_sector].ceiling_height < app->player.elevation + TALL)
		return (FALSE);
	return (TRUE);
}

/**
 * Updates player's position if possible.
 */
void	update_position(t_app *app)
{
	t_vector2 new;

	//limit movement speed and slow player to 0
	if (ft_vector_length(app->player.move_vector) > MOVEMENT_SPEED)
		app->player.move_vector = ft_vector_resize(app->player.move_vector, MOVEMENT_SPEED);
	new = app->player.move_vector;
	app->player.move_vector = ft_vec2_lerp(app->player.move_vector, (t_vector2){0.f,0.f}, MOVE_DECEL * app->conf->delta_time);

	//if player is in the air, apply gravity(depending on jetpack), keep jumping
	if(app->player.flying)
	{
		if(app->player.jetpack)
			app->player.velocity = ft_lerp(app->player.velocity, -GRAVITY * JETPACK_FALL, app->player.jump_timer);
		else
			app->player.velocity = ft_lerp(app->player.velocity, -GRAVITY, app->player.jump_timer);
		if(app->player.jump_timer < JUMP_TIME)
		{
			app->player.jump_timer += app->conf->delta_time;
			app->player.velocity += JUMP_SIZE;
			if(app->player.jump_timer > JUMP_TIME)
				app->player.jump_timer = JUMP_TIME;
		}
		if(app->player.jetpack_boost)
			app->player.velocity += JETPACK;
	}

	ft_printf("elevation %f, floor_height%f\n", app->player.elevation, app->sectors[app->player.current_sector].floor_height);
	ft_printf("test timer %f, velocity %f jetpack %b\n", app->player.jump_timer, app->player.velocity, app->player.jetpack);
	ft_printf("closest point c x%f,y%f\n",ft_closest_point(app->player.pos, get_wall_line(app, app->player.current_sector, 0)).x, ft_closest_point(app->player.pos, get_wall_line(app, app->player.current_sector, 0)).y);
	//checks if player is under floor and resets player to floor
	if(app->player.elevation < app->sectors[app->player.current_sector].floor_height)
	{
		app->player.flying = FALSE;
		app->player.velocity = 0.f;
		app->player.jump_timer = JUMP_TIME;
		app->player.jetpack = FALSE;
		app->player.elevation = app->sectors[app->player.current_sector].floor_height;
	}
	new.x = new.x * MOVE_ACCEL * app->conf->delta_time;
	new.y = new.y * MOVE_ACCEL * app->conf->delta_time;
	new = (t_vector2){app->player.pos.x + new.x, app->player.pos.y + new.y};

	//check collissions
	if(wall_collision_recursive(app, (t_move){new, app->player.elevation}, app->player.current_sector) < 0)
	{
		app->player.move_vector = (t_vector2){0.f,0.f};
		app->player.velocity = 0.f;
		return ;
	}
	app->player.pos.y = new.y;
	app->player.pos.x = new.x;
	if(!ceil_collision(app))
	{
		app->player.jump_timer = JUMP_TIME;
		app->player.velocity = 0.f;
		app->player.elevation = app->sectors[app->player.current_sector].ceiling_height - TALL;
	}
	else
		app->player.elevation += app->player.velocity * app->conf->delta_time;
	app->player.jetpack_boost = FALSE;
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
		app->player.move_vector = ft_vector2_add(app->player.move_vector,
				(t_vector2){app->player.dir.x * app->conf->delta_time,
				app->player.dir.y * app->conf->delta_time});
	if (movement == BACKWARD)
		app->player.move_vector = ft_vector2_add(app->player.move_vector,
				(t_vector2){-app->player.dir.x * app->conf->delta_time,
				-app->player.dir.y  * app->conf->delta_time});
		
	if (movement == LEFT || movement == RIGHT)
	{
		perpendicular = ft_vector_perpendicular(app->player.dir);
		if (movement == LEFT)
			app->player.move_vector = ft_vector2_sub(app->player.move_vector,
					(t_vector2){perpendicular.x * app->conf->delta_time,
					perpendicular.y * app->conf->delta_time});
		if (movement == RIGHT)
			app->player.move_vector = ft_vector2_add(app->player.move_vector,
					(t_vector2){perpendicular.x * app->conf->delta_time,
					perpendicular.y * app->conf->delta_time});
	}
	if (movement == UP && !app->player.flying)
	{
		app->player.flying = TRUE;
		app->player.jump_timer = 0.f;
	}
	if (movement == UP && app->player.flying && app->player.jump_timer == JUMP_TIME)
	{
		app->player.jetpack_boost = TRUE;
		app->player.jetpack = TRUE;
	}
	if (movement == DOWN)
		app->player.elevation -= speed;
}
