/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 15:11:01 by dpalacio          #+#    #+#             */
/*   Updated: 2022/11/24 13:16:38 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENGINE_H
# define ENGINE_H

enum e_occlusion {
	OCCLUDE_TOP,
	OCCLUDE_BOTTOM,
	OCCLUDE_BOTH,
	OCCLUDE_NONE
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
	int				floor_texture;
	double			floor_tex_offset;
	double			ceil_height;
	int				ceil_texture;
	double			ceil_tex_offset;

	t_vector2		floor_slope_start;
	t_vector2		floor_slope_end;
	double			floor_slope_height;
	double			floor_slope_magnitude;

	t_vector2		ceil_slope_start;
	t_vector2		ceil_slope_end;
	double			ceil_slope_height;
	double			ceil_slope_magnitude;

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
	int			light;

	int			wall_start_actual;
	int			wall_start;
	int			wall_end;
	int			wall_type;

	int			parent_height;
	int			parent_wall_start_actual;
	int			parent_wall_start;
	int			parent_wall_end;

	double		floor_horizon;
	double		floor_horizon_angle;
	double		floor_slope_height;

	double		ceil_horizon;
	double		ceil_horizon_angle;
	double		ceil_slope_height;

	int			*occlusion_top;
	int			*occlusion_bottom;
}	t_rayhit;

/**
 * Struct that contains necessary information for starting the raycast for a
 * specific wall.
 */
typedef struct s_raycast_info
{
	t_wall	*wall;
	t_limit	limit;
	int		*occlusion_top;
	int		*occlusion_bottom;
}	t_raycast_info;

/**
 * Wallstack struct. Used when gathering possibly visible walls from sectors and
 * their ordering.
 */
typedef struct s_wallstack
{
	t_wall	walls[MAX_VISIBLE_SECTORS] \
			[(MAX_MEMBER_SECTORS + 1) * MAX_SECTOR_CORNERS + 1];
	int		wall_count[MAX_VISIBLE_SECTORS + 1];
	int		visited[MAX_VISIBLE_SECTORS];
	int		visited_count;
	int		interesting[MAX_VISIBLE_SECTORS];
	int		interesting_count;
}	t_wallstack;

/**
 * Struct that contains skybox drawing information. These values are updated
 * based on player movement.
 */
typedef struct s_sky
{
	t_point		start;
	t_point		size;
	t_vector2	pixel_step;
}	t_sky;

typedef struct s_buffer_unit
{
	int		x;
	int		y;
	int		color;
	float	depth;
}	t_buffer_unit;

#endif
