/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_states.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 16:30:44 by htahvana          #+#    #+#             */
/*   Updated: 2022/12/28 16:57:13 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

static void check_enemy(t_app *app, t_enemy_state *state, int define)
{
	double	dist;

	dist = ft_vector_length(ft_vector2_sub(app->player.pos, app->objects[state->id].position));
	if(dist < 3.f)
		state->agressive = TRUE;
	if(dist < 10.f && state->agressive)
	{
		app->objects[state->id].rot = ft_vector_angle_right((t_vector2){0.f,1.f},ft_vector2_sub(app->objects[state->id].position, app->player.pos));
		state->dir = ft_vector2_normalize(ft_vector2_sub(app->player.pos, app->objects[state->id].position));
		if(dist < app->enemy_def[define].range)
			state->next = ATTACK;
		else
			state->next = WALK;
	}
	else
		state->agressive = FALSE;
}

static void enemy_states(t_app *app, t_enemy_state *state, int define)
{
		app->object_states[state->id] += (float)app->conf->delta_time * app->enemy_def[define].states[state->state][2];

		if(state->state == DEATH && app->object_states[state->id] > app->enemy_def[define].states[state->state][1] - 1)
			state->dead = TRUE;
		else if(app->object_states[state->id] > app->enemy_def[define].states[state->state][1]
				|| (state->state == WALK && app->object_states[state->id] < 0 && app->object_states[state->id] > -app->enemy_def[define].states[WALK][0]))
		{
			check_enemy(app, state, define);
			if(state->state == WALK && state->next == WALK)
				app->object_states[state->id] = (app->object_states[state->id] - 1) * -1;
			else
				app->object_states[state->id] = app->enemy_def[define].states[state->next][0];
			state->state = state->next;
			state->next = IDLE;
		}
		if(!state->dead && state->state == WALK)
		{
			app->objects[state->id].position = ft_vector2_add(app->objects[state->id].position, ft_vec2_mult(state->dir, app->enemy_def[define].speed * app->conf->delta_time));
		}
}

void	update_enemy_states(t_app *app)
{
	t_enemy_state *state;

	state = &(app->enemies[0]);
	state--;

	while (++state != NULL && state->id != 0)
	{
		if (state->dead)
			continue;
		else if (app->objects[state->id].type == MONSTER1)
			enemy_states(app, state, 0);
		else if (app->objects[state->id].type == MONSTER2)
			enemy_states(app, state, 1);
	/* 	if (app->objects[state->id] == MONSTER3)
			enemy_3_states(app, state); */
	}

}