/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 16:27:15 by htahvana          #+#    #+#             */
/*   Updated: 2022/10/17 16:18:33 by htahvana         ###   ########.fr       */
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


//check if list is convex, vertex_side from every point to every other point


//compare two wall lists check if new points are inside check points
//this is awful, would be better if I used a max_limited array of elements
static t_bool	check_points(t_vec2list *walls, t_vec2list *points)
{
	t_vec2list *new;
	t_vec2list *tmp;

	new = points;
	tmp = walls;
	if(tmp == new)
		return (FALSE);
	while(tmp)
	{
		new = points->next;
		while(new != points)
		{
			if(ft_vertex_side((t_vertex2){tmp->point, tmp->next->point}, new->point))
				return (FALSE);
			new = new->next;
		}
		tmp = tmp->next;
		if(tmp == walls)
			break ;
	}
	return (TRUE);
}


t_sectorlist	*find_parent_sector(t_app *app, t_sectorlist *sector)
{
	t_sectorlist *tmp;

	tmp = app->sectors;
	while (tmp)
	{
		if(check_points(tmp->wall_list, sector->wall_list))
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