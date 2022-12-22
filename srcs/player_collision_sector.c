/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_collision_sector.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 20:03:45 by saaltone          #+#    #+#             */
/*   Updated: 2022/12/22 22:25:29 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * @brief Returns TRUE if coordinate is located inside a sector.
 * 
 * @param app 
 * @param sector_id 
 * @param coord 
 * @return t_bool 
 */
static t_bool	inside_sector(t_app *app, int sector_id, t_vector2 coord)
{
	int	i;

	i = 0;
	while (i < app->sectors[sector_id].corner_count)
	{
		if (ft_line_side(get_wall_line(app, sector_id, i), coord))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

/**
 * @brief Returns TRUE if sector has been visited. Also sets sector visited if
 * set_visited is set to TRUE.
 * 
 * @param sector_id 
 * @param visited 
 * @param set_visited 
 * @return t_bool 
 */
static t_bool	has_been_visited(int sector_id, int *visited,
	t_bool set_visited)
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
	if (!set_visited)
		return (FALSE);
	visited[i] = sector_id;
	visited[i + 1] = -1;
	return (FALSE);
}

/**
 * @brief Checks collisions with member sectors.
 * 
 * @param app 
 * @param sector_id 
 */
static void	member_collisions(t_app *app, int sector_id)
{
	t_collision_type	collision_type;
	int					i;
	int					j;
	int					member_id;

	i = -1;
	while (++i < MAX_MEMBER_SECTORS
		&& app->sectors[sector_id].member_sectors[i] >= 0)
	{
		member_id = app->sectors[sector_id].member_sectors[i];
		j = -1;
		while (++j < app->sectors[member_id].corner_count)
		{
			collision_type = collision_wall(app, member_id, j, member_id);
			if (collision_type == COLLISION_PORTAL
				&& inside_sector(app, member_id, app->player.move_pos))
				portal_enter(app, member_id);
		}
	}
}

/**
 * @brief Recurses into portals sector to check collisions.
 * 
 * @param app 
 * @param sector_id 
 * @param portal_id 
 * @param visited 
 * @return t_bool 
 */
t_bool	collision_sector_portal(t_app *app, int sector_id, int portal_id,
	int *visited)
{
	if (has_been_visited(portal_id, visited, FALSE))
	{
		if (app->sectors[sector_id].parent_sector == portal_id
			&& !inside_sector(app, sector_id, app->player.move_pos)
			&& inside_sector(app, portal_id, app->player.move_pos))
			portal_enter(app, portal_id);
		return (TRUE);
	}
	if (inside_sector(app, portal_id, app->player.move_pos)
		&& !inside_sector(app, sector_id, app->player.move_pos))
		portal_enter(app, portal_id);
	if (!collision_sector(app, portal_id, visited))
	{
		portal_enter(app, sector_id);
		return (FALSE);
	}
	return (TRUE);
}

/**
 * @brief Recursive check for collisions with sector walls.
 * 
 * @param app 
 * @param sector_id 
 * @param visited 
 * @return t_bool 
 */
t_bool	collision_sector(t_app *app, int sector_id, int *visited)
{
	t_collision_type	collision_type;
	int					i;
	int					portal_id;

	if (has_been_visited(sector_id, visited, TRUE))
		return (TRUE);
	member_collisions(app, sector_id);
	i = -1;
	while (++i < app->sectors[sector_id].corner_count)
	{
		portal_id = app->sectors[sector_id].wall_types[i];
		collision_type = collision_wall(app, sector_id, i, portal_id);
		if (collision_type == COLLISION_PORTAL)
			collision_sector_portal(app, sector_id, portal_id, visited);
	}
	return (TRUE);
}
