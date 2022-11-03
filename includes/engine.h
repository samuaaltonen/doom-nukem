/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 15:11:01 by dpalacio          #+#    #+#             */
/*   Updated: 2022/11/04 00:31:33 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENGINE_H
# define ENGINE_H

enum e_occlusion {
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

	t_vector2		floor_slope_start;
	t_vector2		floor_slope_end;
	double			floor_slope_height;
	double			floor_slope_length;

	t_vector2		ceiling_slope_start;
	t_vector2		ceiling_slope_end;
	double			ceiling_slope_height;
	double			ceiling_slope_length;

	t_vector3		floor_slope_position;
	t_vector2		floor_slope_angles;
	t_vector3		ceiling_slope_position;
	t_vector2		ceiling_slope_angles;
	int				stack_index;
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
	int			wall_type;
	int			parent_height;
	int			parent_wall_start;
	int			parent_wall_end;

	double		floor_horizon;
	double		floor_horizon_height_offset;
	double		floor_horizon_angle;
	t_bool		floor_horizon_is_ascending;

	double		floor_slope_height;

	double		ceiling_horizon;

	double		perpendicular_distance;

	double		parent_texture_offset_top;
	double		parent_texture_offset_bottom;
	double		slope_texture_offset_top;
	double		slope_texture_offset_bottom;
}	t_rayhit;

/**
 * Wall struct. Contains information of what sector it belongs to and which wall
 * of that sector it is and precalculated x positions in screen.
 */
typedef struct s_wall
{
	int				sector_id;
	int				wall_id;
	int				wall_type;
	t_bool			is_member;
	t_bool			is_portal;
	t_bool			is_inside;
	int				already_selected;
	t_line			line;
	int				start_x;
	int				end_x;
}	t_wall;

/**
 * Wallstack struct. Used when gathering possibly visible walls from sectors and
 * their ordering.
 */
typedef struct s_wallstack
{
	t_wall	walls[MAX_VISIBLE_SECTORS] \
			[(MAX_MEMBER_SECTORS + 1) * MAX_SECTOR_CORNERS];
	int		wall_count[MAX_VISIBLE_SECTORS + 1];
	int		visited[MAX_VISIBLE_SECTORS];
	int		visited_count;
	int		interesting[MAX_VISIBLE_SECTORS];
	int		interesting_count;
}	t_wallstack;

#endif
