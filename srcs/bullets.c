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
 * @brief Fire calculates the entire lifetime of a bullet to later just render
 * info.x = type, info.y = sector
 * @param app 
 * @param target_dir 
 * @param start 
 * @param info 
 */
void	fire(t_app *app, t_vector3 target_dir, t_vector3 start, t_point info)
{
	int	i;

	if (app->bullets_active >= MAX_TEMP_OBJECTS - 1)
		return ;
	i = 0;
	while (i < MAX_TEMP_OBJECTS && app->bullets[i].type != -1)
		i++;
	app->bullets[i].start = (t_vector2){start.x, start.y};
	app->bullets[i].start_z = start.z;
	app->bullets[i].type = info.x;
	app->bullets[i].sector = info.y;
	calc_end(app, &(app->bullets[i]), target_dir);
	app->bullets[i].timer = ft_vector_length(
			ft_vector2_sub(app->bullets[i].end, app->bullets[i].start))
		/ app->bullet_def[app->bullets[i].type].speed;
	app->bullets[i].end = ft_vector2_normalize(
			ft_vector2_sub(app->bullets[i].end, app->bullets[i].start));
	if (app->bullets[i].type == PROJECTILE_ENEMY)
	{
		app->bullets[i].timer = 0.25f;
		app->bullets[i].end = (t_vector2){0.f, 0.f};
		app->bullets[i].end_z = 0.f;
	}
	app->bullets_active++;
	add_fire_movement(app);
	return ;
}

/**
 * @brief Kills bullets, specific types trigger events(explosion at the end)
 * 
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

/**
 * @brief Melee is the same as fire except it stays still for the duration
 * 
 * @param app 
 * @param target_dir 
 * @param start 
 * @param info 
 */
void	melee(t_app *app, t_vector3 target_dir, t_vector3 start, t_point info)
{
	int	i;

	if (app->bullets_active >= MAX_TEMP_OBJECTS - 1)
		return ;
	i = 0;
	while (i < MAX_TEMP_OBJECTS && app->bullets[i].type != -1)
		i++;
	app->bullets[i].start = (t_vector2){start.x, start.y};
	app->bullets[i].start_z = start.z;
	app->bullets[i].type = info.x;
	app->bullets[i].sector = info.y;
	calc_end(app, &(app->bullets[i]), target_dir);
	app->bullets[i].end = ft_vector2_normalize(
			ft_vector2_sub(app->bullets[i].end, app->bullets[i].start));
	app->bullets[i].timer = 0.25f;
	if (!(app->bullets[i].type == 0))
		app->bullets[i].start = ft_vector2_add(app->bullets[i].start,
				ft_vec2_mult(app->bullets[i].end, 0.5f));
	app->bullets[i].end = (t_vector2){0.f, 0.f};
	app->bullets[i].end_z = 0.f;
	app->bullets_active++;
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
