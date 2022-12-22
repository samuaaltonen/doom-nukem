/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_collision.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 20:04:35 by saaltone          #+#    #+#             */
/*   Updated: 2022/12/22 16:56:34 by saaltone         ###   ########.fr       */
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
	return (collision_sector(app, app->player.current_sector,
			(int *)&visited));
}

/**
 * @brief Modifies players movement point according to all collisions. Tries to
 * find possible position that satisfies all collisions. If no possible position
 * is found after MAX_COLLISION_POSITION_TRIES tries, doesn't move player.
 * 
 * @param app 
 */
void	collisions_apply(t_app *app)
{
	t_vector2	pos;
	int			tries;

	tries = -1;
	while (++tries < MAX_COLLISION_POSITION_TRIES)
	{

	}
	app->player.pos = app->player.move_pos;

}
