/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_collision.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 20:04:35 by saaltone          #+#    #+#             */
/*   Updated: 2022/12/22 17:47:53 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

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
					app->player.collisions[i]))
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
