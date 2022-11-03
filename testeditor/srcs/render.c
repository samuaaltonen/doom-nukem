/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 16:18:36 by htahvana          #+#    #+#             */
/*   Updated: 2022/11/03 11:06:32 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * @brief renders all the lines for the given sector
 * 
 * @param app 
 * @param sector_start 
 */
void	render_sector(t_app *app, t_vec2_lst *sector_start)
{
	t_vec2_lst	*tmp;

	tmp = sector_start;
	while (tmp->next != NULL)
	{
		if (tmp->type > -1)
			draw_list_lines(app, tmp, tmp->next, PORTAL);
		else
			draw_list_lines(app, tmp, tmp->next, 0xEEEEEE);
		if (tmp->next == sector_start)
			break ;
		tmp = tmp->next;
	}
}

/**
 * @brief runs render sector on all the sectors in app
 * 
 * @param app 
 */
void	render_sectors(t_app *app)
{
	t_sector_lst	*tmp;

	tmp = app->sectors;
	while (tmp)
	{
		render_sector(app, tmp->wall_list);
		tmp = tmp->next;
	}
}

/**
 * @brief renders points on each point of the active sector
 * 
 * @param app 
 */
void	render_sector_points(t_app *app)
{
	t_vec2_lst	*head;

	if (app->active_sector)
	{
		head = app->active_sector->wall_list;
		while (head)
		{
			render_selection_point(app, head, 2);
			head = head->next;
			if (head == app->active_sector->wall_list)
				break ;
		}
		if (app->wall_edit)
			change_walls_tex(app->active_sector->wall_list,
				app->active_sector->wall_list->tex);
	}
}

/**
 * @brief Renders a square with given size on the given point
 * 
 * @param app 
 * @param point 
 * @param size 
 */
void	render_selection_point(t_app *app, t_vec2_lst *point, int size)
{
	t_point		min;
	t_point		max;

	if (point)
	{
		min.x = (point->point.x - app->view_pos.x)
			* (app->surface->w) / (app->view_size.x - app->view_pos.x);
		min.y = (point->point.y - app->view_pos.y)
			* (app->surface->h) / (app->view_size.y - app->view_pos.y);
		max.x = min.x + size;
		max.y = min.y + size;
		min.x = min.x - size;
		min.y = min.y - size;
		while (min.y < max.y)
		{
			min.x = max.x - size * 2;
			while (min.x < max.x)
			{
				put_pixel_to_surface(app->surface, min.x, min.y, 0xFF00FF);
				min.x++;
			}
			min.y++;
		}
	}
}
