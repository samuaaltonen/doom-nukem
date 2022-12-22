/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_collision.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 20:04:35 by saaltone          #+#    #+#             */
/*   Updated: 2022/12/23 01:06:42 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * @brief Checks if player is actually inside a member sector and switches it
 * there if that is the case (can happen when 2 or more member sectors are on
 * top of each other and player is moving from one member sector to another).
 * 
 * @param app 
 */
void	check_player_sector(t_app *app)
{
	int	i;

	if (app->sectors[app->player.current_sector].parent_sector != -1)
		return ;
	i = -1;
	while (++i < MAX_MEMBER_SECTORS
		&& app->sectors[app->player.current_sector].member_sectors[i] >= 0)
	{
		if (inside_sector(app,
				app->sectors[app->player.current_sector].member_sectors[i],
				app->player.pos))
		{
			portal_enter(app,
				app->sectors[app->player.current_sector].member_sectors[i]);
			return ;
		}
	}
}

/**
 * @brief Starts recursive collision check, which gathers all collisions into
 * players collision array.
 * 
 * @param app 
 */
void	collisions_check(t_app *app)
{
	int	visited[MAX_VISIBLE_SECTORS + 1];

	app->player.total_collisions = 0;
	visited[0] = -1;
	collision_sector(app, app->player.current_sector, (int *)&visited);
}

/**
 * @brief Compares players movement point according to all collisions. Tries to
 * find possible position that satisfies all collisions. If no possible position
 * is found after MAX_COLLISION_POSITION_TRIES tries, doesn't move player.
 * 
 * @param app 
 * @return t_vector2 
 */
t_vector2	collisions_apply(t_app *app)
{
	int			tries;
	int			i;

	if (!app->player.total_collisions)
		return (app->player.move_pos);
	tries = -1;
	while (++tries < MAX_COLLISION_POSITION_TRIES)
	{
		i = -1;
		while (++i < app->player.total_collisions)
		{
			if (!collision_possible(app->player.pos, app->player.move_pos,
					app->player.collisions[i], FALSE))
				continue ;
			app->player.move_pos = get_possible_movement_point(
					app->player.collisions[i], app->player.move_pos,
					ft_line_side(app->player.collisions[i], app->player.pos));
			break ;
		}
		if (i == app->player.total_collisions)
			break ;
	}
	if (tries < MAX_COLLISION_POSITION_TRIES)
		return (app->player.move_pos);
	return (app->player.pos);
}
