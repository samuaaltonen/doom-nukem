/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 22:00:01 by htahvana          #+#    #+#             */
/*   Updated: 2023/01/16 22:02:24 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

void	turn_enemy(t_app *app, t_enemy_state *state)
{
	app->objects[state->id].rot = ft_vector_angle_left(
			(t_vector2){0.f, 1.f},
			ft_vector2_sub(app->objects[state->id].position, app->player.pos));
	state->dir = ft_vector2_normalize(
			ft_vector2_sub(app->player.pos, app->objects[state->id].position));
}

void	enemy_attack(t_app *app, t_enemy_state *state, int define)
{
	if (define == 0)
		fire(app, (t_vector3){state->dir.x, state->dir.y,
			(app->player.elevation - app->objects[state->id].elevation)
			/ ft_vector_length(ft_vector2_sub(app->player.pos,
					app->objects[state->id].position))},
			(t_vector3){app->objects[state->id].position.x,
			app->objects[state->id].position.y,
			app->objects[state->id].elevation + 0.5f},
			(t_point){11, app->objects[state->id].sector});
	if (define == 1)
		melee(app, (t_vector3){state->dir.x, state->dir.y,
			(app->player.elevation - app->objects[state->id].elevation)
			/ ft_vector_length(ft_vector2_sub(app->player.pos,
					app->objects[state->id].position))},
			(t_vector3){app->objects[state->id].position.x,
			app->objects[state->id].position.y,
			app->objects[state->id].elevation + 0.5f},
			(t_point){11, app->objects[state->id].sector});
	state->next = IDLE;
}

void	update_enemy_states(t_app *app)
{
	t_enemy_state	*state;

	state = &(app->enemies[0]);
	state--;
	while (++state != NULL && state->id != -1)
	{
		if (state->dead)
			continue ;
		else if (app->objects[state->id].type == MONSTER1)
			enemy_states(app, state, 0);
		else if (app->objects[state->id].type == MONSTER2)
			enemy_states(app, state, 1);
	/* 	if (app->objects[state->id] == MONSTER3)
			enemy_3_states(app, state); */
	}
}
