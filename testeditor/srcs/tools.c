/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 16:27:15 by htahvana          #+#    #+#             */
/*   Updated: 2022/10/20 14:23:48 by htahvana         ###   ########.fr       */
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

int		get_sector_id(t_app *app, t_sectorlist *sector)
{
	t_sectorlist	*tmp;
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

void	sector_delone(t_sectorlist **sector, void (*del)(void*, size_t))
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


t_sectorlist *sector_pop(t_app *app, t_sectorlist **pop, void (*del)(void *, size_t))
{
	t_sectorlist *prev;
	t_sectorlist *head;

	if(!(app->sectors) || !pop || !(*pop))
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


t_sectorlist *click_sector(t_app *app)
{
	t_sectorlist *tmp;

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

void link_wall_to_sector(t_app *app)
{

	if(app->list_ongoing || app->list_creation)
	{
		app->portal_selection = FALSE; 
		app->active_last = NULL;
	}
		//add scheck the wall is not in itself
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

void	sector_edit(t_app *app, SDL_Keycode key)
{
	if(key == SDLK_UP)
	{
		if(app->ceiling_edit)
			app->active_sector->ceil_height += HEIGHT_INC;
		if(app->floor_edit)
			app->active_sector->floor_height += HEIGHT_INC;
		if(app->light_edit)
			app->active_sector->light++;
	}
	else if(key == SDLK_DOWN)
	{
		if(app->ceiling_edit)
			app->active_sector->ceil_height -= HEIGHT_INC;
		if(app->floor_edit)
			app->active_sector->floor_height -= HEIGHT_INC;
		if(app->light_edit)
			app->active_sector->light--;
	}
	else if(key == SDLK_LEFT)
	{
		if(app->ceiling_edit && app->active_sector->ceil_tex > 0)
			app->active_sector->ceil_tex--;
		if(app->floor_edit && app->active_sector->floor_tex > 0)
			app->active_sector->floor_tex--;
	}
	else if(key == SDLK_RIGHT)
	{
		if(app->ceiling_edit && app->active_sector->ceil_tex < MAX_TEX_COUNT)
			app->active_sector->ceil_tex++;
		if(app->floor_edit && app->active_sector->floor_tex < MAX_TEX_COUNT)
			app->active_sector->floor_tex++;
	}
}