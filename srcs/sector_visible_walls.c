/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector_visible_walls.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 13:12:02 by saaltone          #+#    #+#             */
/*   Updated: 2022/10/14 15:03:11 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * Determines if wall is possibly visible from player view.
 * Checks side first. If player position is at left side of a wall, player is
 * outside of that wall.
 * After that checks if either wall corners are left side of camera plane vector
 * (so they can be visible).
 */
static void	check_possible_visible(t_app *app, int sector_id, int wall_id, t_bool is_member)
{
	t_vertex2	view;
	t_vertex2	wall_vertex;
	int			player_side;

	wall_vertex = get_wall_vertex(app, sector_id, wall_id);
	player_side = ft_vertex_side(wall_vertex, app->player.pos);
	// Not member sector, player need to on right side of all walls (clockwise)
	if (!is_member && player_side)
		return ;
	// Is member, now player need to be on left side of all walls (clockwise)
	if (is_member && !player_side)
		return ;
	view = (t_vertex2){
		app->player.pos,
		(t_vector2){app->player.pos.x + app->player.dir.x + app->player.cam.x,
			app->player.pos.y + app->player.dir.y + app->player.cam.y}
	};
	// Check if either of wall corners are left side of right view vertex
	if (!ft_vertex_side(view, wall_vertex.a)
		&& !ft_vertex_side(view, wall_vertex.b))
		return ;
	view.b = (t_vector2){app->player.pos.x + app->player.dir.x - app->player.cam.x,
			app->player.pos.y + app->player.dir.y - app->player.cam.y};
	// Check if either of wall corners are right side of left view vertex
	if (ft_vertex_side(view, wall_vertex.a)
		&& ft_vertex_side(view, wall_vertex.b))
		return ;
	app->possible_visible[app->possible_visible_count].sector_id = sector_id;
	app->possible_visible[app->possible_visible_count].wall_id = wall_id;
	app->possible_visible[app->possible_visible_count].is_member = is_member;
	app->possible_visible_count++;
}

/**
 * Loops through sectors walls to check which of them might be visible.
 */
static void	loop_sector_walls(t_app *app, int *visited, int sector_id, t_bool is_member)
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