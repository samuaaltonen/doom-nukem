/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector_possible_visible_walls.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 13:12:02 by saaltone          #+#    #+#             */
/*   Updated: 2022/10/10 12:11:47 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * Checks order of 2 given walls.
 *
 * Ordering is done by extending other wall (a) to infinity and then checking
 * for intersection points with the other wall (b). If there is no intersection
 * and wall (b) both corners are at the same side as player position relative
 * to extended wall then drawing priority is with wall (b).
 * If wall (b) both corners are at different side as player position
 * relative to extended (a) wall, then priority is with wall (a).
 * If there is intersection, extend the other one. (if both cases has intersect,
 * then order doesn't matter (invalid sector)).
 */
static t_bool	walls_in_order(t_app *app, int wall_a, int wall_b)
{
	t_vertex2	a;
	t_vertex2	b;
	t_vertex2	extended;
	t_vector2	intersection;
	t_bool		right_side;
	int			extended_wall;

	if (!app->possible_visible[wall_a].is_member
		|| !app->possible_visible[wall_b].is_member)
		return (TRUE);
	a = get_sector_vertex_by_corner(app, app->possible_visible[wall_a].sector_id, app->possible_visible[wall_a].wall_id);
	b = get_sector_vertex_by_corner(app, app->possible_visible[wall_a].sector_id, app->possible_visible[wall_a].wall_id);

	// Extend wall_a to infinity / very long
	extended = ft_vertex_resize(a, MAX_VERTEX_LENGTH, EXTEND_BOTH);
	extended_wall = wall_a;

	// Check intersection
	if (ft_vertex_intersection(extended, b, &intersection))
	{
		extended = ft_vertex_resize(b, MAX_VERTEX_LENGTH, EXTEND_BOTH);
		extended_wall = wall_a;
	}

	/** 
	 * Check side with player pos. Can be done with 2 dimensional cross
	 * product. Cross product between a vector from extended vertex starting
	 * point to test point and vector from vertex starting to end points.
	 */
	// Get player side (true if right side of vertex)
	right_side = ft_vector_crossproduct((t_vector2){app->player.pos.x - extended.a.x, app->player.pos.y - extended.a.y}, 
		(t_vector2){extended.b.x - extended.a.x, extended.b.y - extended.a.y}) > 0;

	// Check if both points of other vertex are at the same side as player
	if (right_side != ft_vector_crossproduct(
		(t_vector2){a.a.x - extended.a.x, a.a.y - extended.a.y}, 
		(t_vector2){extended.b.x - extended.a.x, extended.b.y - extended.a.y}) > 0
		|| right_side != ft_vector_crossproduct(
			(t_vector2){a.b.x - extended.a.x, a.b.y - extended.a.y}, 
			(t_vector2){extended.b.x - extended.a.x, extended.b.y - extended.a.y}) > 0)
		return (extended_wall == wall_b);
	return (extended_wall == wall_a);
}

/**
 * Orders walls depending on visibility. Only orders walls that came from member
 * sectors. Other walls should already be in order (if all sectors convex).
 */
static void	order_possible_visible_walls(t_app *app)
{
	t_wall	temp;
	t_bool	in_order;
	int		i;

	in_order = FALSE;
	while (!in_order)
	{
		in_order = TRUE;
		i = 0;
		while (i < app->possible_visible_count - 1)
		{
			// Checks if 2 walls are in order and flip when necessary
			if (!walls_in_order(app, i, i + 1))
			{
				temp = app->possible_visible[i];
				app->possible_visible[i] = app->possible_visible[i + 1];
				app->possible_visible[i + 1] = temp;
				in_order = FALSE;
			}
			i++;
		}
	}
}

/**
 * Determines if wall is possibly visible from player view.
 * Takes dot product of player direction vector and wall vector. If dot 
 * product >= 0, wall is in front of player.
 *
 * For member sectors need to be opposite (dot product <= 0) (outside walls).
 */
static void	check_possible_visible(t_app *app, int sector_id, int wall_id, t_bool is_member)
{
	t_vector2	wall_vector;
	double		dot_product;

	if (test_sectors[sector_id].corner_count == wall_id + 1)
		wall_vector = (t_vector2){
			test_sectors[sector_id].corners[0].x - test_sectors[sector_id].corners[wall_id].x,
			test_sectors[sector_id].corners[0].y - test_sectors[sector_id].corners[wall_id].y
		};
	else
		wall_vector = (t_vector2){
			test_sectors[sector_id].corners[wall_id + 1].x - test_sectors[sector_id].corners[wall_id].x,
			test_sectors[sector_id].corners[wall_id + 1].y - test_sectors[sector_id].corners[wall_id].y
		};
	dot_product = ft_vector_dotproduct(app->player.dir, wall_vector);
	if ((dot_product >= 0.0 && !is_member) || (dot_product <= 0.0 && is_member))
	{
		/* ft_printf("maybe visible, wall id %d from %f,%f to %f,%f\n",
			wall_id,
			test_sectors[sector_id].corners[wall_id].x,
			test_sectors[sector_id].corners[wall_id].y,
			test_sectors[sector_id].corners[wall_id].x + wall_vector.x,
			test_sectors[sector_id].corners[wall_id].y + wall_vector.y); */
		app->possible_visible[app->possible_visible_count] = (t_wall){sector_id, wall_id, is_member};
		app->possible_visible_count++;
	}
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
	// Loop through member sector walls
	i = 0;
	while (i < MAX_MEMBER_SECTORS)
	{
		// Break loop when -1 is found (no members after that anyways)
		if (test_sectors[sector_id].member_sectors[i] == -1)
			break ;
		loop_sector_walls(app, visited, test_sectors[sector_id].member_sectors[i], TRUE);
		i++;
	}
	// Loop through sector walls
	i = 0;
	while (i < test_sectors[sector_id].corner_count)
	{
		// If wall is portal, recurse into portal
		if (test_sectors[sector_id].wall_types[i] != -1)
			loop_sector_walls(app, visited, test_sectors[sector_id].wall_types[i], FALSE);
		// Check if wall is possibly visible, if yes add to possible_visible array
		check_possible_visible(app, sector_id, i, is_member);
		i++;
	}
}

/**
 * Sets possible visible walls to possible_visible array.
 */
void	sector_walls_possible_visible(t_app *app)
{
	int	already_visited[MAX_VISIBLE_SECTORS];

	// Zero possible walls data
	ft_bzero(app->possible_visible, sizeof(t_wall) * MAX_VISIBLE_WALLS);
	app->possible_visible_count = 0;
	already_visited[0] = -1;

	// Loop through walls and determined if they could be visible
	loop_sector_walls(app, (int *)&already_visited, app->player.current_sector, FALSE);

	// Order possible visible walls
	order_possible_visible_walls(app);
}
