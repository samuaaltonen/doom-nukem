/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   level_validation_sector.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:45:06 by saaltone          #+#    #+#             */
/*   Updated: 2023/01/12 16:45:16 by saaltone         ###   ########.fr       */
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
	int	i;
	int	next;

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
 * @brief Checks if texture IDs are valid.
 * 
 * @param app 
 * @param sector_id 
 * @return t_bool 
 */
static t_bool	valid_textures(t_app *app, int sector_id)
{
	int	i;

	i = 0;
	while (i < app->sectors[sector_id].corner_count)
	{
		if (app->sectors[sector_id].wall_textures[i] < 0
			|| app->sectors[sector_id].wall_textures[i] >= MAX_TEX_COUNT
			|| app->sectors[sector_id].wall_decor[i] < -1
			|| app->sectors[sector_id].wall_decor[i] >= MAX_DECOR_COUNT)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

/**
 * @brief Check if member sectors and portal sectors have valid IDs.
 * 
 * @param app 
 * @param sector_id 
 * @return t_bool 
 */
static t_bool	valid_linked_sectors(t_app *app, int sector_id)
{
	int	i;

	i = 0;
	while (i < MAX_MEMBER_SECTORS)
	{
		if (app->sectors[sector_id].member_sectors[i] < -1
			|| app->sectors[sector_id].member_sectors[i] >= app->sector_count)
			return (FALSE);
		i++;
	}
	i = 0;
	while (i < app->sectors[sector_id].corner_count)
	{
		if (app->sectors[sector_id].wall_types[i] < -1
			|| app->sectors[sector_id].wall_types[i] >= app->sector_count)
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
			|| !is_convex(app, i)
			|| !valid_textures(app, i)
			|| app->sectors[i].parent_sector >= app->sector_count
			|| app->sectors[i].parent_sector < -1
			|| !valid_linked_sectors(app, i))
			exit_error(MSG_ERROR_VALIDATION_SECTOR);
		i++;
	}
}
