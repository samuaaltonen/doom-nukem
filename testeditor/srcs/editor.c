/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 13:03:35 by htahvana          #+#    #+#             */
/*   Updated: 2022/10/21 14:09:55 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * @brief check if clicked point is already part of the same list
 * 
 * @param app 
 * @return t_bool 
 */
t_bool	valid_point(t_app *app)
{
	t_vec2_lst	*tmp;

	tmp = app->active;
	while (tmp)
	{
		if (tmp->point.x == app->mouse_click.x && tmp->point.y == app->mouse_click.y)
			return (FALSE);
		tmp = tmp->next;
	}
return (TRUE);
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