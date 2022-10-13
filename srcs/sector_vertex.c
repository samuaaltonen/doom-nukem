/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector_vertex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 16:47:35 by saaltone          #+#    #+#             */
/*   Updated: 2022/10/10 12:12:34 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * Returns vertex from sector by wall id.
 */
t_vertex2	get_sector_vertex_by_corner(t_app *app, int sector_id, int wall_id)
{
	(void)app;
	if (test_sectors[sector_id].corner_count == wall_id + 1)
		return (t_vertex2){
			test_sectors[sector_id].corners[wall_id],
			test_sectors[sector_id].corners[0],
		};
	else
		return (t_vertex2){
			test_sectors[sector_id].corners[wall_id],
			test_sectors[sector_id].corners[wall_id + 1],
		};
}