/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_extra.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 13:55:36 by htahvana          #+#    #+#             */
/*   Updated: 2022/12/08 15:17:15 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * @brief Puts the max and min values of a bounding box of a sector to the given min and max param
 * 
 * @param app 
 * @param sector 
 * @param min 
 * @param max 
 */
static void	sector_bounds(t_app *app, t_sector_lst *sector,
									t_point *min, t_point *max)
{
	t_vec2_lst	*tmp;
	t_point		screen;

	tmp = sector->wall_list;
	min->x = (tmp->point.x - app->view_pos.x) * (app->surface->w) / (app->view_size.x - app->view_pos.x);
	min->y = (tmp->point.y - app->view_pos.y) * (app->surface->h) / (app->view_size.y - app->view_pos.y);
	max->x = min->x;
	max->y = min->y;
	while (tmp)
	{
		screen.x = (tmp->point.x - app->view_pos.x) * (app->surface->w) / (app->view_size.x - app->view_pos.x);
		screen.y = (tmp->point.y - app->view_pos.y) * (app->surface->h) / (app->view_size.y - app->view_pos.y);
		if (screen.x < min->x)
			min->x = screen.x;
		if (screen.x > max->x)
			max->x = screen.x;
		if (screen.y < min->y)
			min->y = screen.y;
		if (screen.y > max->y)
			max->y = screen.y;
		tmp = tmp->next;
		if (tmp == sector->wall_list)
			break ;
	}
}

/**
 * @brief Makes triangles for rendering from a sector
 * WIP atm only renders a rectangle bounding the sector
 * 
 * @param app 
 */
void	render_fill_active_sector(t_app *app)
{
	t_vec2_lst	*a;
	t_vec2_lst	*b;
	t_point		min;
	t_point		max;
	//t_point		cur;
	int			color;

	color = 0x202020;
	if(interaction_sector_check(app,app->active_sector))
		color = INTERACTION;
	min = (t_point){0, 0};
	max = (t_point){0, 0};
	if (app->active_sector)
	{
		a = app->active_sector->wall_list->next;
		b = app->active_sector->wall_list->next;
		sector_bounds(app, app->active_sector, &min, &max);
		while (a->next != app->active_sector->wall_list && b->next != app->active_sector->wall_list)
		{
			if (a->next == b)
				a = b->next;
			else if (b->next == a)
				b = a->next;
			else
				b = b->next;
			fill_triangle(app, world_to_screen(app,app->active_sector->wall_list->point), world_to_screen(app, a->point), world_to_screen(app, b->point),color);
		}
	}
}


int	interaction_sector_check(t_app *app, t_sector_lst *sector)
{
	int	i;

	i = 0;
	while (i < MAX_INTERACTIONS)
	{	
		if(!app->interactions[i].activation_wall && app->interactions[i].activation_sector == sector)
			return (app->interactions[i].event_id);
		i++;
	}
	return (0);
}

int	interaction_wall_check(t_app *app, t_vec2_lst *wall)
{
	int	i;

	i = 0;
	while (i < MAX_INTERACTIONS)
	{	
		if(app->interactions[i].activation_sector && app->interactions[i].activation_wall == wall)
			return (app->interactions[i].event_id);
		i++;
	}
	return (0);
}

int	interaction_object_check(t_app *app, int id)
{
	int	i;

	i = 0;
	while (i < MAX_INTERACTIONS)
	{
		if(app->interactions[i].activation_object == &app->objects[id])
			return (app->interactions[i].event_id);
		i++;
	}
	return (0);
}