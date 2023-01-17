/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   level_validation_player.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 18:22:00 by saaltone          #+#    #+#             */
/*   Updated: 2023/01/12 18:24:17 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * @brief Checks if player data is valid.
 * 
 * @param app 
 */
void	level_validation_player(t_app *app)
{
	if (app->player.sector < 0
		|| app->player.sector >= app->sector_count
		|| app->player.hp <= 0
		|| app->player.shield < 0
		|| !inside_sector(app, app->player.sector, app->player.pos))
		exit_error(MSG_ERROR_VALIDATION_PLAYER);
}
