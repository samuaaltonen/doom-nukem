/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector_wall_vertex.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 16:47:35 by saaltone          #+#    #+#             */
/*   Updated: 2022/10/14 15:03:11 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * Returns vertex from sector by wall id.
 */
t_vertex2	get_wall_vertex(t_app *app, int sector_id, int wall_id)
{
	(void)app;
	if (app->sectors[sector_id].corner_count == wall_id + 1)
		return (t_vertex2){
			app->sectors[sector_id].corners[wall_id],
			app->sectors[sector_id].corners[0],
		};
	else
		return (t_vertex2){
			app->sectors[sector_id].corners[wall_id],
			app->sectors[sector_id].corners[wall_id + 1],
		};
}
