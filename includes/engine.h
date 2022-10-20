/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 15:11:01 by dpalacio          #+#    #+#             */
/*   Updated: 2022/10/21 01:48:07 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENGINE_H
# define ENGINE_H

# include "doomnukem.h"

enum s_occlusion {
	OCCLUDE_TOP,
	OCCLUDE_BOTTOM,
	OCCLUDE_BOTH
};

/**
 * Sectors
 */
typedef struct s_sector
{
	int				corner_count;
	t_vector2		corners[MAX_SECTOR_CORNERS];
	int				wall_types[MAX_SECTOR_CORNERS];
	int				wall_textures[MAX_SECTOR_CORNERS];
	int				member_sectors[MAX_MEMBER_SECTORS];
	int				parent_sector;
	int				light;
	double			floor_height;
	double			ceiling_height;
	int				floor_texture;
	double			floor_tex_offset;
	int				ceiling_texture;
	double			ceil_tex_offset;
	t_vector3		floor_slope_position;
	t_vector2		floor_slope_angles;
	t_vector3		ceiling_slope_position;
	t_vector2		ceiling_slope_angles;
}	t_sector;

typedef struct s_exportsector
{
	int				corner_count;
	t_vector2		corners[MAX_SECTOR_CORNERS];
	int				wall_types[MAX_SECTOR_CORNERS];
	int				wall_textures[MAX_SECTOR_CORNERS];
	int				member_sectors[MAX_MEMBER_SECTORS];
	int				parent_sector;
	int				light;
	double			floor_height;
	double			ceil_height;
	int				floor_tex;
	int				floor_tex_offset;
	int				ceil_tex;
	int				ceil_tex_offset;
	double			floor_slope_height;
	int				floor_slope_position;
	int				floor_slope_opposite;
	double			ceil_slope_height;
	int				ceil_slope_position;
	int				ceil_slope_opposite;
}	t_exportsector;

/**
 * Rayhit struct.
*/
typedef struct s_rayhit
{
	t_sector	*sector;
	t_vector2	ray;
	int			texture;
	t_vector2	position;
	double		distance;
	double		distortion;
	t_vector2	texture_offset;
	t_vector2	texture_step;
	int			height;
	int			wall_start;
	int			wall_end;
	int			parent_height;
	int			parent_wall_start;
	int			parent_wall_end;
	double		parent_texture_offset_top;
	double		parent_texture_offset_bottom;
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
	t_bool			is_portal;
	int				already_selected;
	t_vertex2		vertex;
	int				start_x;
	int				end_x;
}	t_wall;

#endif
