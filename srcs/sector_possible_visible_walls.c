/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector_possible_visible_walls.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 13:12:02 by saaltone          #+#    #+#             */
/*   Updated: 2022/10/13 22:38:01 by saaltone         ###   ########.fr       */
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
	int			side;
	int			extended_wall;

	if (!app->possible_visible[wall_a].is_member)
		return (FALSE);
	if (!app->possible_visible[wall_b].is_member)
		return (TRUE);
	a = get_sector_vertex_by_corner(app, app->possible_visible[wall_a].sector_id, app->possible_visible[wall_a].wall_id);
	b = get_sector_vertex_by_corner(app, app->possible_visible[wall_b].sector_id, app->possible_visible[wall_b].wall_id);

	// Extend wall_a to infinity / very long
	extended = ft_vertex_resize(a, MAX_VERTEX_LENGTH, EXTEND_BOTH);
	extended_wall = wall_a;

	// Check intersection
	if (ft_vertex_intersection_through(extended, b, &intersection))
	{
		extended = ft_vertex_resize(b, MAX_VERTEX_LENGTH, EXTEND_BOTH);
		extended_wall = wall_b;
		// If interesction again, no change in order
		if (ft_vertex_intersection_through(extended, a, &intersection))
			return (TRUE);
	}

	/** 
	 * Check side with player pos relative to extended wall.
	 */
	// Get player side (1 if left side of vertex)
	side = ft_vertex_side(extended, app->player.pos);

	/**
	 * If wall a was extended and wall b is at the same side as player, then 
	 * wall b has priority (return false so switch b before a).
	 */
	if (extended_wall == wall_a
		&& side == ft_vertex_side(extended, b.a)
		&& side == ft_vertex_side(extended, b.b))
		return (FALSE);
	/**
	 * Similarly if b was extended, and wall a not at the same side as player,
	 * then b has priority.
	 */
	if (extended_wall == wall_b
		&& (side != ft_vertex_side(extended, a.a)
			|| side != ft_vertex_side(extended, a.b)))
		return (FALSE);
	/**
	 * All other cases, wall a has priority so it is already in order.
	 */
	return (TRUE);
}

/**
 * Orders walls depending on visibility. Only orders walls that came from member
 * sectors. Other walls should already be in order (if all sectors convex).
 */
/* static void	order_possible_visible_walls(t_app *app)
{
	t_wall	temp;
	t_bool	in_order;
	int		i;
	int		j;

	i = -1;
	while (++i < app->possible_visible_count)
	{
		app->possible_visible[i].visibility_score = 0;
		if (!app->possible_visible[i].is_member)
			continue ;
		j = -1;
		while (++j < app->possible_visible_count)
		{
			if (i == j)
				continue ;
			app->possible_visible[i].visibility_score += walls_in_order(app, i, j);
		}
	}
	in_order = FALSE;
	while (!in_order)
	{
		in_order = TRUE;
		i = -1;
		while (++i < app->possible_visible_count - 1)
		{
			if (app->possible_visible[i].visibility_score < app->possible_visible[i + 1].visibility_score)
			{
				temp = app->possible_visible[i];
				app->possible_visible[i] = app->possible_visible[i + 1];
				app->possible_visible[i + 1] = temp;
				in_order = FALSE;
			}
		}
	}
} */

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

	wall_vertex = get_sector_vertex_by_corner(app, sector_id, wall_id);
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

t_bool	walls_overlap(t_app *app, int wall_a, int wall_b)
{
	if (app->possible_visible[wall_a].start_x < app->possible_visible[wall_b].end_x
		&& app->possible_visible[wall_a].end_x > app->possible_visible[wall_b].start_x)
		return (TRUE);
	/* ft_printf("No overlap with wall %d:%d (x: %d to %d) and %d:%d\n", 
		app->possible_visible[wall_a].sector_id, app->possible_visible[wall_a].wall_id,
		app->possible_visible[wall_a].start_x, app->possible_visible[wall_a].end_x,
		app->possible_visible[wall_b].sector_id, app->possible_visible[wall_b].wall_id,
		app->possible_visible[wall_b].start_x, app->possible_visible[wall_b].end_x
	); */
	return (FALSE);
}

/**
 * Returns foremost wall from possibly visible walls
*/
int	get_foremost_wall(t_app *app)
{
	int		current_score;
	int		most_score;
	int		most_foremost;
	int		i;
	int		j;
	t_bool	is_foremost;

	i = -1;
	most_score = 0;
	most_foremost = -1;
	while (++i < app->possible_visible_count)
	{
		if (app->possible_visible[i].already_selected)
			continue ;
		if (most_foremost == -1)
			most_foremost = i;
		j = -1;
		is_foremost = TRUE;
		current_score = 0;
		while (++j < app->possible_visible_count)
		{
			if (i == j || app->possible_visible[j].already_selected)
				continue ;
			if (!walls_overlap(app, i, j))
				continue ;
			if (!walls_in_order(app, i, j))
			{
				/* ft_printf("Wall %d:%d is behind of wall %d:%d\n",
					app->possible_visible[i].sector_id, app->possible_visible[i].wall_id,
					app->possible_visible[j].sector_id, app->possible_visible[j].wall_id); */
				is_foremost = FALSE;
			}
			else
			{
				current_score++;
				if (current_score > most_score)
				{
					most_score = current_score;
					most_foremost = i;
				}
			}
		}
		if (is_foremost)
			return (i);
	}
	/* if (app->possible_visible[most_foremost].is_member)
		ft_printf("Cannot determine foremost wall.\n"); */
	return (most_foremost);
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

	// Loop through walls and determine if they could be visible
	loop_sector_walls(app, (int *)&already_visited, app->player.current_sector, FALSE);

	// Order possible visible walls
	//order_possible_visible_walls(app);
}

void	sector_walls_order(t_app *app)
{
	t_wall	temp[MAX_VISIBLE_WALLS];
	int		foremost;
	int		i;

	i = 0;
	while (i < app->possible_visible_count)
	{
		foremost = get_foremost_wall(app);
		temp[i] = app->possible_visible[foremost];
		app->possible_visible[foremost].already_selected = 1;
		i++;
	}
	i = 0;
	/* ft_printf("Front front to back:\n"); */
	while (i < app->possible_visible_count)
	{
		/* ft_printf("%d:%d\n", temp[i].sector_id, temp[i].wall_id); */
		app->possible_visible[i] = temp[i];
		i++;
	}
}
