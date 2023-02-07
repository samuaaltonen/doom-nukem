/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_extra.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 13:55:36 by htahvana          #+#    #+#             */
/*   Updated: 2023/02/07 18:30:38 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * @brief Renders decor circle on a wall line.
 * 
 * @param app 
 * @param wall 
 * @param color 
 */
void	render_decor(t_app *app, t_wall_list *wall, int color)
{
	t_vector2	wall_vector;

	if (wall && wall->decor >= 0)
	{
		wall_vector = ft_vector2_sub(wall->next->point, wall->point);
		wall_vector = ft_vector2_add(wall->point, ft_vector_resize(wall_vector,
					(ft_vector_length(wall_vector) / 2)
					+ wall->decor_offset.x));
		draw_circle(app, world_to_screen(app, wall_vector), 5, color);
	}
}
