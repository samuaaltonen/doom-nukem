/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_menu.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 16:33:06 by htahvana          #+#    #+#             */
/*   Updated: 2022/11/03 11:39:04 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * @brief Changes the selected wall texture to given id
 * 
 * @param app 
 * @param wall 
 * @param wall_id 
 */
void	change_selected_wall_tex(t_app *app, t_vec2_lst *wall, int wall_id)
{
	wall->tex = wall_id;
	(void)app;
}

/**
 * Changes all wall types of the selected sector to it's parent linking them
 */
void	change_walls_type(t_app *app, t_sector_lst *sector)
{
	t_vec2_lst	*head;

	if (!sector)
		return ;
	head = sector->wall_list;
	while (head)
	{
		head->type = get_sector_id(app, sector->parent_sector);
		head = head->next;
		if (head == sector->wall_list)
			break ;
	}
}

/**
 * @brief changes all walls in the given list to wall_tex param
 * 
 * @param walls 
 * @param wall_tex 
 */
void	change_walls_tex(t_vec2_lst *walls, int wall_tex)
{
	t_vec2_lst	*tmp;

	tmp = walls;
	while (tmp)
	{
		tmp->tex = wall_tex;
		tmp = tmp->next;
		if (tmp == walls)
			break ;
	}
}
