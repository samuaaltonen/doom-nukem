/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector_wallstack_order.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 23:00:02 by saaltone          #+#    #+#             */
/*   Updated: 2022/12/08 15:01:39 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * @brief Compares walls relative to player position.
 * 
 * Ordering is done by extending other wall (a) to be very long and then
 * checking for intersection points with the other wall (b). If there is no
 * intersection and wall (b) both corners are at the same side as player
 * position relative to extended wall then drawing priority is with wall (b).
 * 
 * If wall (b) both corners are at different side as player position
 * relative to extended (a) wall, then priority is with wall (a).
 * 
 * If there is intersection, extend the other one. (if both cases has intersect,
 * determines walls to already be in order).
 * 
 * @param app 
 * @param a 
 * @param b 
 * @return t_bool 
 */
static t_bool	compare_walls(t_app *app, t_line a, t_line b)
{
	t_line	extend;
	t_bool	extend_a;
	int		side;

	extend = ft_line_resize(a, MAX_LINE_LENGTH, EXTEND_BOTH);
	extend_a = TRUE;
	if (ft_line_intersection_through(extend, b))
	{
		extend = ft_line_resize(b, MAX_LINE_LENGTH, EXTEND_BOTH);
		extend_a = FALSE;
		if (ft_line_intersection_through(extend, a))
			return (TRUE);
	}
	side = ft_line_side(extend, app->player.pos);
	if (extend_a
		&& (side == ft_line_side(extend, b.a) || ft_line_point(extend, b.a))
		&& (side == ft_line_side(extend, b.b) || ft_line_point(extend, b.b)))
		return (FALSE);
	if (!extend_a
		&& ((side != ft_line_side(extend, a.a) && !ft_line_point(extend, a.a))
			|| (side != ft_line_side(extend, a.b)
				&& !ft_line_point(extend, a.b))))
		return (FALSE);
	return (TRUE);
}

/**
 * @brief Checks order of 2 given walls.
 * 
 * If both wall segments belong to same line (i.e. 2 member sectors next to
 * each other = full intersection), prioritizes a wall that player is looking
 * from inside. In any other case, checks the order relative to player.
 * 
 * @param app 
 * @param wall_a 
 * @param wall_b 
 * @return t_bool 
 */
static t_bool	walls_in_order(t_app *app, t_wall *wall_a, t_wall *wall_b)
{
	t_line	a;
	t_line	b;

	if (wall_a->is_member && !wall_b->is_member)
		return (TRUE);
	if (wall_b->is_member && !wall_a->is_member)
		return (FALSE);
	a = get_wall_line(app, wall_a->sector_id, wall_a->wall_id);
	b = get_wall_line(app, wall_b->sector_id, wall_b->wall_id);
	if (ft_line_intersection_full(a, b)
		&& wall_a->is_inside != wall_b->is_inside)
	{
		if (wall_a->is_inside)
			return (TRUE);
		else
			return (FALSE);
	}
	return (compare_walls(app, a, b));
}

/**
 * @brief Returns TRUE if there is overlap in translated window x coordinates.
 * 
 * @param wall_a 
 * @param wall_b 
 * @return t_bool 
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
 * @brief Returns foremost wall from all possibly visible walls
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
 * 
 * @param app 
 * @param walls 
 * @param wall_count 
 * @return int 
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
	return (first_nonselected);
}

/**
 * @brief Orders possible visible walls.
 * 
 * @param app 
 * @param walls 
 * @param wall_count 
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
