/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 11:00:45 by ssulkuma          #+#    #+#             */
/*   Updated: 2022/11/24 15:56:42 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * Checks if the player position is being placed outside sectors or
 * inside member sectors. Disallows placing if position not valid.
*/
void	check_player_position(t_app *app)
{
	int				id;

	if (!app->sectors || !app->player.sector)
	{
		app->player_edit = TRUE;
		return ;
	}
	id = -1;
	while (++id < MAX_MEMBER_SECTORS && app->player.sector->member_sectors[id])
	{
		if (inside_sector_check(app->player.sector->member_sectors[id], &app->mouse_track))
		{
			app->player.sector = NULL;
			app->player_edit = TRUE;
			return ;
		}
	}
}

/**
 * Renders a square to player position. If player edit mode is on
 * the position follows the mouse, otherwise it's the last clicked position.
*/
void	render_player(t_app *app)
{
	t_vector2	point;

	if(!app->player_edit && app->player.sector)
		point = app->player.position;
	else
		point = app->mouse_track;
	render_point(app, point,10, PLAYER);
}
