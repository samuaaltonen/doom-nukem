/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_states.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 16:30:44 by htahvana          #+#    #+#             */
/*   Updated: 2022/12/16 15:20:29 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

static void enemy_states(t_app *app, t_enemy_state *state, int define)
{
		app->object_states[state->id] += (float)app->conf->delta_time * app->enemy_def[define].states[state->state][2];
		if(state->state == DEATH && app->object_states[state->id] > app->enemy_def[define].states[state->state][1] - 1)
			state->dead = TRUE;
		else if(app->object_states[state->id] > app->enemy_def[define].states[state->state][1]
				|| (state->state == WALK && app->object_states[state->id] < 0 && app->object_states[state->id] > -app->enemy_def[define].states[WALK][0]))
		{
			if(state->state == WALK && state->next == WALK)
				app->object_states[state->id] = (app->object_states[state->id] - 1) * -1;
			else
				app->object_states[state->id] = app->enemy_def[define].states[state->next][0];
			state->state = state->next;
			state->next = IDLE;
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