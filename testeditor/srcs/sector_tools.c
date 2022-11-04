/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 13:53:18 by htahvana          #+#    #+#             */
/*   Updated: 2022/11/03 12:48:18 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * @brief Get the sector id of the sector parameter
 * 
 * @param app 
 * @param sector 
 * @return int 
 */
int	get_sector_id(t_app *app, t_sector_lst *sector)
{
	t_sector_lst	*tmp;
	int				i;

	i = 0;
	if (!sector)
		return (-1);
	tmp = app->sectors;
	while (tmp != sector)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

/**
 * returns the clicked sector, by checking if 
 */
t_sector_lst	*click_sector(t_app *app)
{
	t_sector_lst	*tmp;

	tmp = app->sectors;
	while (tmp)
	{
		if (inside_sector_check(app, tmp))
		{
			while (tmp->parent_sector)
			{
				tmp = tmp->parent_sector;
			}
			return (tmp);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

/**
 * Returns true if the click is inside a convex sector, checking the point
 * side to all walls.
 */
int	inside_sector_check(t_app *app, t_sector_lst *sector)
{
	t_vec2_lst	*tmp;

	tmp = sector->wall_list;
	while (tmp)
	{
		if (ft_line_side((t_line){tmp->point, tmp->next->point},
			app->mouse_track))
			return (0);
		tmp = tmp->next;
		if (tmp == sector->wall_list)
			break ;
	}
	return (1);
}
