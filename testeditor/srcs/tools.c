/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 16:27:15 by htahvana          #+#    #+#             */
/*   Updated: 2023/01/13 16:19:37 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

//check if list is convex, line_side from every point to every other point

/**
 * Finds and returns the wall in the sector that is furthest from the 
 * parallel line to selected point
 * 
 * ft_vector_length(c) * (sin(ft_vector_angle(line, c))
 * c = vector to iterated point
 */
t_vec2_lst	*find_opposite_point(t_sector_lst *sector, t_vec2_lst *point)
{
	t_vector2	c;
	t_vec2_lst	*head;
	t_vec2_lst	*selection;
	double		opposite;
	double		max;

	selection = NULL;
	max = 0.0f;
	head = sector->wall_list;
	while (head->next != sector->wall_list)
	{
		c = (t_vector2){head->point.x - point->point.x,
			head->point.y - point->point.y};
		opposite = ft_vector_length(c) * sin(ft_vector_angle((t_vector2)
				{point->next->point.x - point->point.x, point->next->point.y
					- point->point.y}, c));
		if (opposite > max)
		{
			max = opposite;
			selection = head;
		}
		head = head->next;
	}
	return (selection);
}

t_sector_lst	*sector_by_index(t_app *app, int index)
{
	t_sector_lst	*head;
	int				i;

	i = 0;
	head = app->sectors;
	if (index == -1)
		return (NULL);
	while (head && i != index && i < MAX_SEARCH_COUNT)
	{
		head = head->next;
		i++;
	}
	if (i == MAX_SEARCH_COUNT)
		exit_error(MSG_ERROR_LEVEL_DATA);
	return (head);
}

/**
 * @brief Finds which point in active sector was clicked
 * 
 * @param app 
 * @return t_vec2_lst* 
 */
t_vec2_lst	*find_clicked_vector(t_app *app)
{
	t_vec2_lst		*found;

	if (app->active_sector)
	{
		found = app->active_sector->wall_list;
		while (found)
		{
			if (app->mouse_track.x == found->point.x
				&& app->mouse_track.y == found->point.y)
				return (found);
			if (found->next == app->active_sector->wall_list)
				break ;
			found = found->next;
		}
	}
	return (NULL);
}

/**
 * Converts world coordinates to screen coordinates.
*/
t_point	world_to_screen(t_app *app, t_vector2 pos)
{
	return ((t_point){(pos.x - app->view_pos.x) * (app->surface->w)
		/ (app->view_size.x - app->view_pos.x), (pos.y - app->view_pos.y)
		* (app->surface->h) / (app->view_size.y - app->view_pos.y)});
}

/**
 * Converts screen coordinates to world coordinates.
*/
t_vector2	screen_to_world(t_app *app, t_point pos)
{
	return ((t_vector2){app->view_pos.x + (pos.x / (double)app->surface->w)
		* app->zoom_area.x, app->view_pos.y + (pos.y / (double)app->surface->h)
		* app->zoom_area.y});
}
