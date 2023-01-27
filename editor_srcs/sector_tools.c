/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 13:53:18 by htahvana          #+#    #+#             */
/*   Updated: 2023/01/27 18:52:57 by htahvana         ###   ########.fr       */
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
	int			corners;

	tmp = app->active;
	corners = 0;
	while (tmp)
	{
		if (tmp->next && ft_line_side((t_line){tmp->point, tmp->next->point},
			app->mouse_track))
		{
			cancel_list_creation(app);
			return (FALSE);
		}
		tmp = tmp->next;
		corners++;
	}
	if (corners > MAX_SECTOR_CORNERS)
	{
		cancel_list_creation(app);
		return (FALSE);
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


static int	find_linkable_walls(t_app *app, t_vec2_lst *wall,
		t_sector_lst *origin, t_sector_lst *sector)
{
	int			i;
	t_vec2_lst	*target_wall;

	i = -1;
	target_wall = sector->wall_list;
	while (++i < sector->corner_count + 1)
	{
		if (ft_cmp_line_points((t_line){wall->point, wall->next->point},
				(t_line){target_wall->point, target_wall->next->point}))
		{
			target_wall->type = get_sector_id(app, origin);
			wall->type = get_sector_id(app, sector);
			return (TRUE);
		}
		target_wall = target_wall->next;
	}
	return (FALSE);
}

int	find_links(t_app *app, t_sector_lst *new)
{
	int				i;
	t_vec2_lst		*start_wall;
	t_sector_lst	*sector_list;
	int				counter;

	i = -1;
	start_wall = new->wall_list;
	sector_list = app->sectors;
	while (++i < new->corner_count)
	{
		counter = 0;
		sector_list = app->sectors;
		while (++counter < app->sector_count)
		{
			if (find_linkable_walls(app, start_wall, new, sector_list))
				break ;
			sector_list = sector_list->next;
		}
		start_wall = start_wall->next;
	}
	return (0);
}
