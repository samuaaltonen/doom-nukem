/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 14:38:52 by dpalacio          #+#    #+#             */
/*   Updated: 2023/01/09 17:49:18 by saaltone         ###   ########.fr       */
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
# define PANELS_PATH		"assets/textures/spritesheet_full.bmp"
# define SKYBOX_PATH		"assets/images/skybox.bmp"
# define FONT_PATH			"assets/fonts/sci-fi_font.bmp"
# define UI_FRAME_PATH		"assets/ui/ui_frame.bmp"
# define TITLESCREEN_PATH	"assets/images/awakened3.bmp"
# define CROSSHAIR_PATH		"assets/ui/crosshair.bmp"
# define POINTER_PATH		"assets/ui/mouse_pointer.bmp"
# define SHIELD_PATH		"assets/ui/shield.bmp"
# define HP_PATH			"assets/ui/hp.bmp"
# define PISTOL_PATH		"assets/textures/pistol.bmp"
# define BULLET_PATH		"assets/textures/bullet.bmp"
# define METER_PATH			"assets/ui/meter.bmp"
# define PICKUP_PATH		"assets/images/Objects_small_sheet.bmp"
# define OBJECT_PATH		"assets/images/Objects_Big_sheet.bmp"
# define MONSTER_1_PATH		"assets/images/Monster1_full_sheet.bmp"
# define MONSTER_2_PATH		"assets/images/Monster2_full_sheet.bmp"
# define SPRITE_PATH		"assets/images/Objects_small_sheet.bmp"
# define MUSIC_PATH			"assets/sounds/title_music.wav"
# define SOUND_LASER_PATH	"assets/sounds/laser.wav"
# define SOUND_SHOT_PATH	"assets/sounds/pistol_shot.wav"
# define SOUND_RELOAD_PATH	"assets/sounds/pistol_reload.wav"
# define SOUND_BUMP_PATH	"assets/sounds/bump.wav"
# define TEXTS_PATH			"assets/texts/texts.txt"
# define MAP_PATH			"./testeditor/test.test"
# define MAX_SPRITES 5

enum e_spritesheet {
	SMALL_SPRITE,
	BIG_SPRITE,
	PROJECTILE_SPRITE,
	ENEMY_SPRITE
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
	SDL_Surface		*sprite;
	SDL_Surface		*bg;
	SDL_Surface		*sprites[MAX_SPRITES];
}	t_assets;

#endif
