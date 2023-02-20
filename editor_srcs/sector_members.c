/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector_members.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 11:47:05 by ssulkuma          #+#    #+#             */
/*   Updated: 2023/02/20 12:40:27 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * @brief Adds a member sector the an existing parent sector.
 * 
 * @param parent
 * @param child
*/
void	add_member_sector(t_sector_list *parent, t_sector_list *child)
{
	int		i;

	i = 0;
	if (parent && child)
	{
		while (parent->member_sectors[i])
			i++;
		if (i >= MAX_MEMBER_SECTORS)
			exit_error(MSG_ERROR_MEMBER_LIMIT);
		parent->member_sectors[i] = child;
	}
}

/**
 * @brief Finds which member sector in active sector was clicked.
 * 
 * @param app 
 * @return t_sector_list* 
 */
t_sector_list	*find_child_sector(t_app *app)
{
	int				i;
	t_sector_list	*tmp;
	t_wall_list		*wall;

	wall = app->active_sector->wall_list;
	while (wall)
	{
		if (ft_vector_compare(wall->point, app->mouse_track))
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
 * @brief Finds child sector in parent for target sector.
 * 
 * @param app
 * @param parent
 * @return t_sector_list*
*/
t_sector_list	*find_child_target_sector(t_app *app, t_sector_list *parent)
{
	int				i;
	t_sector_list	*tmp;
	t_wall_list		*wall;

	if (!parent)
		return (NULL);
	wall = parent->wall_list;
	while (wall)
	{
		if (ft_vector_compare(wall->point, app->mouse_track))
			return (NULL);
		wall = wall->next;
		if (wall == parent->wall_list)
			break ;
	}
	i = 0;
	while (i < MAX_MEMBER_SECTORS && parent->member_sectors[i])
	{
		tmp = parent->member_sectors[i];
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
int	get_member_sector_count(t_sector_list *parent)
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
