/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 16:27:15 by htahvana          #+#    #+#             */
/*   Updated: 2022/10/21 13:11:04 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * @brief changes all walls in the given list to wall_tex param
 * 
 * @param walls 
 * @param wall_tex 
 */
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

/**
 * @brief Get the sector id of the sector parameter
 * 
 * @param app 
 * @param sector 
 * @return int 
 */
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


//WIP
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

/**
 * Pop out the selected sector from the sector list if the sector has no members, runs del on it and returns the popped sector.
 * 
 */
t_sectorlist *sector_pop(t_app *app, t_sectorlist **pop, void (*del)(void *, size_t))
{
	t_sectorlist *prev;
	t_sectorlist *head;

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

/**
 * Handles sector changes depending on active states and pressed keys
 * Up and Down for heights
 * Left and Right for textures
 * U and J for slope heights
 */
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
	else if(key == SDLK_u)
	{
		if(app->ceiling_edit)
			app->active_sector->ceil_slope_height += HEIGHT_INC;
		if(app->floor_edit)
			app->active_sector->floor_slope_height += HEIGHT_INC;
	}
	else if(key == SDLK_j)
	{
		if(app->ceiling_edit)
			app->active_sector->ceil_slope_height -= HEIGHT_INC;
		if(app->floor_edit)
			app->active_sector->floor_slope_height -= HEIGHT_INC;
	}
}

/**
 * Finds and returns the wall in the sector that is furthest from the parallel line to selected point
 * 
 * ft_vector_length(c) * (sin(ft_vector_angle(line, c))
 * c = vector to iterated point
 */
t_vec2list	*find_opposite_point(t_sectorlist *sector, t_vec2list *point)
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


/**
 * Changes all wall types of the selected sector to it's parent linking them
 */
void	change_walls_type(t_app *app, t_sectorlist *sector)
{
	t_vec2list *head;

	if(!sector)
		return ;
	head = sector->wall_list;
	while(head)
	{
		head->wall_type = get_sector_id(app, sector->parent_sector);

		head = head->next;
		if(head == sector->wall_list)
			break;
	}
}
