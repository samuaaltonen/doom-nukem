/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 14:38:52 by dpalacio          #+#    #+#             */
/*   Updated: 2023/01/23 15:37:07 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASSETS_H
# define ASSETS_H
# define IMAGE_PIXEL_BYTES			4
# define IMAGE_PIXEL_BITS			32
# define TEX_SIZE					128
# define TEX_PICKUP					44
# define TEX_OBJECT					128
# define SKYBOX_W					1536
# define SKYBOX_H					1088
# define FONT_W						416
# define FONT_H						64
# define UI_FRAME_W					30
# define UI_FRAME_H					30
# define TITLE_SCREEN_W				1280
# define TITLE_SCREEN_H				720
# define CROSSHAIR_W				16
# define CROSSHAIR_H				16
# define POINTER_W					22
# define POINTER_H					22
# define SHIELD_W					32
# define SHIELD_H					32
# define HEALTH_W					32
# define HEALTH_H					32
# define PISTOL_W					64
# define PISTOL_H					64
# define BULLET_W					4
# define BULLET_H					10
# define METER_W					16
# define METER_H					32
# define OBJECT_ICON_W				128
# define OBJECT_ICON_H				2688
# define WEAPON_W					256
# define WEAPON_H					256
# define OBJECT_SMALL_W				3960
# define OBJECT_SMALL_H				308
# define OBJECT_BIG_W				11520
# define OBJECT_BIG_H				896
# define PROJECTILE_W				44
# define PROJECTILE_H				352
# define ENEMY_1_W					11520
# define ENEMY_1_H					1024
# define ENEMY_2_W					11520
# define ENEMY_2_H					1536
# define ENEMY_3_W					11520
# define ENEMY_3_H					640
# define MAX_TEX_COUNT				79
# define MAX_DECOR_COUNT			21
# define MAX_BMP_OFFSET				32768
# define MAX_BMP_WIDTH				32768
# define MAX_BMP_HEIGHT				32768
# define MAX_WAV_SIZE				67108864
# define MAX_ASSET_COUNT			32
# define MAX_UNCOMPRESS_BATCH		4096
# define MAX_COMPRESS_BATCH			6144
# define MIN_UNCOMPRESS_UPDATE		256
# define DEFAULT_AUDIO_CHANNELS		1
# define DEFAULT_AUDIO_FORMAT		AUDIO_S16LSB
# define DEFAULT_AUDIO_FREQUENCEY	24000
# define DEFAULT_AUDIO_SAMPLES		4096
# define PROGRESS_BAR_FRAME_COLOR	0xff0099f2
# define PROGRESS_BAR_COLOR			0xff00def2
# define MAP_PATH			"./test.test"
# define MAX_SPRITES 6

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
	EXPORT_SPRITE,
	EXPORT_MONSTER_1,
	EXPORT_MONSTER_2,
	EXPORT_MONSTER_3,
	EXPORT_MUSIC,
	EXPORT_SOUND_LASER,
	EXPORT_SOUND_SHOT,
	EXPORT_SOUND_RELOAD,
	EXPORT_SOUND_BUMP,
	EXPORT_TEXTS
};

enum e_spritesheet {
	SMALL_SPRITE,
	BIG_SPRITE,
	PROJECTILE_SPRITE,
	ENEMY_SPRITE_1,
	ENEMY_SPRITE_2,
	ENEMY_SPRITE_3
};
/**
 * Struct for font. 
 */
typedef struct s_font
{
	SDL_Surface		*font;
	int				size;
}	t_font;

/**
 * Struct for all assets.
 */
typedef struct s_assets
{
	t_font			font;
	SDL_Surface		*ui_frame;
	SDL_Surface		*ui_frame_bg;
	SDL_Surface		*text_prompt;
	SDL_Surface		*button_idle;
	SDL_Surface		*button_select;
	SDL_Surface		*button_press;
	SDL_Surface		*title_screen_image;
	SDL_Surface		*crosshair;
	SDL_Surface		*pointer;
	SDL_Surface		*shield;
	SDL_Surface		*hp;
	SDL_Surface		*pistol;
	SDL_Surface		*bullet;
	SDL_Surface		*meter;
	SDL_Surface		*object_icon;
	SDL_Surface		*panels;
	SDL_Surface		*weapon;
	SDL_Surface		*skybox;
	SDL_Surface		*sprites[MAX_SPRITES];
}	t_assets;

#endif
