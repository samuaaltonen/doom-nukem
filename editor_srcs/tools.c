/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 16:27:15 by htahvana          #+#    #+#             */
/*   Updated: 2023/02/20 18:32:18 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * @brief Finds and returns the wall in the sector that is furthest from the 
 * parallel line to selected point.
 * 
 * ft_vector_length(c) * (sin(ft_vector_angle(line, c))
 * c = vector to iterated point
 * 
 * @param sector
 * @param point
 * @return t_wall_list*
 */
t_wall_list	*find_opposite_point(t_sector_list *sector, t_wall_list *point)
{
	t_vector2	c;
	t_wall_list	*head;
	t_wall_list	*selection;
	double		opposite;
	double		max;

	selection = NULL;
	max = 0.0f;
	head = sector->wall_list;
	while (TRUE)
	{
		c = ft_vector2_sub(head->point, point->point);
		opposite = ft_vector_length(c) * sin(ft_vector_angle((t_vector2)
				{point->next->point.x - point->point.x, point->next->point.y
					- point->point.y}, c));
		if (opposite > max)
		{
			max = opposite;
			selection = head;
		}
		head = head->next;
		if (head == sector->wall_list)
			break ;
	}
	return (selection);
}

/**
 * @brief Returns the sector by index given.
 * 
 * @param app
 * @param index
 * @return t_sector_list*
*/
t_sector_list	*sector_by_index(t_app *app, int index)
{
	t_sector_list	*head;
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
 * @brief Finds which point in active sector was clicked.
 * 
 * @param app 
 * @return t_wall_list* 
 */
t_wall_list	*find_clicked_vector(t_app *app)
{
	t_wall_list		*found;
	t_point			mouse;
	t_vector2		mouse_pos;
	t_line			wall_line;

	SDL_GetMouseState(&mouse.x, &mouse.y);
	mouse_pos = screen_to_world(app, mouse);
	if (app->active_sector)
	{
		found = app->active_sector->wall_list;
		while (found)
		{
			wall_line = (t_line){found->point, found->next->point};
			if (ft_vector_compare(app->mouse_track, found->point)
				|| ft_point_on_segment_epsilon(wall_line, mouse_pos,
					0.025 * (app->view_size.x / 200)))
				return (found);
			if (found->next == app->active_sector->wall_list)
				break ;
			found = found->next;
		}
	}
	return (NULL);
}

/**
 * @brief Converts world coordinates to screen coordinates.
 * 
 * @param app
 * @param pos
 * @return t_point
*/
t_point	world_to_screen(t_app *app, t_vector2 pos)
{
	return ((t_point){(pos.x - app->view_start.x) * (app->surface->w)
		/ (app->view_end.x - app->view_start.x), (pos.y - app->view_start.y)
		* (app->surface->h) / (app->view_end.y - app->view_start.y)});
}

/**
 * @brief Converts screen coordinates to world coordinates.
 * 
 * @param app
 * @param pos
 * @return t_vector2
*/
t_vector2	screen_to_world(t_app *app, t_point pos)
{
	return ((t_vector2){app->view_start.x + (pos.x / (double)app->surface->w)
		* app->view_size.x, app->view_start.y
		+ (pos.y / (double)app->surface->h)
		* app->view_size.y});
}
