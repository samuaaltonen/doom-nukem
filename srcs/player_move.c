/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 15:21:33 by saaltone          #+#    #+#             */
/*   Updated: 2022/12/21 15:42:17 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

static t_bool	portal_can_enter(t_app *app, int sector_id)
{
	double	target_floor;
	double	target_ceil;
	int		i;

	i = -1;
	while (++i < app->sectors[sector_id].corner_count)
	{
		if (ft_line_side(get_wall_line(app, sector_id, i), app->player.move_pos))
			return (FALSE);
	}
	target_floor = get_sector_floor_height(app, sector_id, app->player.move_pos);
	target_ceil = get_sector_ceil_height(app, sector_id, app->player.move_pos);
	if (app->player.elevation + MAX_STEP < target_floor
		|| target_ceil < app->player.elevation + PLAYER_HEIGHT)
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

static t_bool	has_been_visited(int sector_id, int *visited)
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
	visited[i] = sector_id;
	return (FALSE);
}

static t_bool	sector_collisions(t_app *app, t_vector2 *collision,
	int sector_id, int *visited)
{
	t_line		wall_line;
	t_collision	collision_type;
	int			i;
	/* int			j;
	int			member_id; */

	if (has_been_visited(sector_id, visited))
		return (TRUE);
	i = -1;
	while (++i < app->sectors[sector_id].corner_count)
	{
		wall_line = get_wall_line(app, sector_id, i);
		collision_type = circle_collision(app, sector_id, i);
		if (collision_type == COLLISION_NONE)
			continue ;
		if (collision_type == COLLISION_WALL)
			return (FALSE);
		//ft_printf("{green}Checking if can enter to %d{reset}\n", app->sectors[sector_id].wall_types[i]);
		if (!portal_can_enter(app, app->sectors[sector_id].wall_types[i]))
		{
			ft_printf("{red}CANNOT ENTER PORTAL %d{reset}\n", app->sectors[sector_id].wall_types[i]);
			return (FALSE);
		}
		if (ft_line_side(wall_line, app->player.move_pos))
			portal_enter(app, app->sectors[sector_id].wall_types[i]);
		//ft_printf("{green}Checking collisions in sector %d{reset}\n", app->sectors[sector_id].wall_types[i]);
		if (!sector_collisions(app, collision, app->sectors[sector_id].wall_types[i], visited))
		{
			//ft_printf("{red}Collision in sector %d prevent entering the protal.\n", app->sectors[sector_id].wall_types[i]);
			return (FALSE);
		}
	}
	/* i = 0;
	while (app->sectors[sector_id].member_sectors[i] >= 0)
	{
		member_id = app->sectors[sector_id].member_sectors[i];
		j = -1;
		while (++j < app->sectors[member_id].corner_count)
		{
			wall_line = get_wall_line(app, member_id, j);
			if (!circle_collision(app, member_id, j, collision))
				continue ;
			if (!portal_can_enter(app, member_id, *collision))
				return (FALSE);
			if (!ft_line_side(wall_line, app->player.move_pos))
				portal_enter(app, member_id, *collision);
		}
		i++;
	} */
	return (TRUE);
}

static t_bool	check_collisions(t_app *app, t_vector2 *collision)
{
	int	visited[MAX_VISIBLE_SECTORS];

	visited[0] = -1;
	return (sector_collisions(app, collision, app->player.current_sector, (int *)&visited));
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
	t_vector2 new;

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
	new = app->player.move_pos;
	if (!check_collisions(app, &new))
		app->player.move_pos = new;
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
