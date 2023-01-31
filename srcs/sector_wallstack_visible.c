/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector_wallstack_visible.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 15:49:36 by saaltone          #+#    #+#             */
/*   Updated: 2023/01/31 15:06:00 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * @brief Returns TRUE if given line has any part visible to player.
 * 
 * - If both corners of the wall are in view cone returns TRUE
 * - If not, then check intersection points with view lines: Extend view
 *   lines and check intersection with the wall and return TRUE if either of
 *   the intersection coordinates are left of camera plane (in front of player).
 * 
 * @param app 
 * @param wall 
 * @return t_bool 
 */
static t_bool	has_visible_part(t_app *app, t_line wall)
{
	t_line		left;
	t_line		right;
	t_vector2	intersection;

	left = (t_line){app->player.pos, ft_vector2_add(app->player.pos,
			ft_vec2_mult(ft_vector2_sub(app->player.dir, app->player.cam),
				MAX_VIEW_DISTANCE))};
	right = (t_line){app->player.pos, ft_vector2_add(app->player.pos,
			ft_vec2_mult(ft_vector2_add(app->player.dir, app->player.cam),
				MAX_VIEW_DISTANCE))};
	if (ft_line_side(right, wall.a) && ft_line_side(right, wall.b)
		&& !ft_line_side(left, wall.a) && !ft_line_side(left, wall.b))
		return (TRUE);
	if (ft_line_intersection_segment(left, wall, &intersection)
		|| ft_line_intersection_segment(right, wall, &intersection))
		return (TRUE);
	return (FALSE);
}

/**
 * @brief Checks for duplicate walls in the wallstack. Duplicate is defined as
 * having identical endpoints. If duplicate is found, only keep the wall that
 * is closer to the player.
 * 
 * @param app 
 * @param walls 
 * @param walls_count 
 * @param wall 
 * @return int 
 */
static int	check_duplicate(t_app *app, t_wall *walls, int *walls_count,
	t_wall wall)
{
	int	i;

	i = -1;
	while (++i < *walls_count)
	{
		if (!(walls[i].line.a.x == wall.line.a.x
				&& walls[i].line.a.y == wall.line.a.y
				&& walls[i].line.b.x == wall.line.b.x
				&& walls[i].line.b.y == wall.line.b.y)
			&& !(walls[i].line.a.x == wall.line.b.x
				&& walls[i].line.a.y == wall.line.b.y
				&& walls[i].line.b.x == wall.line.a.x
				&& walls[i].line.b.y == wall.line.a.y))
			continue ;
		if (get_relative_wall_distance(app->player.pos, walls[i].line)
			< get_relative_wall_distance(app->player.pos, wall.line))
			return (*walls_count);
		return (i);
	}
	return (*walls_count);
}

/**
 * @brief Determines if wall is possibly visible from player view.
 * Checks side first. If player position is at left side of a wall, player is
 * outside of that wall (unless member sectors wall).
 * After that checks if either wall corners are left side of camera plane vector
 * (so they can be visible).
 * 
 * @param app 
 * @param walls 
 * @param walls_count 
 * @param wall 
 */
static void	check_possible_visible(t_app *app, t_wall *walls, int *walls_count,
	t_wall wall)
{
	int	add_index;
	int	player_side;

	wall.is_inside = !wall.is_member;
	wall.line = get_wall_line(app, wall.sector_id, wall.wall_id);
	player_side = ft_line_side(wall.line, app->player.pos);
	if (ft_line_point(wall.line, app->player.pos))
		player_side = 1;
	if (!wall.is_member && player_side)
		return ;
	wall.is_portal = FALSE;
	if (app->sectors[wall.sector_id].wall_types[wall.wall_id] != -1
		|| wall.is_member)
		wall.is_portal = TRUE;
	if (wall.is_member && !player_side)
		wall.is_inside = TRUE;
	if (!has_visible_part(app, wall.line))
		return ;
	add_index = check_duplicate(app, walls, walls_count, wall);
	walls[add_index] = wall;
	if (add_index == *walls_count)
		*walls_count = *walls_count + 1;
}

/**
 * @brief Initializes wall struct.
 * 
 * @param wall 
 * @param sector 
 * @param sector_id 
 * @param wall_index 
 */
static void	initialize_wall_data(t_wall *wall, t_sector *sector, int sector_id,
	int wall_index)
{
	wall->sector_id = sector_id;
	wall->wall_id = wall_index;
	wall->wall_type = sector->wall_types[wall_index];
	if (sector->parent_sector != -1)
		wall->is_member = TRUE;
	else
		wall->is_member = FALSE;
}

/**
 * @brief Loops through sectors walls to check which of them might be visible.
 * If it encounters a wall that is portal, adds that portals destination sector
 * to interesting array in wallstack (to be also visited).
 * 
 * @param app 
 * @param wallstack 
 * @param index 
 * @param sector_id 
 */
void	sector_visible_walls(t_app *app, t_wallstack *wallstack, int index,
	int sector_id)
{
	int			i;
	t_sector	*sector;
	t_wall		wall;

	ft_bzero(&wall, sizeof(t_wall));
	sector = &app->sectors[sector_id];
	sector->stack_index = index;
	i = -1;
	while (++i < MAX_MEMBER_SECTORS && sector->member_sectors[i] != -1)
		sector_visible_walls(app, wallstack, index, sector->member_sectors[i]);
	i = -1;
	while (++i < sector->corner_count)
	{
		if (sector->parent_sector == -1 && sector->wall_types[i] != -1)
		{
			wallstack->interesting[wallstack->interesting_count]
				= sector->wall_types[i];
			wallstack->interesting_count++;
		}
		initialize_wall_data(&wall, sector, sector_id, i);
		check_possible_visible(app, (t_wall *)&wallstack->walls[index],
			(int *)&wallstack->wall_count[index], wall);
	}
}
