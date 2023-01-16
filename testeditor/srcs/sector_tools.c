/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 13:53:18 by htahvana          #+#    #+#             */
/*   Updated: 2023/01/16 13:59:32 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * @brief Get the sector id of the sector parameter.
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
 * @brief Checks that the mouse click is inside a sector and returns the
 * clicked sector.
 * 
 * @param app
 * @return t_sector_lst*
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
 * @brief Returns true if the click is inside a convex sector, checking the 
 * point side to all walls.
 * 
 * @param sector
 * @param mouse
 * @return int
 */
int	inside_sector_check(t_sector_lst *sector, t_vector2 *mouse)
{
	t_vec2_lst	*tmp;

	tmp = sector->wall_list;
	while (tmp)
	{
		if (ft_line_side((t_line){tmp->point, tmp->next->point}, (*mouse)))
			return (FALSE);
		tmp = tmp->next;
		if (tmp == sector->wall_list)
			break ;
	}
	return (TRUE);
}

/**
 * @brief Checks if the sector is valid and can be completed. Returns true if 
 * sector is valid and false if sector is invalid. If invalid, cancels list
 * creation and deletes the drawn lines.
 * 
 * @param app
 * @return t_bool
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

/**
 * @brief Deletes the given sector. If sector is a member sector, deletes it
 * and moves the member sectors in the array one step backwards.
 * 
 * @param sector
*/
void	sector_delone(t_sector_lst **sector)
{
	int		i;

	i = 0;
	if ((*sector)->parent_sector)
	{
		while ((*sector)->parent_sector->member_sectors[i] != *sector)
			i++;
		(*sector)->parent_sector->member_sectors[i] = NULL;
		while (++i < MAX_MEMBER_SECTORS
			&& (*sector)->parent_sector->member_sectors[i])
		{
			(*sector)->parent_sector->member_sectors[i - 1]
				= (*sector)->parent_sector->member_sectors[i];
			(*sector)->parent_sector->member_sectors[i] = NULL;
		}
		(*sector)->parent_sector = NULL;
	}
	del_vector_list(&((*sector)->wall_list));
	free(*sector);
	*sector = NULL;
}
