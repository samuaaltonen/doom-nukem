/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_weapons.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <danielmdc94@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 18:27:42 by htahvana          #+#    #+#             */
/*   Updated: 2023/02/15 17:55:29 by dpalacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * @brief Defines bullet values.
 * 
 * @param app 
 */
void	define_bullets(t_app *app)
{
	app->bullet_def[0].speed = 5.f;
	app->bullet_def[0].damage = 20.f;
	app->bullet_def[0].size = (t_vector2){0.5f, 0.5f};
	app->bullet_def[1].speed = 5.f;
	app->bullet_def[1].damage = 25.f;
	app->bullet_def[1].size = (t_vector2){0.5f, 0.5f};
	app->bullet_def[2].speed = 8.f;
	app->bullet_def[2].damage = 25.f;
	app->bullet_def[2].size = (t_vector2){0.5f, 0.5f};
	app->bullet_def[3].speed = 8.f;
	app->bullet_def[3].damage = 25.f;
	app->bullet_def[3].size = (t_vector2){0.5f, 0.5f};
	app->bullet_def[4].speed = 100.f;
	app->bullet_def[4].damage = 40.f;
	app->bullet_def[4].size = (t_vector2){0.5f, 0.5f};
	app->bullet_def[5].speed = 8.f;
	app->bullet_def[5].damage = 30.f;
	app->bullet_def[5].size = (t_vector2){0.5f, 0.5f};
	app->bullet_def[6].speed = 10.f;
	app->bullet_def[6].damage = 25.f;
	app->bullet_def[6].size = (t_vector2){0.5f, 0.5f};
	app->bullet_def[7].speed = 50.f;
	app->bullet_def[7].damage = 20.f;
	app->bullet_def[7].size = (t_vector2){0.5f, 0.5f};
}

void	define_weapons(t_app *app)
{
	app->weapons_def[0].type = 0;
	app->weapons_def[0].magazine = 0;
	app->weapons_def[0].fire_rate = 0.f;
	app->weapons_def[1].type = 4;
	app->weapons_def[1].magazine = WEAPON1_MAG;
	app->weapons_def[1].fire_rate = 0.1f;
	app->weapons_def[2].type = 5;
	app->weapons_def[2].magazine = WEAPON2_MAG;
	app->weapons_def[2].fire_rate = 1.5f;
	app->weapons_def[3].type = 7;
	app->weapons_def[3].magazine = WEAPON3_MAG;
	app->weapons_def[3].fire_rate = 1.f;
}
