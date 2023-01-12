/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 14:38:52 by dpalacio          #+#    #+#             */
/*   Updated: 2023/01/12 16:09:03 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASSETS_H
# define ASSETS_H
# define MAX_BMP_OFFSET				32768
# define MAX_BMP_WIDTH				32768
# define MAX_BMP_HEIGHT				32768
# define MAX_ASSET_COUNT			32
# define MAX_UNCOMPRESS_BATCH		4096
# define MAX_COMPRESS_BATCH			6144
# define DEFAULT_AUDIO_CHANNELS		1
# define DEFAULT_AUDIO_FORMAT		AUDIO_S16LSB
# define DEFAULT_AUDIO_FREQUENCEY	24000
# define DEFAULT_AUDIO_SAMPLES		4096
# define PROGRESS_BAR_FRAME_COLOR	0xff0099f2
# define PROGRESS_BAR_COLOR			0xff00def2
# define MAP_PATH			"./testeditor/test.test"
# define MAX_SPRITES 5

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

enum e_spritesheet {
	SMALL_SPRITE,
	BIG_SPRITE,
	PROJECTILE_SPRITE,
	ENEMY_SPRITE_1,
	ENEMY_SPRITE_2,
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
	SDL_Surface		*bg;
	SDL_Surface		*sprites[MAX_SPRITES];
}	t_assets;

#endif
