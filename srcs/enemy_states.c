/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_states.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 16:30:44 by htahvana          #+#    #+#             */
/*   Updated: 2023/02/17 19:34:59 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * @brief Specific handling of instant attack,
 * 	instead of at the end of an animation
 * 
 * @param app 
 * @param state 
 * @param define 
 */
static void	enemy_attack_check(t_app *app, t_enemy_state *state, int define)
{
	if (state->agressive && state->state == WALK
		&& in_range(app->player.pos, app->objects[state->id].position,
			app->enemy_def[define].range)
		&& in_range_height(app->player.elevation,
			app->objects[state->id].elevation,
			app->enemy_def[define].range))
	{
		turn_enemy(app, state);
		state->state = ATTACK;
		app->object_states[state->id]
			= app->enemy_def[define].states[state->state][0];
		state->next = ATTACK;
	}
}

/**
 * @brief Checks the attack / aggro ranges for enemies
 * 
 * @param app 
 * @param state 
 * @param define 
 */
static void	check_enemy(t_app *app, t_enemy_state *state, int define)
{
	if (!state->agressive && in_range(app->player.pos,
			app->objects[state->id].position, 3.f)
		&& in_range_height(app->player.elevation,
			app->objects[state->id].elevation, 3.f))
		state->agressive = TRUE;
	else if (state->agressive && (in_range(app->player.pos,
				app->objects[state->id].position, 10.f)
			&& in_range_height(app->player.elevation,
				app->objects[state->id].elevation, 7.f)))
	{
		turn_enemy(app, state);
		if (in_range(app->player.pos, app->objects[state->id].position,
				app->enemy_def[define].range) && in_range_height(
				app->player.elevation, app->objects[state->id].elevation,
				app->enemy_def[define].range))
			state->next = ATTACK;
		else
			state->next = WALK;
	}
	else
	{
		state->agressive = FALSE;
		state->next = IDLE;
	}
}

/**
 * @brief Updates the enemy states based on defines
 * 
 * @param app 
 * @param state 
 * @param define 
 */
static void	enemy_state_update(t_app *app, t_enemy_state *state, int define)
{
	check_enemy(app, state, define);
	if (state->state == WALK && state->next == WALK && define != 2)
		app->object_states[state->id]
			= (app->object_states[state->id] - 1) * -1;
	else
		app->object_states[state->id]
			= app->enemy_def[define].states[state->next][0];
	state->state = state->next;
	if (state->next != ATTACK)
		state->next = IDLE;
}

/**
 * @brief Moves the enemies
 * 
 * @param app 
 * @param state 
 * @param define 
 */
static void	enemy_walk_update(t_app *app, t_enemy_state *state, int define)
{
	t_move	new;

	avoid_walls(app, state);
	new = (t_move){ft_vector2_add(app->objects[state->id].position,
			ft_vec2_mult(state->dir, app->enemy_def[define].speed
				* app->conf->delta_time)),
		app->sectors[app->objects[state->id].sector].floor_height};
	if (enemy_move_check(app, new,
			app->objects[state->id].sector, state) != -1)
	{
		app->objects[state->id].position = new.pos;
		state->target_elevation = sector_floor_height(app,
				app->objects[state->id].sector, new.pos);
	}
}

/**
 * @brief Enemy state machine, current animation timers are held as floats
 * 	in object_states[id], enemy states stores current state, and the next state.
 * 	Defines get current animation start and end frames from enemy define arrays,
 * 	as well as the speed of the specific animation loop
 * 	Special handling of pingpong animation for the walk cycles.
 * 	Special handling of instant attack when in range for 1 enemy type
 * 
 * @param app 
 * @param state state holds relevant enemy data
 * @param define is the enemy definition id
 */
void	enemy_states(t_app *app, t_enemy_state *state, int define)
{
	app->object_states[state->id] += (float)app->conf->delta_time
		* app->enemy_def[define].states[state->state][2];
	if (state->state == WALK && define == 1)
		enemy_attack_check(app, state, define);
	if (state->state == DEATH && app->object_states[state->id]
		> app->enemy_def[define].states[state->state][1] - 1)
	{
		state->dead = TRUE;
		enemy_interaction_check(app, state);
	}
	else if (state->state == ATTACK && state->next == ATTACK
		&& app->enemy_def[define].attack_speed < app->object_states[state->id])
		enemy_attack(app, state, define);
	else if (app->object_states[state->id]
		> app->enemy_def[define].states[state->state][1]
			|| (state->state == WALK && app->object_states[state->id] < 0
			&& app->object_states[state->id]
			> -app->enemy_def[define].states[WALK][0]))
		enemy_state_update(app, state, define);
	if (state->state == WALK)
		enemy_walk_update(app, state, define);
}
