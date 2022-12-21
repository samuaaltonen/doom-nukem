/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_collision.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 20:04:35 by saaltone          #+#    #+#             */
/*   Updated: 2022/12/21 20:09:31 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

t_bool	collision_check(t_app *app)
{
	int	visited[MAX_VISIBLE_SECTORS + 1];

	visited[0] = -1;
	return (collision_sector(app, app->player.current_sector,
			(int *)&visited));
}
