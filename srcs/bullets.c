/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bullets.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 14:01:41 by htahvana          #+#    #+#             */
/*   Updated: 2023/01/16 19:04:00 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * @brief Kills bullets, specific types trigger events(explosion at the end)
 * the explosion is calculated to be slightly back out from the wall/floor
 * @param app 
 * @param bullet 
 */
void	kill_bullet(t_app *app, t_bullet *bullet)
{
	if (bullet->type == PROJECTILE_ROCKET || bullet->type == 4)
		melee(app, (t_vector3){0.f, 0.f, 0.f}, ft_vec2_to_vec3(
				ft_vector2_sub(bullet->start, ft_vec2_mult(bullet->end, 0.15f)),
				bullet->start_z - bullet->end_z * 0.12f),
			(t_point){PROJECTILE_EXPLOSION, bullet->sector});
	bullet->type = -1;
	app->bullets_active--;
}

static void	start_bullet(t_app *app, t_bullet *bullet)
{
	double	delta;

	delta = app->conf->delta_time;
	if (bullet->timer < 0)
		delta += bullet->timer;
	bullet->start = ft_vector2_add(bullet->start,
			ft_vec2_mult(bullet->end, delta
				* app->bullet_def[bullet->type].speed));
	bullet->start_z += bullet->end_z
		* delta
		* app->bullet_def[bullet->type].speed;
}

/**
 * @brief loops through the bullet array adds time to timers and updats positions
 * 
 * @param app 
 */
void	update_bullets(t_app *app)
{
	int			i;
	t_bullet	*bullet;

	i = -1;
	while (++i < MAX_TEMP_OBJECTS)
	{
		bullet = &(app->bullets[i]);
		if (bullet->type == -1)
			continue ;
		if (bullet->timer > 0)
			bullet->timer -= app->conf->delta_time;
		else
		{
			kill_bullet(app, bullet);
			if (app->sectors[bullet->sector].wall_types[bullet->wall_id] > -1
				&& app->sectors[bullet->sector].wall_textures[bullet->wall_id]
				== PARTIALLY_TRANSPARENT_TEXTURE_ID)
				app->sectors[bullet->sector].wall_textures[bullet->wall_id]++;
		}
		start_bullet(app, bullet);
	}
}
