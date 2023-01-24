/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 15:11:01 by dpalacio          #+#    #+#             */
/*   Updated: 2023/01/24 13:59:28 by htahvana         ###   ########.fr       */
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

enum e_objects {
	EMPTY,
	ARMOR_PICKUP,
	COIN_PICKUP,
	AMMO_PICKUP,
	HP_PICKUP,
	JETPACK_PICKUP,
	WEAPON1,
	WEAPON2,
	BIG1,
	BIG2,
	BIG3,
	BIG4,
	BIG5,
	BIG6,
	BIG7,
	MONSTER1,
	MONSTER2,
	MONSTER3,
};

typedef struct s_export_asset
{
	int				size;
	int				width;
	int				height;
}	t_export_asset;

typedef struct s_level_header
{
	int				gravity;
	int				sector_count;
	int				object_count;
	int				interaction_count;
	t_export_asset	asset_info[MAX_ASSET_COUNT];
}	t_level_header;

typedef struct s_import_info
{
	t_thread_data	*thread;
	t_level_header	header;
	unsigned char	*data;
	int				length;
	int				imported;
	int				compressed_length;
	int				uncompressed;
}	t_import_info;

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
	int				wall_decor[MAX_SECTOR_CORNERS];
	t_vector2		decor_offset[MAX_SECTOR_CORNERS];
	double			light;
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

typedef struct s_export_sector
{
	int				corner_count;
	t_vector2		corners[MAX_SECTOR_CORNERS];
	int				wall_types[MAX_SECTOR_CORNERS];
	int				wall_textures[MAX_SECTOR_CORNERS];
	int				member_sectors[MAX_MEMBER_SECTORS];
	int				wall_decor[MAX_SECTOR_CORNERS];
	t_vector2		decor_offset[MAX_SECTOR_CORNERS];
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
}	t_export_sector;

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
	int				already_passed[THREAD_COUNT];
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
	t_sector		*sector;
	t_wall			*wall;
	int				wall_id;
	t_vector2		ray;
	int				texture;
	t_vector2		position;
	double			distance;
	double			distortion;
	double			texture_offset;
	double			texture_step;
	int				height;
	int				light;

	double			wall_start_actual;
	int				wall_start;
	int				wall_end;
	int				wall_type;

	double			parent_wall_start_actual;
	int				parent_wall_start;
	int				parent_wall_end;
	int				parent_height;

	double			floor_horizon;
	double			floor_horizon_angle;
	double			floor_slope_height;

	double			ceil_horizon;
	double			ceil_horizon_angle;
	double			ceil_slope_height;

	int				*occlusion_top;
	int				*occlusion_bottom;

	t_bool			has_decor;
	int				decor_texture;
	int				decor_start;
	double			decor_start_actual;
	int				decor_end;
	double			decor_texture_offset;
}	t_rayhit;

/**
 * Struct that contains necessary information for starting the raycast for a
 * specific wall.
 */
typedef struct s_raycast_info
{
	t_wall			*wall;
	t_limit			limit;
	int				*occlusion_top;
	int				*occlusion_bottom;
}	t_raycast_info;

/**
 * Wallstack struct. Used when gathering possibly visible walls from sectors and
 * their ordering.
 */
typedef struct s_wallstack
{
	t_wall			walls[MAX_VISIBLE_SECTORS] \
						[(MAX_MEMBER_SECTORS + 1) * MAX_SECTOR_CORNERS + 1];
	int				wall_count[MAX_VISIBLE_SECTORS + 1];
	int				visited[MAX_VISIBLE_SECTORS];
	int				visited_count;
	int				interesting[MAX_VISIBLE_SECTORS];
	int				interesting_count;
}	t_wallstack;

typedef struct s_object
{
	int				type;
	double			var;
	t_vector2		position;
	double			elevation;
	int				sector;
}	t_object;

typedef struct s_gameobject
{
	int				type;
	double			var;
	t_vector2		position;
	double			rot;
	double			elevation;
	int				sector;
}	t_gameobject;

/**
 * Struct that contains skybox drawing information. These values are updated
 * based on player movement.
 */
typedef struct s_sky
{
	t_point			start;
	t_point			size;
	t_vector2		pixel_step;
}	t_sky;

#endif
