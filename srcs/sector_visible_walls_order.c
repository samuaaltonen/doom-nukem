/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector_visible_walls_order.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 23:00:02 by saaltone          #+#    #+#             */
/*   Updated: 2022/10/15 19:54:22 by saaltone         ###   ########.fr       */
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
	int			side;
	int			extended_wall;

	if (!app->possible_visible[wall_a].is_member)
		return (FALSE);
	if (!app->possible_visible[wall_b].is_member)
		return (TRUE);
	a = get_wall_vertex(app, app->possible_visible[wall_a].sector_id, app->possible_visible[wall_a].wall_id);
	b = get_wall_vertex(app, app->possible_visible[wall_b].sector_id, app->possible_visible[wall_b].wall_id);

	// Extend wall_a to infinity / very long
	extended = ft_vertex_resize(a, MAX_VERTEX_LENGTH, EXTEND_BOTH);
	extended_wall = wall_a;

	// Check intersection
	if (ft_vertex_intersection_through(extended, b))
	{
		extended = ft_vertex_resize(b, MAX_VERTEX_LENGTH, EXTEND_BOTH);
		extended_wall = wall_b;
		// If interesction again, no change in order
		if (ft_vertex_intersection_through(extended, a))
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
 * Returns TRUE if there is overlap in translated window x coordinates.
*/
t_bool	walls_overlap(t_app *app, int wall_a, int wall_b)
{
	if (app->possible_visible[wall_a].start_x < app->possible_visible[wall_b].end_x
		&& app->possible_visible[wall_a].end_x > app->possible_visible[wall_b].start_x)
		return (TRUE);
	return (FALSE);
}

/**
 * Returns foremost wall from all possibly visible walls
 * 
 * Loops through all walls
 * - if a wall has already been picked, skip
 * - loop current wall against other walls to see if it is a good pick
 * - skip comparing if:
 *   - wall is the same as current one (i == j)
 *   - wall that we are comparing to has been selected before
 *   - if there is no actual overlap in translated window coordinates (x)
 * - compares walls (i, j), if they are not in order, break, (i) is not foremost
 * - if order was fine with all walls that (i) was compared with, return (i)
 * - if there was no clear foremost wall returns first non picked one
*/
int	get_foremost_wall(t_app *app)
{
	int		first_nonselected;
	int		i;
	int		j;

	i = -1;
	first_nonselected = -1;
	while (++i < app->possible_visible_count)
	{
		if (app->possible_visible[i].already_selected)
			continue ;
		if (first_nonselected == -1)
			first_nonselected = i;
		j = -1;
		while (++j < app->possible_visible_count)
		{
			if (i == j || app->possible_visible[j].already_selected
				|| !walls_overlap(app, i, j))
				continue ;
			if (!walls_in_order(app, i, j))
				break ;
		}
		if (j == app->possible_visible_count)
			return (i);
	}
	return (first_nonselected);
}

/**
 * Orders possible visible walls.
*/
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
	/* ft_printf("Wall order:\n"); */
	while (i < app->possible_visible_count)
	{
		/* ft_printf("%d:%d\n", temp[i].sector_id, temp[i].wall_id); */
		app->possible_visible[i] = temp[i];
		i++;
	}
}
