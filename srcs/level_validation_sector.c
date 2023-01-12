/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   level_validation_sector.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:45:06 by saaltone          #+#    #+#             */
/*   Updated: 2023/01/12 15:58:51 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * @brief Checks if all sector wall angles are convex.
 * 
 * @param app 
 * @param sector_id 
 * @return t_bool 
 */
static t_bool	is_convex(t_app *app, int sector_id)
{
	int		i;
	int		next;

	i = 0;
	while (i < app->sectors[sector_id].corner_count)
	{
		next = i + 1;
		if (i == app->sectors[sector_id].corner_count - 1)
			next = 0;
		if (ft_vector_angle_left(get_wall_vector(app, sector_id, i),
			get_wall_vector(app, sector_id, next)) < M_PI)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

/**
 * @brief Performs validation checks for sector data.
 * 
 * @param app 
 */
void	level_validation_sectors(t_app *app)
{
	int	i;

	i = 0;
	while (i < app->sector_count)
	{
		if (app->sectors[i].corner_count > MAX_SECTOR_CORNERS
			|| !is_convex(app, i))
			exit_error(MSG_ERROR_VALIDATION_SECTOR);
		i++;
	}
}
