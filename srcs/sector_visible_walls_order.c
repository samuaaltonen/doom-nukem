/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector_visible_walls_order.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 23:00:02 by saaltone          #+#    #+#             */
/*   Updated: 2022/11/29 15:19:23 by saaltone         ###   ########.fr       */
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
static t_bool	walls_in_order(t_app *app, t_wall *wall_a, t_wall *wall_b)
{
	t_line	a;
	t_line	b;
	t_line	extended;
	t_bool	extended_a;
	int		side;

	if (wall_a->is_member && !wall_b->is_member)
		return (TRUE);
	if (wall_b->is_member && !wall_a->is_member)
		return (FALSE);
	a = get_wall_line(app, wall_a->sector_id, wall_a->wall_id);
	b = get_wall_line(app, wall_b->sector_id, wall_b->wall_id);

	// Extend wall_a to infinity / very long
	extended = ft_line_resize(a, MAX_LINE_LENGTH, EXTEND_BOTH);
	extended_a = TRUE;

	if (ft_line_intersection_full(a, b) && wall_a->is_inside != wall_b->is_inside) {
		if (wall_a->is_inside)
			return (TRUE);
		else
			return (FALSE);
	}

	// Check intersection
	if (ft_line_intersection_through(extended, b))
	{
		extended = ft_line_resize(b, MAX_LINE_LENGTH, EXTEND_BOTH);
		extended_a = FALSE;

		// If interesction again, no change in order
		if (ft_line_intersection_through(extended, a))
			return (TRUE);
	}

	/** 
	 * Check side with player pos relative to extended wall.
	 */
	// Get player side (1 if left side of line)
	side = ft_line_side(extended, app->player.pos);

	/**
	 * If wall a was extended and wall b is at the same side as player, then 
	 * wall b has priority (return false so switch b before a).
	 */
	if (extended_a
		&& (side == ft_line_side(extended, b.a) || ft_line_point(extended, b.a))
		&& (side == ft_line_side(extended, b.b) || ft_line_point(extended, b.b)))
		return (FALSE);
	/**
	 * Similarly if b was extended, and wall a is not at the same side as player,
	 * then b has priority.
	 */
	if (!extended_a
		&& ((side != ft_line_side(extended, a.a) && !ft_line_point(extended, a.a))
			|| (side != ft_line_side(extended, a.b) && !ft_line_point(extended, a.b))))
		return (FALSE);
	/**
	 * All other cases, wall a has priority so it is already in order.
	 */
	return (TRUE);
}

/**
 * Returns TRUE if there is overlap in translated window x coordinates.
*/
t_bool	walls_overlap(t_wall *wall_a, t_wall *wall_b)
{
	int	overlap_start;
	int	overlap_end;

	overlap_start = wall_a->start_x - wall_b->end_x;
	overlap_end = wall_a->end_x - wall_b->start_x;
	if (overlap_start < -2 && overlap_end > 2)
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
static int	get_foremost_wall(t_app *app, t_wall *walls, int wall_count)
{
	int		first_nonselected;
	int		i;
	int		j;

	i = -1;
	first_nonselected = -1;
	while (++i < wall_count)
	{
		if (walls[i].already_selected)
			continue ;
		if (first_nonselected == -1)
			first_nonselected = i;
		j = -1;
		while (++j < wall_count)
		{
			if (i == j || walls[j].already_selected
				|| !walls_overlap(&walls[i], &walls[j]))
				continue ;
			if (!walls_in_order(app, &walls[i], &walls[j]))
				break ;
		}
		if (j == wall_count)
			return (i);
	}
	/**
	 * TODO: Remove 
	 */
	ft_printf("{red}ERROR: Wall ordering has no good pick, going with %d,%d (%d){white}\n", walls[first_nonselected].sector_id, walls[first_nonselected].wall_id, first_nonselected);
	return (first_nonselected);
}

/**
 * Orders possible visible walls.
*/
void	sector_walls_order(t_app *app, t_wall *walls, int wall_count)
{
	t_wall	temp[MAX_VISIBLE_WALLS];
	int		foremost;
	int		i;

	i = 0;
	while (i < wall_count)
	{
		foremost = get_foremost_wall(app, walls, wall_count);
		temp[i] = walls[foremost];
		walls[foremost].already_selected = 1;
		i++;
	}
	i = 0;
	while (i < wall_count)
	{
		walls[i] = temp[i];
		i++;
	}
}
