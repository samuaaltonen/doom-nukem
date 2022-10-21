/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_menu.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 16:33:06 by htahvana          #+#    #+#             */
/*   Updated: 2022/10/21 13:36:06 by htahvana         ###   ########.fr       */
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
void	change_selected_wall_tex(t_app *app, t_vec2list *wall, int wall_id)
{
	(void)app;
	wall->wall_texture = wall_id;
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

/**
 * @brief changes all walls in the given list to wall_tex param
 * 
 * @param walls 
 * @param wall_tex 
 */
void	change_walls_tex(t_vec2list *walls, int wall_tex)
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