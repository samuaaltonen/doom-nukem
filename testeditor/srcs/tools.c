/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 16:27:15 by htahvana          #+#    #+#             */
/*   Updated: 2022/10/17 14:18:52 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

void	change_all_wall_tex(t_vec2list *walls, int wall_tex)
{
	t_vec2list *tmp;

	tmp = walls;
	while(tmp)
	{
		tmp->wall_texture = wall_tex;
		tmp = tmp->next;
		if(tmp == walls)
			break;
	}
}

t_sectorlist *click_sector(t_app *app)
{
	t_sectorlist *tmp;

	tmp = app->sectors;
	while(tmp)
	{
		if(inside_sector_check(app, tmp))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

int	inside_sector_check(t_app *app, t_sectorlist *sector)
{
	t_vec2list *tmp;

	tmp = sector->wall_list;
	while (tmp)
	{
		if(ft_vertex_side((t_vertex2){tmp->point, tmp->next->point}, app->mouse_click))
			return (0);
		tmp = tmp->next;
		if(tmp == sector->wall_list)
			break;
	}

	return(1);
}