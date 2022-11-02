/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 11:00:45 by ssulkuma          #+#    #+#             */
/*   Updated: 2022/11/02 14:07:41 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * Draws the player square to the correct position.
*/
static void	draw_player_square(t_app *app, t_point world_pos)
{
	int			x;
	int			y;

	y = 0;
	while (y < 10)
	{
		x = 0;
		while (x < 10)
		{
			put_pixel_to_surface(app->surface, (world_pos.x - 5) + x,
				(world_pos.y - 5) + y, PLAYER);
			x++;
		}
		y++;
	}
}

/**
 * Renders a square to player position. If player edit mode is on
 * the position follows the mouse, otherwise it's the last clicked position.
*/
void	render_player(t_app *app)
{
	t_point		world_pos;
	t_vector2	point;

	if (app->player_edit && !app->list_creation && !app->active_sector)
		point = app->mouse_track;
	else
		point = app->mouse_click;
	world_pos.x = (point.x - app->view_pos.x) * (app->surface->w)
		/ (app->view_size.x - app->view_pos.x);
	world_pos.y = (point.y - app->view_pos.y) * (app->surface->h)
		/ (app->view_size.y - app->view_pos.y);
	draw_player_square(app, world_pos);
	if (!app->player_edit)
	{
		app->player.position.x = point.x;
		app->player.position.y = point.y;
		app->player.direction.x = 0;
		app->player.direction.y = 0;
	}
}
