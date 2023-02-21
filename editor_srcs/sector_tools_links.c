/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector_tools_links.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 14:48:51 by saaltone          #+#    #+#             */
/*   Updated: 2023/02/21 14:52:35 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * @brief Finds linkable walls of a sector.
 * 
 * @param app 
 * @param wall 
 * @param origin 
 * @param sector 
 * @return int 
 */
static int	find_linkable_walls(t_app *app, t_wall_list *wall,
		t_sector_list *origin, t_sector_list *sector)
{
	int			i;
	t_wall_list	*target_wall;

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

/**
 * @brief Finds possible links to nearby sectors.
 * 
 * @param app 
 * @param new_list 
 * @return int 
 */
int	find_links(t_app *app, t_sector_list *new_list)
{
	int				i;
	t_wall_list		*start_wall;
	t_sector_list	*sector_list;
	int				counter;

	i = -1;
	start_wall = new_list->wall_list;
	while (++i < new_list->corner_count)
	{
		counter = 0;
		sector_list = app->sectors;
		while (++counter < app->sector_count)
		{
			if (find_linkable_walls(app, start_wall, new_list, sector_list))
				break ;
			sector_list = sector_list->next;
		}
		start_wall = start_wall->next;
	}
	return (0);
}
