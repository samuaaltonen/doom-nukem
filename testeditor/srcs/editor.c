/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 13:03:35 by htahvana          #+#    #+#             */
/*   Updated: 2023/01/02 16:18:19 by ssulkuma         ###   ########.fr       */
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
		if (tmp->point.x == app->mouse_track.x
			&& tmp->point.y == app->mouse_track.y)
			return (FALSE);
		if (tmp->next && ft_line_side((t_line)
				{tmp->point, tmp->next->point}, app->mouse_track))
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
	double	increment;

	increment = HEIGHT_INC;
	if (app->keystates & SHIFT_DOWN)
		increment = app->divider;
	if (key == SDLK_UP)
		edit_up_key_changes(app, increment);
	else if (key == SDLK_DOWN)
		edit_down_key_changes(app, increment);
	else if (key == SDLK_LEFT)
		edit_left_key_changes(app, key);
	else if (key == SDLK_RIGHT)
		edit_right_key_changes(app, key);
}
