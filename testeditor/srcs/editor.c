/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 13:03:35 by htahvana          #+#    #+#             */
/*   Updated: 2022/10/21 13:33:07 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

void	zoom_slider(t_app *app)
{
	int		x;
	int		y;
	int		zoom_point;

	y = app->surface->h / 4;
	zoom_point = y + (app->surface->h / 2) / 6 * app->zoom_range;
	while (y <= (app->surface->h - (app->surface->h / 4) + 10))
	{
		x = app->surface->w - 30;
		while (x <= (app->surface->w - 20))
		{
			if (x == (app->surface->w - 25) || y == app->surface->h / 4 || y == (app->surface->h - (app->surface->h / 4) + 10))
				put_pixel_to_surface(app->surface, x, y, 0xFFFFFF);
			if (y >= zoom_point && y <= zoom_point + 10)
				put_pixel_to_surface(app->surface, x, y, 0xFFFFFF);
			x++;
		}
		y++;
	}
	
}

/**
 * @brief check if clicked point is already part of the same list
 * 
 * @param app 
 * @return t_bool 
 */
t_bool	valid_point(t_app *app)
{
	t_vec2list	*tmp;

	tmp = app->active;
	while (tmp)
	{
		if (tmp->point.x == app->mouse_click.x && tmp->point.y == app->mouse_click.y)
			return (FALSE);
		tmp = tmp->next;
	}
return (TRUE);
}


static void	add_member_sector(t_sectorlist *parent, t_sectorlist *child)
{
	int i;

	i = 0;
	if(parent && child)
	{
		while (parent->member_sectors[i])
			i++;
		if(i >= MAX_MEMBER_SECTORS)
			exit_error("Trying to add too many members\n");
		parent->member_sectors[i] = child;
	}
}

/**
 * @brief Completes an ongoing sector
 * 
 * @param app 
 * @return t_bool 
 */
t_bool	complete_sector(t_app *app)
{
	t_sectorlist *new;

	app->active_last->next = app->active;
	new = put_sector_lst(app,new_sector_list(app->active));
	app->active = NULL;
	app->active_last = NULL;
	app->list_ongoing = FALSE;
	app->list_creation = FALSE;
	new->parent_sector = app->active_sector;
	add_member_sector(new->parent_sector, new);
	change_all_wall_tex(new->wall_list, app->sectorcount);
	change_walls_type(app, new);
 return (0);
}
