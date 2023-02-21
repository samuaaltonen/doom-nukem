/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 16:18:36 by htahvana          #+#    #+#             */
/*   Updated: 2023/02/21 15:01:58 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * @brief Finds matching wall.
 * 
 * @param app 
 * @param wall 
 * @param origin 
 * @return int 
 */
int	find_wall_match(t_app *app, t_wall_list *wall, t_sector_list *origin)
{
	int				i;
	t_sector_list	*target_sector;
	t_wall_list		*target_wall;

	target_sector = sector_by_index(app, wall->type);
	if (!target_sector)
		return (FALSE);
	i = -1;
	target_wall = target_sector->wall_list;
	while (++i < target_sector->corner_count + 1)
	{
		if (ft_cmp_line_points((t_line){wall->point, wall->next->point},
			(t_line){target_wall->point, target_wall->next->point})
				&& target_wall->type == get_sector_id(app, origin))
			return (TRUE);
		target_wall = target_wall->next;
	}
	return (FALSE);
}

/**
 * @brief Renders all the lines for the given sector.
 * 
 * @param app 
 * @param sector_start 
 */
void	render_sector(t_app *app, t_wall_list *wall_start,
	t_sector_list *sector)
{
	t_wall_list	*tmp;

	tmp = wall_start;
	while (tmp->next != NULL)
	{
		if (tmp->type > -1)
		{
			if (find_wall_match(app, tmp, sector))
				draw_list_lines(app, tmp, tmp->next, PORTAL_LINK);
			else
				draw_list_lines(app, tmp, tmp->next, PORTAL);
		}
		else
			draw_list_lines(app, tmp, tmp->next, 0xEEEEEE);
		if (interaction_wall_check(app, tmp))
			render_decor(app, tmp, INTERACTION);
		else
			render_decor(app, tmp, 0xEEEEEE);
		if (tmp->next == wall_start)
			break ;
		tmp = tmp->next;
	}
}

/**
 * @brief Runs render sector on all the sectors in app.
 * 
 * @param app
 */
void	render_sectors(t_app *app)
{
	t_sector_list	*tmp;

	tmp = app->sectors;
	while (tmp)
	{
		render_sector(app, tmp->wall_list, tmp);
		tmp = tmp->next;
	}
}

/**
 * @brief Renders points on each corner of the active sector.
 * 
 * @param app 
 */
void	render_sector_points(t_app *app)
{
	t_wall_list	*head;

	if (app->active_sector)
	{
		head = app->active_sector->wall_list;
		while (head)
		{
			render_point(app, head->point, 2, POINT);
			head = head->next;
			if (head == app->active_sector->wall_list)
				break ;
		}
	}
}

/**
 * @brief Renders a square with given size on the given point.
 * 
 * @param app 
 * @param point 
 * @param size 
 * @param color
 */
void	render_point(t_app *app, t_vector2 point, int size, int color)
{
	t_point		min;
	t_point		max;

	min = world_to_screen(app, point);
	max.x = min.x + size;
	max.y = min.y + size;
	min.y = min.y - size;
	while (min.y < max.y)
	{
		min.x = max.x - size * 2;
		while (min.x < max.x)
		{
			put_pixel_to_surface(app->surface, min.x, min.y, color);
			min.x++;
		}
		min.y++;
	}
}
