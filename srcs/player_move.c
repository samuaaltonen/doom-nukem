/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 15:21:33 by saaltone          #+#    #+#             */
/*   Updated: 2022/12/20 15:20:17 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * @brief Checks if player can move to target sector (if not too high elevation
 * difference with floor/ceiling). If moving to the sector is possible, changes
 * player sector id.
 * 
 * @param app 
 * @param portal_id 
 * @return t_bool 
 */
static t_bool	enter_portal(t_app *app, int portal_id, t_vector2 pos)
{
	double	target_floor;
	double	target_ceil;

	target_floor = get_sector_floor_height(app, portal_id, pos);
	target_ceil = get_sector_ceil_height(app, portal_id, pos);
	if (app->player.elevation + MAX_STEP < target_floor
		|| target_ceil < app->player.elevation + PLAYER_HEIGHT)
		return (FALSE);
	app->player.current_sector = portal_id;
	interaction_check_portal(app, portal_id);
	if (app->player.elevation != target_floor)
		app->player.flying = TRUE;
	ft_printf("{cyan}Entering to portal %d.{reset}\n", portal_id);
	return (TRUE);
}

//circle collide all walls, pass only collided & ignored portals to recursive wall traversal
static t_bool	wall_collisions(t_app *app, t_vector2 *collision)
{
	t_line	wall_line;
	int		i;
	int		j;
	int		member_id;

	i = -1;
	while (++i < app->sectors[app->player.current_sector].corner_count)
	{
		wall_line = get_wall_line(app, app->player.current_sector, i);
		if (!circle_collision(app, wall_line, collision))
			continue ;
		if (app->sectors[app->player.current_sector].wall_types[i] == -1
			|| app->sectors[app->player.current_sector].wall_textures[i]
				== PARTIALLY_TRANSPARENT_TEXTURE_ID)
		{
			ft_printf("{cyan}Collision with wall id %d.{reset}\n", i);
			return (TRUE);
		}
		if (!ft_line_side(wall_line, app->player.pos))
			return (FALSE);
		if (!enter_portal(app, app->sectors[app->player.current_sector].wall_types[i], *collision))
			return (TRUE);
		ft_printf("{green}Collision with portal %d to sector %d. Entering portal.{reset}\n", i, app->sectors[app->player.current_sector].wall_types[i]);
	}
	i = 0;
	while (app->sectors[app->player.current_sector].member_sectors[i] >= 0)
	{
		member_id = app->sectors[app->player.current_sector].member_sectors[i];
		j = -1;
		while (++j < app->sectors[member_id].corner_count)
		{
			if (!circle_collision(app, get_wall_line(app, member_id, j), collision))
				continue ;
			return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

//a - r || vec aC || || vec p 1 c || * vec v || vec v ||
/**
 * @brief Checks if players new position is on the otherside of any wall,
 * 	recurses into the new sector if it's a portal,
 * 	returns -1 if the player can't be in the new position
 * 
 * @param app 
 * @param new 
 * @param sector_id 
 * @return int 
 */
/* static int	wall_traversal_recursive(t_app *app, t_move new, int sector_id)
{
	t_line	wall_line;
	int		i;
	int		member_id;
	int		portal_id;
	int		counter;

	i = -1;
	while (++i < app->sectors[sector_id].corner_count)
	{
		wall_line = get_wall_line(app, sector_id, i);
		if (!ft_line_side(wall_line, new.pos))
			continue ;
		if (!ft_line_intersection_segment((t_line){app->player.pos, new.pos}, wall_line, NULL))
			continue ;
		portal_id = app->sectors[sector_id].wall_types[i];
		if (portal_id < 0
			|| (new.elevation + MAX_STEP < app->sectors[portal_id].floor_height
				||	app->sectors[portal_id].ceil_height < new.elevation + PLAYER_HEIGHT))
			return (-1);
		else
		{
			if (app->sectors[sector_id].wall_textures[i] == PARTIALLY_TRANSPARENT_TEXTURE_ID)
				return (-1);
			portal_id = wall_traversal_recursive(app, new, portal_id);
			if (portal_id < 0)
				return (-1);
			else
			{
				app->player.current_sector = portal_id;
				interaction_check_portal(app, portal_id);
				if (new.elevation != app->sectors[portal_id].floor_height)
					app->player.flying = TRUE;
				return (portal_id);
			}
		}
	}

	//member sector walls
	counter = 0;
	while(app->sectors[sector_id].member_sectors[counter] >= 0)
	{
		i = -1;
		member_id = app->sectors[sector_id].member_sectors[counter];
		while (++i < app->sectors[member_id].corner_count)
		{
			if(ft_line_side(get_wall_line(app, member_id ,i), new.pos) != 0)
				break;
		}
		if(i == app->sectors[member_id].corner_count)
		{
			portal_id = wall_traversal_recursive(app, new, member_id);
			if (portal_id < 0
				|| (new.elevation + MAX_STEP < get_sector_floor_height(app, portal_id, new.pos)
					||	get_sector_ceil_height(app, portal_id, new.pos) < new.elevation + PLAYER_HEIGHT))
				return (-1);
			else
			{
				app->player.current_sector = portal_id;
				interaction_check_portal(app, portal_id);
				if(new.elevation != app->sectors[portal_id].floor_height)
					app->player.flying = TRUE;
				return(portal_id);
			}
		}
		counter++;
	}
	return (sector_id);
} */

static t_bool ceil_collision(t_app *app)
{
	if(get_sector_ceil_height(app, app->player.current_sector, app->player.pos) < app->player.elevation + PLAYER_HEIGHT)
		return (FALSE);
	return (TRUE);
}

/**
 * @brief Limits player movement speed to maximum value. Also if movement is
 * very small, round to 0.
 * 
 * @param app 
 */
static t_bool	limit_speed(t_app *app)
{
	double	speed;

	speed = ft_vector_length(app->player.move_vector);
	if (speed < MOVE_MIN)
	{
		app->player.move_vector = (t_vector2){0.0, 0.0};
		return (FALSE);
	}
	if (app->player.is_decelerating)
		app->player.move_vector = ft_vec2_lerp(app->player.move_vector,
			(t_vector2){0.f, 0.f}, MOVE_DECEL * app->conf->delta_time);
	if (speed > app->player.move_speed)
		app->player.move_vector = ft_vector_resize(app->player.move_vector,
			app->player.move_speed);
	return (TRUE);
}

/**
 * @brief Updates player's position if possible.
 * 
 * @param app 
 */
void	update_position(t_app *app)
{
	t_vector2 new;

	if (!limit_speed(app))
		return ;

	app->player.move_pos = ft_vector2_add(app->player.pos, ft_vec2_mult(app->player.move_vector, app->conf->delta_time));
	new = app->player.move_pos;

	double	pos_floor_height = get_sector_floor_height(app, app->player.current_sector, app->player.pos);

	if (!app->player.flying && app->player.elevation > pos_floor_height)
		app->player.elevation = pos_floor_height;

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
	
	if (app->player.elevation < pos_floor_height)
	{
		app->player.flying = FALSE;
		app->player.velocity = 0.f;
		app->player.jump_timer = JUMP_TIME;
	//	app->player.jetpack = FALSE;
		app->player.elevation = pos_floor_height;
	}

	/* if(wall_traversal_recursive(app, (t_move){new, app->player.elevation}, app->player.current_sector) < 0)
	{
		app->player.move_vector = (t_vector2){0.f,0.f};
		app->player.velocity = 0.f;
		return ;
	} */
	if (wall_collisions(app, &new))
		app->player.move_pos = new;
	if (wall_collisions(app, &new))
	{
		app->player.move_vector = (t_vector2){0.f,0.f};
		app->player.move_pos = new;
	}
	app->player.pos = app->player.move_pos;
	if(!ceil_collision(app))
	{
		app->player.jump_timer = JUMP_TIME;
		app->player.velocity = 0.f;
		app->player.elevation = get_sector_ceil_height(app, app->player.current_sector, app->player.pos) - PLAYER_HEIGHT;
	}
	else
		app->player.elevation += app->player.velocity * app->conf->delta_time;
	app->player.jetpack_boost = FALSE;
}

/**
 * @brief Moves player to given direction if there is no collision.
 * 
 * @param app 
 * @param movement 
 * @param speed 
 */
void	player_move(t_app *app, t_movement movement, double speed)
{
	t_vector2	perpendicular;

	if (!(movement == FORWARD || movement == BACKWARD
			|| movement == LEFTWARD || movement == RIGHTWARD 
			|| movement == UPWARD || movement == DOWNWARD))
		return ;
	app->player.is_decelerating = FALSE;
	if (movement == FORWARD)
		app->player.move_vector = ft_vector2_add(app->player.move_vector,
				(t_vector2){app->player.dir.x * speed,
				app->player.dir.y * speed});
	if (movement == BACKWARD)
		app->player.move_vector = ft_vector2_add(app->player.move_vector,
				(t_vector2){-app->player.dir.x * speed,
				-app->player.dir.y  * speed});
		
	if (movement == LEFTWARD || movement == RIGHTWARD)
	{
		perpendicular = ft_vector_perpendicular(app->player.dir);
		if (movement == LEFTWARD)
			app->player.move_vector = ft_vector2_sub(app->player.move_vector,
					(t_vector2){perpendicular.x * speed,
					perpendicular.y * speed});
		if (movement == RIGHTWARD)
			app->player.move_vector = ft_vector2_add(app->player.move_vector,
					(t_vector2){perpendicular.x * speed,
					perpendicular.y * speed});
	}
	if (movement == UPWARD && !app->player.flying)
	{
		app->player.flying = TRUE;
		app->player.jump_timer = 0.0;
	}
	if (movement == UPWARD && app->player.flying && app->player.jump_timer == JUMP_TIME)
	{
		//----DEBUG FEATURE
		if (app->player.jetpack == TRUE)
			app->player.jetpack_boost = TRUE;
		//----
		// app->player.jetpack = TRUE;
	}
	if (movement == DOWNWARD)
		app->player.elevation -= speed;
}
