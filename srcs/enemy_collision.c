/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_collision.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 19:29:42 by htahvana          #+#    #+#             */
/*   Updated: 2023/02/17 19:31:13 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

static void	init_colliders(t_app *app, t_enemy_state *enemy,
		t_vector2 *colliders, int *collider)
{
	*collider = -1;
	colliders[0] = (t_vector2){app->objects[enemy->id].position.x
		- ENEMY_COLLISION + 0.01f, app->objects[enemy->id].position.y
		- ENEMY_COLLISION};
	colliders[1] = (t_vector2){app->objects[enemy->id].position.x
		+ ENEMY_COLLISION, app->objects[enemy->id].position.y
		- ENEMY_COLLISION};
	colliders[2] = (t_vector2){app->objects[enemy->id].position.x
		- ENEMY_COLLISION + 0.01f, app->objects[enemy->id].position.y
		+ ENEMY_COLLISION};
	colliders[3] = (t_vector2){app->objects[enemy->id].position.x
		+ ENEMY_COLLISION, app->objects[enemy->id].position.y
		+ ENEMY_COLLISION};
}

/**
 * @brief Makes 4 colliders around the enemy, collects which of the colliders
 * 	hit walls, adds them and creates a direction away from the collided points
 * 
 * @param app 
 * @param enemy 
 */
void	avoid_walls(t_app *app, t_enemy_state *enemy)
{
	t_vector2	colliders[4];
	int			collider;
	t_bool		hit[5];
	t_vector2	new;

	init_colliders(app, enemy, (t_vector2 *)colliders, &collider);
	ft_bzero(&hit, sizeof(hit));
	collect_hits(app, enemy, (t_bool *)&hit, (t_vector2 *)colliders);
	if (hit[4])
	{
		new = app->objects[enemy->id].position;
		while (++collider < 4)
		{
			if (!hit[collider])
				continue ;
			new = ft_vector2_add(new, ft_vector2_sub(colliders[collider],
						app->objects[enemy->id].position));
		}
		enemy->dir = ft_vector2_normalize(ft_vector2_sub(
					app->objects[enemy->id].position, new));
		app->objects[enemy->id].rot = ft_vector_angle_left(
				(t_vector2){0.f, -1.f}, enemy->dir);
	}
}
