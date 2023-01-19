/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   level_validation_sector.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:45:06 by saaltone          #+#    #+#             */
/*   Updated: 2023/01/13 15:48:43 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * @brief Returns wall vector from sector by wall id.
 * 
 * @param app 
 * @param sector_id 
 * @param wall_id 
 * @return t_vector2 
 */
static t_vector2	get_wall_vector(t_export_sector *sector, int wall_id)
{
	if (sector->corner_count == wall_id + 1)
		return (ft_vector2_sub(sector->corners[0],
				sector->corners[wall_id]));
	return (ft_vector2_sub(sector->corners[wall_id + 1],
			sector->corners[wall_id]));
}

/**
 * @brief Checks if all sector wall angles are convex.
 * 
 * @param app 
 * @param sector_id 
 * @return t_bool 
 */
static t_bool	is_convex(t_export_sector *sector)
{
	int	i;
	int	next;

	i = 0;
	while (i < sector->corner_count)
	{
		next = i + 1;
		if (i == sector->corner_count - 1)
			next = 0;
		if (ft_vector_angle_left(get_wall_vector(sector, i),
				get_wall_vector(sector, next)) < M_PI)
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
static t_bool	valid_textures(t_export_sector *sector)
{
	int	i;

	i = 0;
	while (i < sector->corner_count)
	{
		if (sector->wall_textures[i] < 0
			|| sector->wall_textures[i] >= MAX_TEX_COUNT
			|| sector->wall_decor[i] < -1
			|| sector->wall_decor[i] >= MAX_DECOR_COUNT)
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
static t_bool	valid_linked_sectors(t_app *app, t_export_sector *sector)
{
	int	i;

	i = 0;
	while (i < MAX_MEMBER_SECTORS)
	{
		if (sector->member_sectors[i] < -1
			|| sector->member_sectors[i] >= app->sector_count)
			return (FALSE);
		i++;
	}
	i = 0;
	while (i < sector->corner_count)
	{
		if (sector->wall_types[i] < -1
			|| sector->wall_types[i] >= app->sector_count)
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
void	level_validation_sector(t_app *app, t_export_sector *sector)
{
	if (sector->corner_count > MAX_SECTOR_CORNERS
		|| !is_convex(sector)
		|| !valid_textures(sector)
		|| sector->parent_sector >= app->sector_count
		|| sector->parent_sector < -1
		|| !valid_linked_sectors(app, sector))
		exit_error(MSG_ERROR_IMPORT_OBJECT);
}
