/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector_wallstack.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 14:38:55 by saaltone          #+#    #+#             */
/*   Updated: 2022/12/28 04:15:48 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

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
 * @brief Orders wallstack.
 * 
 * @param app 
 */
static void	sector_wallstack_order(t_app *app)
{
	int	i;

	i = 0;
	while (app->wallstack.wall_count[i] != -1)
	{
		if (app->wallstack.wall_count[i] > 0)
		{
			sector_walls_prepare(app, (t_wall *)&app->wallstack.walls[i],
				app->wallstack.wall_count[i]);
			sector_walls_order(app, (t_wall *)&app->wallstack.walls[i],
				app->wallstack.wall_count[i]);
		}
		i++;
	}
}

/**
 * @brief Sets possible visible walls to possible_visible array. Starts with
 * players current sector (or its parent sector if member). Whenever encouters
 * a portal in loop_sector_walls, adds it to wallstack.interesting array to
 * be visited in the next iteration.
 * 
 * After gathering all interesting (i.e. possibly visible) walls in wallstack
 * array, orders them sector by sector.
 * 
 * @param app 
 */
void	sector_wallstack_build(t_app *app)
{
	int	i;

	app->wallstack.visited[0] = -1;
	if (app->sectors[app->player.sector].parent_sector == -1)
		app->wallstack.interesting[0] = app->player.sector;
	else
		app->wallstack.interesting[0]
			= app->sectors[app->player.sector].parent_sector;
	app->wallstack.interesting_count = 1;
	i = 0;
	while (i < app->wallstack.interesting_count && i < MAX_VISIBLE_SECTORS - 1)
	{
		app->wallstack.wall_count[i] = 0;
		app->wallstack.wall_count[i + 1] = -1;
		if (!has_been_visited((int *)&app->wallstack.visited,
				app->wallstack.interesting[i]))
			sector_visible_walls(app, &app->wallstack, i,
				app->wallstack.interesting[i]);
		i++;
	}
	sector_wallstack_order(app);
}
