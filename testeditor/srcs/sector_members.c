/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector_members.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 11:47:05 by ssulkuma          #+#    #+#             */
/*   Updated: 2022/11/24 14:14:09 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * Adds a member sector the an existing parent sector.
*/
void	add_member_sector(t_sector_lst *parent, t_sector_lst *child)
{
	int		i;

	i = 0;
	if (parent && child)
	{
		while (parent->member_sectors[i])
			i++;
		if (i >= MAX_MEMBER_SECTORS)
			exit_error("Trying to add too many members.\n");
		parent->member_sectors[i] = child;
	}
}

/**
 * @brief Finds which member sector in active sector was clicked
 * 
 * @param app 
 * @return t_sector_lst* 
 */
t_sector_lst	*find_child_sector(t_app *app)
{
	int				i;
	t_sector_lst	*tmp;
	t_vec2_lst		*wall;

	wall = app->active_sector->wall_list;
	while (wall)
	{
		if (wall->point.x == app->mouse_track.x
			&& wall->point.y == app->mouse_track.y)
			return (NULL);
		wall = wall->next;
		if (wall == app->active_sector->wall_list)
			break ;
	}
	i = 0;
	while (i < MAX_MEMBER_SECTORS && app->active_sector->member_sectors[i])
	{
		tmp = app->active_sector->member_sectors[i];
		if (inside_sector_check(tmp, &app->mouse_track))
			return (tmp);
		i++;
	}
	return (NULL);
}
