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
 * Returns line from sector by wall id.
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
