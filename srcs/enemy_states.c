/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_states.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 16:30:44 by htahvana          #+#    #+#             */
/*   Updated: 2022/12/15 17:28:15 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

static void enemy_states(t_app *app, t_enemy_state *state, int define)
{
		app->object_states[state->id] += (float)app->conf->delta_time * app->enemy_def[define].states[state->state][2];
		if(app->object_states[state->id] > (app->enemy_def[define].states[state->state][0] + app->enemy_def[define].states[state->state][1]))
		{
			state->state = state->next;
			app->object_states[state->id] = app->enemy_def[define].states[state->state][0];
			state->next = IDLE;
		}
}

void	update_enemy_states(t_app *app)
{
	t_enemy_state *state;
	state = &(app->enemies[0]);
	while (state->id != 0)
	{
		if (state->dead)
			continue;
		if (app->objects[state->id].type == MONSTER1)
			enemy_states(app, state, 0);
		else if (app->objects[state->id].type == MONSTER2)
			enemy_states(app, state, 1);
	/* 	if (app->objects[state->id] == MONSTER3)
			enemy_3_states(app, state); */
		state++;
	}

}