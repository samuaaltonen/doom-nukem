/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector_visible_walls.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 13:12:02 by saaltone          #+#    #+#             */
/*   Updated: 2022/10/21 13:02:15 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * Returns TRUE if given vertex has either corners visible to player.
 * 
 * - If both corners of the wall are in view cone returns TRUE
 * - If not, then check intersection points with view vertices: Extend view
 *   vertices and check intersection with the wall and return TRUE if either of
 *   the intersection coordinates are left of camera plane (in front of player).
*/
static t_bool	has_visible_corner(t_app *app, t_vertex2 wall)
{
	t_vertex2	left;
	t_vertex2	right;
	t_vertex2	view_camera;
	t_vector2	intersection;

	view_camera = (t_vertex2){app->player.pos,
		(t_vector2){app->player.pos.x + app->player.cam.x,
		app->player.pos.y + app->player.cam.y}};
	left = (t_vertex2){app->player.pos,
		(t_vector2){app->player.pos.x + app->player.dir.x - app->player.cam.x,
		app->player.pos.y + app->player.dir.y - app->player.cam.y}};
	right = (t_vertex2){app->player.pos,
		(t_vector2){app->player.pos.x + app->player.dir.x + app->player.cam.x,
		app->player.pos.y + app->player.dir.y + app->player.cam.y}};
	if (ft_vertex_side(right, wall.a) && ft_vertex_side(right, wall.b)
		&& !ft_vertex_side(left, wall.a) && !ft_vertex_side(left, wall.b))
		return (TRUE);
	left = ft_vertex_resize(left, MAX_VERTEX_LENGTH, EXTEND_BOTH);
	right = ft_vertex_resize(right, MAX_VERTEX_LENGTH, EXTEND_BOTH);
	if ((ft_vertex_intersection(left, wall, &intersection)
			&& ft_vertex_side(view_camera, intersection))
		|| (ft_vertex_intersection(right, wall, &intersection)
			&& ft_vertex_side(view_camera, intersection)))
		return (TRUE);
	return (FALSE);
}

/**
 * Determines if wall is possibly visible from player view.
 * Checks side first. If player position is at left side of a wall, player is
 * outside of that wall.
 * After that checks if either wall corners are left side of camera plane vector
 * (so they can be visible).
 */
static void	check_possible_visible(t_app *app, int sector_id, int wall_id,
	t_bool is_member)
{
	t_bool		is_inside;
	t_bool		is_portal;
	t_vertex2	wall_vertex;
	int			player_side;

	is_inside = !is_member;
	wall_vertex = get_wall_vertex(app, sector_id, wall_id);
	player_side = ft_vertex_side(wall_vertex, app->player.pos);
	// Not member sector, player need to on right side of all walls (clockwise)
	if (!is_member && player_side)
		return ;
	is_portal = FALSE;
	if (app->sectors[sector_id].wall_types[wall_id] != -1 || is_member)
		is_portal = TRUE;
	/** Is member, now player need to be on left side of all walls. If not, mark
	 * wall as not portal (it is now only considered as "inside" wall within
	 * portal/member) */
	if (is_member && !player_side)
		is_inside = TRUE;
	if (!has_visible_corner(app, wall_vertex))
		return ;
	app->possible_visible[app->possible_visible_count].sector_id = sector_id;
	app->possible_visible[app->possible_visible_count].wall_id = wall_id;
	app->possible_visible[app->possible_visible_count].is_member = is_member;
	app->possible_visible[app->possible_visible_count].is_portal = is_portal;
	app->possible_visible[app->possible_visible_count].is_inside = is_inside;
	app->possible_visible_count++;
}

/**
 * Loops through sectors walls to check which of them might be visible.
 */
static void	loop_sector_walls(t_app *app, int *visited, int sector_id,
	t_bool is_member)
{
	int	i;

	i = 0;
	// Check if sector has already been visited in this function, stop if it has
	while (i < MAX_VISIBLE_SECTORS)
	{
		if (visited[i] == -1)
			break ;
		if (visited[i] == sector_id)
			return ;
		i++;
	}
	// Stop anyways if visited already MAX_VISIBLE_SECTORS
	if (i == MAX_VISIBLE_SECTORS)
		return ;
	// Mark this sector as visited
	visited[i] = sector_id;
	// Set next for -1 in visited array
	if (i < MAX_VISIBLE_SECTORS - 1)
		visited[i + 1] = -1;
	// Loop through member sector walls
	i = 0;
	while (i < MAX_MEMBER_SECTORS)
	{
		// Break loop when -1 is found (no members after that anyways)
		if (app->sectors[sector_id].member_sectors[i] == -1)
			break ;
		loop_sector_walls(app, visited, app->sectors[sector_id].member_sectors[i], TRUE);
		i++;
	}
	// Loop through sector walls
	i = 0;
	while (i < app->sectors[sector_id].corner_count)
	{
		// If wall is portal, recurse into portal
		if (app->sectors[sector_id].wall_types[i] != -1)
			loop_sector_walls(app, visited, app->sectors[sector_id].wall_types[i], FALSE);
		// Check if wall is possibly visible, if yes add to possible_visible array
		check_possible_visible(app, sector_id, i, is_member);
		i++;
	}
}

/**
 * Sets possible visible walls to possible_visible array.
 */
void	sector_visible_walls(t_app *app)
{
	int	already_visited[MAX_VISIBLE_SECTORS];

	app->possible_visible_count = 0;
	already_visited[0] = -1;
	loop_sector_walls(app, (int *)&already_visited,
		app->player.current_sector, FALSE);
}