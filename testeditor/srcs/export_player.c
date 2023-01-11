/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 20:07:56 by saaltone          #+#    #+#             */
/*   Updated: 2023/01/11 20:19:07 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * @brief Returns player weapon data stacked to int.
 * 
 * @param app 
 * @param weapons 
 * @return int 
 */
static int as_bits(t_app *app)
{
	int	inventory;
	int	i;

	inventory = 0;
	i = 0;
	while (i < MAX_WEAPONS)
	{
		if (i == app->player.selected_weapon)
			inventory |= 1 << i;
		i++;
	}
	return (inventory);
}

/**
 * @brief Exports player data.
 * 
 * @param app 
 * @param fd 
 */
void	export_player(t_app *app, int fd)
{
	t_export_player	export;

	ft_bzero(&export, sizeof(t_export_player));
	export.position = app->player.position;
	export.direction = app->player.direction;
	export.sector = get_sector_id(app,app->player.sector);
	export.health = app->player.health;
	export.weapons = as_bits(app);
	export.armor = app->player.armor;
	export.inventory = app->player.inventory;
 	if (write(fd, &export, sizeof(t_export_player)) == -1)
		exit_error(MSG_ERROR_FILE_WRITE);
}
