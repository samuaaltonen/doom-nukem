/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_weapons.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 18:27:42 by htahvana          #+#    #+#             */
/*   Updated: 2023/02/21 14:27:24 by saaltone         ###   ########.fr       */
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
	app->bullet_def[0].speed = 5.0;
	app->bullet_def[0].damage = 20.0;
	app->bullet_def[0].size = (t_vector2){0.5, 0.5};
	app->bullet_def[1].speed = 5.0;
	app->bullet_def[1].damage = 25.0;
	app->bullet_def[1].size = (t_vector2){0.5, 0.5};
	app->bullet_def[2].speed = 8.0;
	app->bullet_def[2].damage = 25.0;
	app->bullet_def[2].size = (t_vector2){0.5, 0.5};
	app->bullet_def[3].speed = 8.0;
	app->bullet_def[3].damage = 25.0;
	app->bullet_def[3].size = (t_vector2){0.5, 0.5};
	app->bullet_def[4].speed = 10.0;
	app->bullet_def[4].damage = 40.0;
	app->bullet_def[4].size = (t_vector2){0.5, 0.5};
	app->bullet_def[5].speed = 8.0;
	app->bullet_def[5].damage = 90.0;
	app->bullet_def[5].size = (t_vector2){0.5, 0.5};
	app->bullet_def[6].speed = 10.0;
	app->bullet_def[6].damage = 25.0;
	app->bullet_def[6].size = (t_vector2){0.5, 0.5};
	app->bullet_def[7].speed = 10.0;
	app->bullet_def[7].damage = 45.0;
	app->bullet_def[7].size = (t_vector2){0.5, 0.5};
}

void	define_weapons(t_app *app)
{
	app->weapons_def[0].type = 0;
	app->weapons_def[0].magazine = 0;
	app->weapons_def[0].fire_rate = 0.0;
	app->weapons_def[1].type = 4;
	app->weapons_def[1].magazine = WEAPON1_MAG;
	app->weapons_def[1].fire_rate = 0.2;
	app->weapons_def[2].type = 5;
	app->weapons_def[2].magazine = WEAPON2_MAG;
	app->weapons_def[2].fire_rate = 1.0;
	app->weapons_def[3].type = 7;
	app->weapons_def[3].magazine = WEAPON3_MAG;
	app->weapons_def[3].fire_rate = 1.0;
}
