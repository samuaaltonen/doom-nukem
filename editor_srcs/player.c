/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 11:00:45 by ssulkuma          #+#    #+#             */
/*   Updated: 2023/02/01 17:23:43 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * @brief Checks that the player position cannot be placed on sector corners.
 * 
 * @param app
 * @param mouse
 * @return t_bool
*/
static t_bool	check_sector_corners(t_app *app, t_vector2 *mouse)
{
	t_vec2_lst	*tmp;

	tmp = app->active_sector->wall_list;
	while (tmp)
	{
		if (mouse->x == tmp->point.x && mouse->y == tmp->point.y)
			return (FALSE);
		tmp = tmp->next;
		if (tmp == app->active_sector->wall_list)
			break ;
	}
	return (TRUE);
}

/**
 * @brief Checks if the player position is being placed outside sectors or
 * inside member sectors. Disallows placing if position not valid.
 * 
 * @param app
*/
void	check_player_position(t_app *app)
{
	int			id;

	if (!app->player.sector || app->active_sector->parent_sector
		|| !app->sectors || !check_sector_corners(app, &app->player.position)
		|| !inside_sector_check(app->active_sector, &app->mouse_track))
	{
		app->player.sector = NULL;
		app->player_edit = TRUE;
		return ;
	}
	id = -1;
	while (++id < MAX_MEMBER_SECTORS && app->player.sector->member_sectors[id])
	{
		if (inside_sector_check(app->player.sector->member_sectors[id],
				&app->mouse_track))
		{
			app->player.sector = NULL;
			app->player_edit = TRUE;
			return ;
		}
	}
}

/**
 * @brief Renders a square to player position. If player edit mode is on
 * the position follows the mouse, otherwise it's the last clicked position.
 * 
 * @param app
*/
void	render_player(t_app *app)
{
	t_vector2	point;
	int			size;

	size = 6 / app->zoom_range;
	if (!app->player_edit && app->player.sector)
		point = app->player.position;
	else
		point = app->mouse_track;
	if (!app->list_creation
		|| (app->list_creation && app->player.sector && !app->player_edit))
		render_point(app, point, 4 * size, PLAYER);
}
