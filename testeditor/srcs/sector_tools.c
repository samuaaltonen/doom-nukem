/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 13:53:18 by htahvana          #+#    #+#             */
/*   Updated: 2022/12/07 13:59:53 by ssulkuma         ###   ########.fr       */
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
		if (inside_sector_check(tmp, &app->mouse_track))
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
int	inside_sector_check(t_sector_lst *sector, t_vector2 *mouse)
{
	t_vec2_lst	*tmp;

	tmp = sector->wall_list;
	while (tmp)
	{
		if (ft_line_side((t_line){tmp->point, tmp->next->point}, (*mouse)))
			return (0);
		tmp = tmp->next;
		if (tmp == sector->wall_list)
			break ;
	}
	return (1);
}

/**
 * Checks if the sector is valid and can be completed. Returns 1 if sector is
 * valid and 0 if sector is invalid. If invalid, cancels list creation and
 * deletes the drawn lines.
*/
t_bool	valid_sector(t_app *app)
{
	t_vec2_lst	*tmp;

	tmp = app->active;
	while (tmp)
	{
		if (tmp->next && ft_line_side((t_line){tmp->point, tmp->next->point},
			app->mouse_track))
		{
			cancel_list_creation(app);
			return (FALSE);
		}
		tmp = tmp->next;
	}
	return (TRUE);
}
