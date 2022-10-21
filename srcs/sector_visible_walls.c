/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector_visible_walls.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 13:12:02 by saaltone          #+#    #+#             */
/*   Updated: 2022/10/21 18:23:49 by saaltone         ###   ########.fr       */
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
static void	check_possible_visible(t_app *app, t_wall *walls, int *walls_count, t_wall wall)
{
	t_bool		is_inside;
	t_bool		is_portal;
	t_vertex2	wall_vertex;
	int			player_side;

	is_inside = !wall.is_member;
	wall_vertex = get_wall_vertex(app, wall.sector_id, wall.wall_id);
	player_side = ft_vertex_side(wall_vertex, app->player.pos);
	// Not member sector, player need to on right side of all walls (clockwise)
	if (!wall.is_member && player_side)
		return ;
	is_portal = FALSE;
	if (app->sectors[wall.sector_id].wall_types[wall.wall_id] != -1 || wall.is_member)
		is_portal = TRUE;
	/** Is member, now player need to be on left side of all walls. If not, mark
	 * wall as not portal (it is now only considered as "inside" wall within
	 * portal/member) */
	if (wall.is_member && !player_side)
		is_inside = TRUE;
	if (!has_visible_corner(app, wall_vertex))
		return ;
	walls[*walls_count] = wall;
	walls[*walls_count].is_portal = is_portal;
	walls[*walls_count].is_inside = is_inside;
	*walls_count = *walls_count + 1;
}

/**
 * @brief Returns TRUE if a sector has already been visited. If not, sets sector
 * as visited.
 * 
 * @param visited 
 * @param sector_id 
 * @return t_bool 
 */
static t_bool	has_been_visited(int *visited, int sector_id)
{
	int	i;

	i = 0;
	while (i < MAX_VISIBLE_SECTORS)
	{
		if (visited[i] == -1)
			break ;
		if (visited[i] == sector_id)
			return (TRUE);
		i++;
	}
	if (i == MAX_VISIBLE_SECTORS)
		return (TRUE);
	visited[i] = sector_id;
	if (i < MAX_VISIBLE_SECTORS - 1)
		visited[i + 1] = -1;
	return (FALSE);
}

/**
 * Loops through sectors walls to check which of them might be visible.
 */
static void	loop_sector_walls(t_app *app, t_wall *walls, int *walls_count, int *interested,
	int sector_id, t_bool is_member)
{
	int			i;
	t_sector	*sector;
	t_wall		wall;

	sector = &app->sectors[sector_id];
	// Loop through member sector walls
	i = -1;
	while (++i < MAX_MEMBER_SECTORS)
	{
		// Break loop when -1 is found (no members after that anyways)
		if (sector->member_sectors[i] == -1)
			break ;
		loop_sector_walls(app, walls, walls_count, interested, sector->member_sectors[i], TRUE);
	}
	// Loop through sector walls
	i = -1;
	while (++i < sector->corner_count)
	{
		// If wall is a portal, add portal destination to be interesting sector
		if (sector->wall_types[i] != -1)
		{
			*(interested + 1) = sector->wall_types[i];
			*(interested + 2) = -1;
		}
		wall.sector_id = sector_id;
		wall.wall_id = i;
		wall.is_member = is_member;
		check_possible_visible(app, walls, walls_count, wall);
	}
}

/**
 * @brief Copies walls from sector based array to main array that is used for
 * rendering.
 * 
 * @param app 
 * @param walls 
 * @param wall_count 
 */
void	sector_walls_copy(t_app *app, t_wall *walls, int wall_count)
{
	int	previously_copied;
	int	i;

	previously_copied = app->visible_walls_count;
	i = 0;
	while (i < wall_count)
	{
		ft_printf("Copying wall %d,%d\n", walls[i].sector_id, walls[i].wall_id);
		app->visible_walls[i + previously_copied] = walls[i];
		app->visible_walls_count++;
		i++;
	}
}

/**
 * Sets possible visible walls to possible_visible array.
 */
void	sector_visible_walls(t_app *app)
{
	t_wall	visible_walls[MAX_VISIBLE_SECTORS][(MAX_MEMBER_SECTORS + 1) * MAX_SECTOR_CORNERS];
	int		visible_count[MAX_VISIBLE_SECTORS + 1];
	int		already_visited[MAX_VISIBLE_SECTORS];
	int		interested_in[MAX_VISIBLE_SECTORS];
	int		i;

	already_visited[0] = -1;
	interested_in[0] = app->player.current_sector;
	interested_in[1] = -1;
	i = 0;
	while (interested_in[i] != -1 && i < MAX_VISIBLE_SECTORS - 1)
	{
		visible_count[i] = 0;
		visible_count[i + 1] = -1;
		if (!has_been_visited((int *)&already_visited, interested_in[i]))
			loop_sector_walls(app, (t_wall *)&visible_walls[i], &visible_count[i], &interested_in[i], interested_in[i], FALSE);
		i++;
	}
	/**
	 * Order walls and stack them to main array for rendering
	 */
	i = 0;
	app->visible_walls_count = 0;
	while (visible_count[i] > 0)
	{
		ft_printf("group %d, wall count %d\n", i, visible_count[i]);
		sector_walls_prepare(app, (t_wall *)&visible_walls[i], visible_count[i]);
		sector_walls_order(app, (t_wall *)&visible_walls[i], visible_count[i]);
		sector_walls_copy(app, (t_wall *)&visible_walls[i], visible_count[i]);
		i++;
	}
}