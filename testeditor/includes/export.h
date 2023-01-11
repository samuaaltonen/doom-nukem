/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 12:48:41 by saaltone          #+#    #+#             */
/*   Updated: 2023/01/11 17:46:13 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPORT_H
# define EXPORT_H
# define MAX_BMP_OFFSET			32768
# define MAX_BMP_WIDTH			32768
# define MAX_BMP_HEIGHT			32768
# define MAX_ASSET_COUNT		32
# define MAX_UNCOMPRESS_BATCH	4096
# define MAX_COMPRESS_BATCH		6144
# define PANELS_PATH		"../assets/textures/spritesheet_full.bmp"
# define SKYBOX_PATH		"../assets/images/skybox.bmp"
# define FONT_PATH			"../assets/fonts/sci-fi_font.bmp"
# define UI_FRAME_PATH		"../assets/ui/ui_frame.bmp"
# define TITLESCREEN_PATH	"../assets/images/awakened3.bmp"
# define CROSSHAIR_PATH		"../assets/ui/crosshair.bmp"
# define POINTER_PATH		"../assets/ui/mouse_pointer.bmp"
# define SHIELD_PATH		"../assets/ui/shield.bmp"
# define HP_PATH			"../assets/ui/hp.bmp"
# define PISTOL_PATH		"../assets/textures/pistol.bmp"
# define BULLET_PATH		"../assets/textures/bullet.bmp"
# define METER_PATH			"../assets/ui/meter.bmp"
# define PICKUP_PATH		"../assets/images/Objects_small_sheet.bmp"
# define OBJECT_PATH		"../assets/images/Objects_Big_sheet.bmp"
# define OBJECT_ICON_PATH	"../assets/images/Objects_icons.bmp"
# define MONSTER_1_PATH		"../assets/images/Monster1_full_sheet.bmp"
# define MONSTER_2_PATH		"../assets/images/Monster2_full_sheet.bmp"
# define SPRITE_PATH		"../assets/images/Projectiles.bmp"
# define WEAPON_HD_PATH		"../assets/images/weapon_cannon4.bmp"
# define MUSIC_PATH			"../assets/sounds/title_music.wav"
# define SOUND_LASER_PATH	"../assets/sounds/laser.wav"
# define SOUND_SHOT_PATH	"../assets/sounds/pistol_shot.wav"
# define SOUND_RELOAD_PATH	"../assets/sounds/pistol_reload.wav"
# define SOUND_BUMP_PATH	"../assets/sounds/bump.wav"
# define TEXTS_PATH			"../assets/texts/texts.txt"
# define MAX_TEXT_LINES 16
# define MAX_TEXT_LINE_LENGTH 512

enum e_export_assets
{
	EXPORT_PANELS,
	EXPORT_SKYBOX,
	EXPORT_FONT,
	EXPORT_UI_FRAME,
	EXPORT_TITLESCREEN,
	EXPORT_CROSSHAIR,
	EXPORT_POINTER,
	EXPORT_SHIELD,
	EXPORT_HP,
	EXPORT_PISTOL,
	EXPORT_BULLET,
	EXPORT_METER,
	EXPORT_ICON,
	EXPORT_WEAPON_HD,
	EXPORT_PICKUP,
	EXPORT_OBJECT,
	EXPORT_MONSTER_1,
	EXPORT_MONSTER_2,
	EXPORT_SPRITE,
	EXPORT_MUSIC,
	EXPORT_SOUND_LASER,
	EXPORT_SOUND_SHOT,
	EXPORT_SOUND_RELOAD,
	EXPORT_SOUND_BUMP,
	EXPORT_TEXTS
};

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

typedef struct s_export_player
{
	t_vector2		position;
	t_vector2		direction;
	int				sector;
	int				health;
	int				weapons;
	int				armor;
	t_inventory		inventory;
}	t_export_player;

typedef struct s_export_object
{
	int			type;
	double		var;
	t_vector2	pos;
	double		elevation;
	int			sector;
}	t_export_object;

typedef struct	s_export_interaction
{
	int				event_id;
	double 			variable;
	double			editable;
	int				activation_sector;
	int				activation_wall;
	int				activation_object;
	int				target_sector;
}	t_export_interaction;

typedef struct	s_export_asset
{
	int	size;
	int	width;
	int	height;
}	t_export_asset;

typedef struct	s_level_header
{
	int				version;
	int				sector_count;
	int				object_count;
	int				interaction_count;
	t_export_asset	asset_info[MAX_ASSET_COUNT];
}	t_level_header;

/**
 * RLE compression
 */
void			expand_data(unsigned char **data, int *length, int *allocated);
unsigned char	*read_source(const char *source, int *source_length);
void			rle_uncompress_data(const char *source, unsigned char **data,
					int *length);
void			rle_compress(const char *source);
void			rle_uncompress(const char *source);

#endif