/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <danielmdc94@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 15:11:01 by dpalacio          #+#    #+#             */
/*   Updated: 2022/10/19 15:47:33 by dpalacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENGINE_H
# define ENGINE_H

# include "doomnukem.h"

/**
 * Sectors
 */
typedef struct s_sector
{
	t_vector2		corners[MAX_SECTOR_CORNERS];
	int				wall_types[MAX_SECTOR_CORNERS];
	int				wall_textures[MAX_SECTOR_CORNERS];
	int				member_sectors[MAX_MEMBER_SECTORS];
	int				parent_sector;
	int				corner_count;
	double			floor_height;
	double			ceiling_height;
	int				floor_texture;
	int				ceiling_texture;
	t_vector3		floor_slope_position;
	t_vector2		floor_slope_angles;
	t_vector3		ceiling_slope_position;
	t_vector2		ceiling_slope_angles;
}	t_sector;

typedef struct s_exportsector
{
	t_vector2		corners[MAX_SECTOR_CORNERS];
	int				wall_types[MAX_SECTOR_CORNERS];
	int				wall_textures[MAX_SECTOR_CORNERS];
	int				member_sectors[MAX_MEMBER_SECTORS];
	int				corner_count;
	double			floor_height;
	double			ceiling_height;
	int				floor_texture;
	int				ceiling_texture;
	double			floor_slope_height;
	int				floor_slope_position;
	int				floor_slope_opposite;
	double			ceiling_slope_height;
	int				ceiling_slope_position;
	int				ceiling_slope_opposite;
}	t_exportsector;

/**
 * Rayhit struct.
*/
typedef struct s_rayhit
{
	t_sector	*sector;
	int			texture;
	t_vector2	position;
	double		distance;
	t_vector2	texture_offset;
	t_vector2	texture_step;
	int			height;
	int			wall_start;
	int			wall_end;
}	t_rayhit;

/**
 * Wall struct. Contains information of what sector it belongs to and which wall
 * of that sector it is.
 */
typedef struct s_wall
{
	int				sector_id;
	int				wall_id;
	t_bool			is_member;
	int				already_selected;
	t_vertex2		vertex;
	int				start_x;
	int				end_x;
}	t_wall;

#endif
