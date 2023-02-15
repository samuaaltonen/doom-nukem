/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_enemies.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 19:38:34 by saaltone          #+#    #+#             */
/*   Updated: 2023/02/15 17:28:32 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * @brief Defines enemy type 0 values.
 * state 0 Idle
 * state 1 Attack
 * state 2 Death
 * state 3 Walk
 * 0 frame start, 1 frame end, 2 frame speed
 * 
 * @param app 
 */
void	define_enemy_0(t_app *app)
{
	app->enemy_def[0].state_count = 4;
	app->enemy_def[0].range = 3.f;
	app->enemy_def[0].speed = 2.f;
	app->enemy_def[0].health = 100.f;
	app->enemy_def[0].attack_speed = 2.f;
	app->enemy_def[0].states[0][0] = 0.f;
	app->enemy_def[0].states[0][1] = 1.f;
	app->enemy_def[0].states[0][2] = 1.f;
	app->enemy_def[0].states[1][0] = 1.f;
	app->enemy_def[0].states[1][1] = 3.f;
	app->enemy_def[0].states[1][2] = 2.5f;
	app->enemy_def[0].states[2][0] = 3.f;
	app->enemy_def[0].states[2][1] = 5.f;
	app->enemy_def[0].states[2][2] = 2.f;
	app->enemy_def[0].states[3][0] = 5.f;
	app->enemy_def[0].states[3][1] = 8.f;
	app->enemy_def[0].states[3][2] = 5.f;
}

/**
 * @brief Defines enemy type 1 values.
 * state 0 Idle
 * state 1 Attack
 * state 2 Death
 * state 3 Walk
 * 0 frame start, 1 frame end, 2 frame speed
 * 
 * @param app 
 */
void	define_enemy_1(t_app *app)
{
	app->enemy_def[1].state_count = 4;
	app->enemy_def[1].range = 1.f;
	app->enemy_def[1].speed = 5.f;
	app->enemy_def[1].health = 75.f;
	app->enemy_def[1].attack_speed = 4.f;
	app->enemy_def[1].states[0][0] = 0.f;
	app->enemy_def[1].states[0][1] = 1.f;
	app->enemy_def[1].states[0][2] = 1.f;
	app->enemy_def[1].states[1][0] = 1.f;
	app->enemy_def[1].states[1][1] = 6.f;
	app->enemy_def[1].states[1][2] = 5.f;
	app->enemy_def[1].states[2][0] = 6.f;
	app->enemy_def[1].states[2][1] = 8.f;
	app->enemy_def[1].states[2][2] = 2.f;
	app->enemy_def[1].states[3][0] = 9.f;
	app->enemy_def[1].states[3][1] = 12.f;
	app->enemy_def[1].states[3][2] = 5.f;
}

/**
 * @brief Defines enemy type 2 values.
 * state 0 Idle
 * state 1 Attack
 * state 2 Death
 * state 3 Walk
 * 0 frame start, 1 frame end, 2 frame speed
 * 
 * @param app 
 */
void	define_enemy_2(t_app *app)
{
	app->enemy_def[2].state_count = 4;
	app->enemy_def[2].range = 5.f;
	app->enemy_def[2].speed = 3.f;
	app->enemy_def[2].health = 100.f;
	app->enemy_def[2].attack_speed = 1.5f;
	app->enemy_def[2].states[0][0] = 0.f;
	app->enemy_def[2].states[0][1] = 1.f;
	app->enemy_def[2].states[0][2] = 1.f;
	app->enemy_def[2].states[1][0] = 1.f;
	app->enemy_def[2].states[1][1] = 2.f;
	app->enemy_def[2].states[1][2] = 1.5f;
	app->enemy_def[2].states[2][0] = 2.f;
	app->enemy_def[2].states[2][1] = 4.f;
	app->enemy_def[2].states[2][2] = 2.f;
	app->enemy_def[2].states[3][0] = 4.f;
	app->enemy_def[2].states[3][1] = 5.f;
	app->enemy_def[2].states[3][2] = 1.f;
}

/**
 * @brief Defines enemy values.
 * 
 * @param app 
 */
void	define_enemies(t_app *app)
{
	define_enemy_0(app);
	define_enemy_1(app);
	define_enemy_2(app);
}

/**
 * @brief Initializes enemy data.
 * 
 * @param app 
 */
void	init_enemies(t_app *app)
{
	int				i;
	t_enemy_state	*enemy;
	int				enemy_count;

	ft_bzero(&app->enemies, sizeof(app->enemies));
	enemy = &(app->enemies[0]);
	i = -1;
	enemy_count = 0;
	while (++i < MAX_OBJECTS)
	{
		if (app->objects[i].type >= MONSTER1
			&& app->objects[i].type < MONSTER1 + MAX_ENEMY_TYPES)
		{
			enemy->id = i;
			enemy->hp = app->enemy_def[app->objects[i].type - MONSTER1].health;
			enemy->pos = app->objects[i].position;
			enemy->dead = FALSE;
			enemy->agressive = FALSE;
			enemy->target_elevation = app->objects[i].elevation;
			enemy++;
			enemy_count++;
		}
		else
			enemy->id = -1;
	}
}
