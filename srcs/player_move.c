/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 15:21:33 by saaltone          #+#    #+#             */
/*   Updated: 2022/12/21 19:36:56 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

t_bool	portal_can_enter(t_app *app, t_line wall, int source_sector, int target_sector)
{
	t_vector2	check_pos;
	double		source_floor;
	double		source_ceil;
	double		target_floor;
	double		target_ceil;

	check_pos = ft_closest_point(app->player.move_pos, wall);
	source_floor = get_sector_floor_height(app, source_sector, check_pos);
	source_ceil = get_sector_ceil_height(app, source_sector, check_pos);
	target_floor = get_sector_floor_height(app, target_sector, check_pos);
	target_ceil = get_sector_ceil_height(app, target_sector, check_pos);
	if (app->player.elevation + MAX_STEP < target_floor
		&& source_floor + MAX_STEP < target_floor)
		return (FALSE);
	if (target_ceil < app->player.elevation + PLAYER_HEIGHT
		&& source_ceil - MAX_STEP > target_ceil)
		return (FALSE);
	return (TRUE);
}

static void	portal_enter(t_app *app, int sector_id)
{
	double	target_floor;

	target_floor = get_sector_floor_height(app, sector_id, app->player.move_pos);
	app->player.current_sector = sector_id;
	interaction_check_portal(app, sector_id);
	if (app->player.elevation != target_floor)
		app->player.flying = TRUE;
	ft_printf("{cyan}Entering to portal %d.{reset}\n", sector_id);
}

/**
 * @brief Returns TRUE if coordinate is located inside a sector.
 * 
 * @param app 
 * @param sector_id 
 * @param coord 
 * @return t_bool 
 */
static t_bool	inside_sector(t_app *app, int sector_id, t_vector2 coord)
{
	int	i;

	i = 0;
	while (i < app->sectors[sector_id].corner_count)
	{
		if (ft_line_side(get_wall_line(app, sector_id, i), coord))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

static t_bool	has_been_visited(int sector_id, int *visited, t_bool set_visited)
{
	int	i;

	i = 0;
	while (i < MAX_VISIBLE_SECTORS && visited[i] != -1)
	{
		if (visited[i] == sector_id)
			return (TRUE);
		i++;
	}
	if (i == MAX_VISIBLE_SECTORS)
		return (TRUE);
	if (!set_visited)
		return (FALSE);
	ft_printf("{cyan}Setting sector %d as visited.{reset}\n", sector_id);
	visited[i] = sector_id;
	visited[i + 1] = -1;
	return (FALSE);
}

static t_bool	member_collisions(t_app *app, int sector_id)
{
	t_collision	collision_type;
	int			i;
	int			j;
	int			member_id;

	i = -1;
	while (++i < MAX_MEMBER_SECTORS
		&& app->sectors[sector_id].member_sectors[i] >= 0)
	{
		member_id = app->sectors[sector_id].member_sectors[i];
		j = -1;
		while (++j < app->sectors[member_id].corner_count)
		{
			collision_type = circle_collision(app, member_id, j, member_id);
			if (collision_type == COLLISION_NONE)
				continue ;
			if (collision_type == COLLISION_WALL)
			{
				ft_printf("Collision with member sector %d\n", member_id);
				return (FALSE);
			}
			if (!inside_sector(app, member_id, app->player.move_pos))
				continue ;
			portal_enter(app, member_id);
			break ;
		}
	}
	return (TRUE);
}

static t_bool	sector_collisions(t_app *app, int sector_id, int *visited)
{
	t_collision	collision_type;
	t_line		wall_line;
	int			i;
	int			portal_id;

	if (has_been_visited(sector_id, visited, TRUE)){
		ft_printf("Sector %d has already been visited, skipping.\n", sector_id);
		return (TRUE);
	}
	if (!member_collisions(app, sector_id))
		return (FALSE);
	i = -1;
	while (++i < app->sectors[sector_id].corner_count)
	{
		wall_line = get_wall_line(app, sector_id, i);
		portal_id = app->sectors[sector_id].wall_types[i];
		collision_type = circle_collision(app, sector_id, i, portal_id);
		if (collision_type == COLLISION_NONE)
			continue ;
		if (collision_type == COLLISION_WALL)
			return (FALSE);
		if (has_been_visited(portal_id, visited, FALSE))
		{
			if (app->sectors[sector_id].parent_sector == portal_id
				&& inside_sector(app, portal_id, app->player.move_pos))
				portal_enter(app, portal_id);
			continue ;
		}
		if (inside_sector(app, portal_id, app->player.move_pos)
			&& !inside_sector(app, sector_id, app->player.move_pos))
			portal_enter(app, portal_id);
		ft_printf("{yellow}Checking collisions in sector %d{reset}\n", portal_id);
		if (!sector_collisions(app, portal_id, visited))
		{
			ft_printf("{red}Collision in sector %d prevent entering the protal.\n", portal_id);
			portal_enter(app, sector_id);
			return (FALSE);
		}
		ft_printf("{green}No collisions in sector %d{reset}\n", portal_id);
	}
	return (TRUE);
}

static t_bool	check_collisions(t_app *app)
{
	int	visited[MAX_VISIBLE_SECTORS + 1];

	visited[0] = -1;
	return (sector_collisions(app, app->player.current_sector, (int *)&visited));
}

static t_bool ceil_collision(t_app *app)
{
	if (get_sector_ceil_height(app, app->player.current_sector, app->player.pos) < app->player.elevation + PLAYER_HEIGHT)
		return (TRUE);
	return (FALSE);
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

	if (app->player.elevation_velocity < GRAVITY)
		app->player.elevation_velocity = GRAVITY;
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
	double	pos_floor_height = get_sector_floor_height(app, app->player.current_sector, app->player.pos);

	if (!app->player.flying && app->player.elevation > pos_floor_height)
		app->player.elevation = pos_floor_height;

	if(app->player.flying)
	{
		if (app->player.jetpack)
			app->player.elevation_velocity = GRAVITY * JETPACK_FALL;
		else
			app->player.elevation_velocity += GRAVITY * app->conf->delta_time;
	}

	if (ceil_collision(app))
		app->player.elevation = get_sector_ceil_height(app, app->player.current_sector, app->player.pos) - PLAYER_HEIGHT;
	else
		app->player.elevation += app->player.elevation_velocity * app->conf->delta_time;

	if (app->player.elevation < pos_floor_height)
	{
		//ft_printf("stepping %f\n", app->player.elevation);
		if (!app->player.jetpack)
		{
			app->player.flying = FALSE;
			app->player.elevation_velocity = 0.0;
		}
		//app->player.elevation = ft_lerp(app->player.elevation, pos_floor_height, app->player.step_timer);
		app->player.elevation = pos_floor_height;
		app->player.step_timer += app->conf->delta_time;
	}
	else
		app->player.step_timer = 0.0;

	if (!limit_speed(app))
		return ;

	app->player.move_pos = ft_vector2_add(app->player.pos, ft_vec2_mult(app->player.move_vector, app->conf->delta_time));
	check_collisions(app);
	/* if (!check_collisions(app, &new))
	{
		app->player.move_vector = (t_vector2){0.f, 0.f};
		app->player.move_pos = new;
	} */
	app->player.pos = app->player.move_pos;
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
	ft_printf("========================\n");
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
	if ((movement == UPWARD || movement == DOWNWARD) && app->player.jetpack)
		app->player.elevation += speed;
	if (movement == UPWARD && !app->player.jetpack && !app->player.flying)
	{
		app->player.flying = TRUE;
		app->player.elevation_velocity = speed;
	}
}
