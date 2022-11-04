/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 11:00:45 by ssulkuma          #+#    #+#             */
/*   Updated: 2022/11/03 16:19:25 by ssulkuma         ###   ########.fr       */
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
 * Checks if the player position is being placed outside sectors or
 * inside member sectors. Disallows placing if position not valid.
*/
static void	check_player_position(t_app *app, t_vector2 *point)
{
	// int				id;
	// t_sector_lst	*temp;

	if (app->player.sector == -1)
	{
		point = &app->mouse_track;
		app->player_edit = TRUE;
		return ;
	}
	// id = 0;
	// temp = app->sectors;
	// while (id < app->player.sector)
	// {
	// 	temp = temp->next;
	// 	id++;
	// }
	// while (id < MAX_MEMBER_SECTORS && temp->member_sectors[id])
	// {
	// 	if (inside_sector_check(app, temp->member_sectors[id]))
	// 	{
	// 		point = &app->mouse_track;
	// 		app->player_edit = TRUE;
	// 	}
	// 	id++;
	// }
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
	check_player_position(app, &point);
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
		app->player.direction.y = 1;
	}
}
