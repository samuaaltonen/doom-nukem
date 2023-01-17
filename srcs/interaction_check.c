/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interaction_check.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 16:06:37 by saaltone          #+#    #+#             */
/*   Updated: 2023/01/16 22:50:52 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * @brief Checks if player is near and in front of activation decor.
 * 
 * @param app 
 * @param sector_id 
 * @param wall_id 
 * @return t_bool 
 */
static t_bool	is_near_activation_decor(t_app *app, int sector_id, int wall_id)
{
	t_vector2	decor_start;
	t_vector2	decor_center;
	double		decor_floor;
	t_vector2	wall_vector;
	t_line		wall_line;

	if (sector_id == -1)
		return (FALSE);
	wall_line = get_wall_line(app, sector_id, wall_id);
	wall_vector = ft_vector2_sub(wall_line.b, wall_line.a);
	decor_start = ft_vector2_add(wall_line.a, ft_vector_resize(wall_vector,
				(ft_vector_length(wall_vector) - DECOR_SIZE) / 2
				+ app->sectors[sector_id].decor_offset[wall_id].x));
	decor_center = ft_vector2_add(decor_start, ft_vector_resize(wall_vector,
				DECOR_SIZE / 2));
	if (ft_vector_length(ft_vector2_sub(app->player.pos, decor_center))
		> INTERACTION_ACTION_DISTANCE)
		return (FALSE);
	decor_floor = (app->sectors[sector_id].ceil_height
			- app->sectors[sector_id].floor_height - DECOR_SIZE) / 2
		+ app->sectors[sector_id].floor_height
		+ app->sectors[sector_id].decor_offset[wall_id].y;
	if (fabs(decor_floor - app->player.elevation) > INTERACTION_ACTION_DISTANCE)
		return (FALSE);
	return (TRUE);
}

/**
 * @brief Checks if interaction requires key and if so, uses one from player
 * inventory.
 * 
 * @param app 
 * @param interaction 
 * @return t_bool 
 */
static t_bool	check_key_requirement(t_app *app, t_interaction *interaction)
{
	if (!interaction->requires_key)
		return (TRUE);
	if (app->player.inventory.key <= 0)
		return (FALSE);
	app->player.inventory.key--;
	return (TRUE);
}

/**
 * @brief Loops through interaction array and checks if any interactivable
 * events could be triggered.
 * 
 * @param app 
 */
void	interaction_check(t_app *app)
{
	int	i;

	i = -1;
	while (++i < MAX_INTERACTIONS)
	{
		if (app->interactions[i].event_id == EVENT_NONE)
			continue ;
		if (app->interactions[i].activation_wall != -1
			&& is_near_activation_decor(app,
				app->interactions[i].activation_sector,
				app->interactions[i].activation_wall)
			&& check_key_requirement(app, &app->interactions[i]))
			interaction_trigger(app, i);
	}
}

/**
 * @brief Loops through interaction array and checks if any interactivable
 * events are can be triggered by entering the sector.
 * 
 * @param app 
 * @param sector_id 
 */
void	interaction_check_portal(t_app *app, int sector_id)
{
	int	i;

	i = -1;
	while (++i < MAX_INTERACTIONS)
	{
		if (app->interactions[i].event_id == EVENT_NONE)
			continue ;
		if (app->interactions[i].activation_sector == sector_id
			&& app->interactions[i].activation_wall == -1
			&& check_key_requirement(app, &app->interactions[i]))
			interaction_trigger(app, i);
	}
}
