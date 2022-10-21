/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 16:27:15 by htahvana          #+#    #+#             */
/*   Updated: 2022/10/21 13:41:46 by htahvana         ###   ########.fr       */
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
int		get_sector_id(t_app *app, t_sector_lst *sector)
{
	t_sector_lst	*tmp;
	int				i;

	i = 0;
	if(!sector)
		return (-1);
	tmp = app->sectors;
	while(tmp != sector)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}


//WIP
void	sector_delone(t_sector_lst **sector, void (*del)(void*, size_t))
{
	(void)del;
	int i;

	i = 0;
	if((*sector)->parent_sector)
	{
		while ((*sector)->parent_sector->member_sectors[i] != *sector)
			i++;
		(*sector)->parent_sector->member_sectors[i] = NULL;
		while (++i < MAX_MEMBER_SECTORS && (*sector)->parent_sector->member_sectors[i])
		{
			(*sector)->parent_sector->member_sectors[i - 1] = (*sector)->parent_sector->member_sectors[i];
			(*sector)->parent_sector->member_sectors[i] = NULL;
		}
		(*sector)->parent_sector = NULL;
	}
	free(*sector);
	*sector = NULL;
}

/**
 * Pop out the selected sector from the sector list if the sector has no members, runs del on it and returns the popped sector.
 * 
 */
t_sector_lst *sector_pop(t_app *app, t_sector_lst **pop, void (*del)(void *, size_t))
{
	t_sector_lst *prev;
	t_sector_lst *head;

	if((*pop)->member_sectors[0] || !(app->sectors) || !pop || !(*pop))
		return (NULL);
	prev = NULL;
	head = app->sectors;
	while(head->next && head != *pop)
	{
		prev = head;
		head = head->next;
	}
	if (head == *pop)
	{
		if(prev)
			prev->next = (*pop)->next;
		if(head == app->sectors)
			app->sectors = (*pop)->next;
		if(del)
			sector_delone(&(app->active_sector), del);
		app->active_sector = NULL;
		app->sectorcount--;
	}
	return (*pop);
}

/**
 * returns the clicked sector, by checking if 
 */
t_sector_lst *click_sector(t_app *app)
{
	t_sector_lst *tmp;

	tmp = app->sectors;
	while(tmp)
	{
		if(inside_sector_check(app, tmp))
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


//check if list is convex, vertex_side from every point to every other point

/**
 * Handles the manual linking event using active wall and active sector
 * 
 * activate on a selected wall, navigate to link target sector, activate again
 */
void link_wall_to_sector(t_app *app)
{

	if(app->list_ongoing || app->list_creation)
	{
		app->portal_selection = FALSE; 
		app->active_last = NULL;
	}
		//add check the wall is not in itself
	if(app->portal_selection && app->active_sector && app->active_last)
	{
		app->active_last->wall_type = get_sector_id(app, app->active_sector);
		app->portal_selection = FALSE;
		app->active_last = NULL;
	}
	else if(!app->portal_selection && app->active)
	{
		app->portal_selection = TRUE;
		app->active_last = app->active;
	}
}

/**
 * Returns true if the click is inside a convex sector, checking the point side to all walls
 */
int	inside_sector_check(t_app *app, t_sector_lst *sector)
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

/**
 * Finds and returns the wall in the sector that is furthest from the parallel line to selected point
 * 
 * ft_vector_length(c) * (sin(ft_vector_angle(line, c))
 * c = vector to iterated point
 */
t_vec2list	*find_opposite_point(t_sector_lst *sector, t_vec2list *point)
{
	t_vector2 c;
	t_vec2list *head;
	t_vec2list *selection;
	double	opposite;
	double	max;

	max = 0.0f;
	head = sector->wall_list;
	while (head->next != sector->wall_list )
	{
		c = (t_vector2){head->point.x - point->point.x, head->point.y - point->point.y};
		opposite = ft_vector_length(c) * sin(ft_vector_angle((t_vector2){point->next->point.x - point->point.x, point->next->point.y - point->point.y}, c));
		if(opposite > max)
		{
			max = opposite;
			selection = head;
		}
		head = head->next;
	}
		return (selection);
		//ft_printf(" opposite distance %f, \n", ft_vector_length(c) * ( sin(ft_vector_angle(line, c))));
}
