/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector_wall_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 16:47:35 by saaltone          #+#    #+#             */
/*   Updated: 2022/10/25 10:45:47 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * @brief Returns wall vector from sector by wall id.
 * 
 * @param app 
 * @param sector_id 
 * @param wall_id 
 * @return t_vector2 
 */
t_vector2	get_wall_vector(t_app *app, int sector_id, int wall_id)
{
	if (app->sectors[sector_id].corner_count == wall_id + 1)
		return (ft_vector2_sub(app->sectors[sector_id].corners[0],
			app->sectors[sector_id].corners[wall_id]));
	return (ft_vector2_sub(app->sectors[sector_id].corners[wall_id + 1],
		app->sectors[sector_id].corners[wall_id]));
}

/**
 * @brief Returns line from sector by wall id.
 * 
 * @param app 
 * @param sector_id 
 * @param wall_id 
 * @return t_line 
 */
t_line	get_wall_line(t_app *app, int sector_id, int wall_id)
{
	if (app->sectors[sector_id].corner_count == wall_id + 1)
		return ((t_line){
			app->sectors[sector_id].corners[wall_id],
			app->sectors[sector_id].corners[0],
		});
	return ((t_line){
		app->sectors[sector_id].corners[wall_id],
		app->sectors[sector_id].corners[wall_id + 1],
	});
}
