/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_states.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 16:30:44 by htahvana          #+#    #+#             */
/*   Updated: 2023/01/04 17:37:51 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

static void	avoid_walls(t_app *app, t_enemy_state *enemy)
{
	t_vector2	colliders[4];
	int	i;
	t_line	wall_line;
	int collider;
	t_bool hit[4];
	t_bool	collision;

	hit[0] = FALSE;
	hit[1] = FALSE;
	hit[2] = FALSE;
	hit[3] = FALSE;
	collision = FALSE;
	colliders[0] = (t_vector2){app->objects[enemy->id].position.x - 1.f, app->objects[enemy->id].position.y - 1.f};
	colliders[1] = (t_vector2){app->objects[enemy->id].position.x + 1.f, app->objects[enemy->id].position.y - 1.f};
	colliders[2] = (t_vector2){app->objects[enemy->id].position.x - 1.f, app->objects[enemy->id].position.y + 1.f};
	colliders[3] = (t_vector2){app->objects[enemy->id].position.x + 1.f, app->objects[enemy->id].position.y + 1.f};
	collider = -1;
	while(++collider < 4)
	{
		i = -1;
		while (++i < app->sectors[app->objects[enemy->id].sector].corner_count)
		{
			wall_line = get_wall_line(app, app->objects[enemy->id].sector, i);
			if (ft_line_side(wall_line, colliders[collider]))
			{
				if(app->sectors[app->objects[enemy->id].sector].wall_types[i] == -1)
				{
					hit[collider] = TRUE;
					collision = TRUE;
					break;
				}
			}
		}
	}
	collider = -1;
	if(collision)
	{
		t_vector2 new = app->objects[enemy->id].position;
		i = 0;
		while(++collider < 4)
		{
			if(hit[collider])
				new = ft_vector2_add(new, colliders[collider]);
		}
		app->objects[enemy->id].rot = ft_vector_angle_right((t_vector2){0.f,1.f},ft_vector2_sub(new,app->objects[enemy->id].position));
		enemy->dir = ft_vector2_normalize(ft_vector2_sub(app->objects[enemy->id].position, new));
	}
}

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
		if(dist + ft_abs(app->player.elevation - app->objects[state->id].elevation) < app->enemy_def[define].range)
			state->next = ATTACK;
		else
			state->next = WALK;
	}
	else
		state->agressive = FALSE;
}

static void enemy_states(t_app *app, t_enemy_state *state, int define)
{

	t_move new;
	t_vector2 attack_dir;

		app->object_states[state->id] += (float)app->conf->delta_time * app->enemy_def[define].states[state->state][2];

		if(state->state == DEATH && app->object_states[state->id] > app->enemy_def[define].states[state->state][1] - 1)
			state->dead = TRUE;
		else if(state->state == ATTACK && state->next == ATTACK && app->enemy_def[define].attack_speed < app->object_states[state->id])
		{
			attack_dir = ft_vector2_normalize(ft_vector2_sub(app->player.pos,app->objects[state->id].position));
			fire(app,(t_vector3){attack_dir.x,attack_dir.y,(app->player.elevation - app->objects[state->id].elevation) / ft_vector_length(ft_vector2_sub(app->player.pos,app->objects[state->id].position))},
					(t_vector3){app->objects[state->id].position.x, app->objects[state->id].position.y,
					app->objects[state->id].elevation + 0.5f},(t_point){12,app->objects[state->id].sector});
			state->next = IDLE;
		}
		else if(app->object_states[state->id] > app->enemy_def[define].states[state->state][1]
				|| (state->state == WALK && app->object_states[state->id] < 0 && app->object_states[state->id] > -app->enemy_def[define].states[WALK][0]))
		{
			check_enemy(app, state, define);
			if(state->state == WALK && state->next == WALK)
				app->object_states[state->id] = (app->object_states[state->id] - 1) * -1;
			else
				app->object_states[state->id] = app->enemy_def[define].states[state->next][0];
			state->state = state->next;
			if(state->next != ATTACK)
				state->next = IDLE;
		}
		if(!state->dead && state->state == WALK)
		{
			avoid_walls(app, state);
			new = (t_move){ft_vector2_add(app->objects[state->id].position, ft_vec2_mult(state->dir, app->enemy_def[define].speed * app->conf->delta_time)), app->sectors[app->objects[state->id].sector].floor_height};
			if (enemy_move_check(app, new, app->objects[state->id].sector,state) != -1)
			{
				app->objects[state->id].position = new.pos;
				app->objects[state->id].elevation = sector_floor_height(app, app->objects[state->id].sector, new.pos);
			}
		}
}

void	update_enemy_states(t_app *app)
{
	t_enemy_state *state;

	state = &(app->enemies[0]);
	state--;
	while (++state != NULL && state->id != -1)
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