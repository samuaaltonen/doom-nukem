/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bullet_fire.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:52:53 by htahvana          #+#    #+#             */
/*   Updated: 2023/02/21 14:50:14 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

static void	init_bullet_info(t_app *app, int id, t_vector3 start, t_point info)
{
	app->bullets[id].start = (t_vector2){start.x, start.y};
	app->bullets[id].start_z = start.z;
	app->bullets[id].type = info.x;
	app->bullets[id].sector = info.y;
}

/**
 * @brief Fire calculates the entire lifetime of a bullet to just update
 * 
 * @param app 
 * @param target_dir 
 * @param start 
 * @param info info.x = type, info.y = sector
 */
void	fire(t_app *app, t_vector3 target_dir, t_vector3 start, t_point info)
{
	int	i;

	if (app->bullets_active >= MAX_TEMP_OBJECTS - 1)
		return ;
	i = 0;
	while (i < MAX_TEMP_OBJECTS - 1 && app->bullets[i].type != -1)
		i++;
	init_bullet_info(app, i, start, info);
	calc_bullet_end(app, &(app->bullets[i]), target_dir);
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
	return ;
}

/**
 * @brief Melee is the same as fire except it stays still for the duration
 * 
 * @param app 
 * @param target_dir projectile direction
 * @param start start position 
 * @param info x is the bullet type, y is the bullet sector
 */
void	melee(t_app *app, t_vector3 target_dir, t_vector3 start, t_point info)
{
	int	i;

	if (app->bullets_active >= MAX_TEMP_OBJECTS - 1)
		return ;
	i = 0;
	while (i < MAX_TEMP_OBJECTS - 1 && app->bullets[i].type != -1)
		i++;
	app->bullets[i].start = (t_vector2){start.x, start.y};
	app->bullets[i].start_z = start.z;
	app->bullets[i].type = info.x;
	app->bullets[i].sector = info.y;
	app->bullets[i].end = ft_vector2_add(app->bullets[i].start,
			ft_vec2_mult((t_vector2){target_dir.x, target_dir.y}, 25.f));
	app->bullets[i].end_z = target_dir.z + 0.025f;
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
