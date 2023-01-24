/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector_members.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 11:47:05 by ssulkuma          #+#    #+#             */
/*   Updated: 2023/01/16 13:32:05 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * @brief Adds a member sector the an existing parent sector.
 * 
 * @param parent
 * @param child
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
 * @brief Finds which member sector in active sector was clicked.
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

/**
 * @brief Counts how many member sectors does the given sector have.
 * 
 * @param parent
 * @return int
*/
int	get_member_sector_count(t_sector_lst *parent)
{
	int		index;

	if (!parent)
		return (-1);
	index = 0;
	while (index < MAX_MEMBER_SECTORS)
	{
		if (!parent->member_sectors[index])
			break ;
		index++;
	}
	return (index);
}
