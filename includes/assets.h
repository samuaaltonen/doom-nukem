/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 14:38:52 by dpalacio          #+#    #+#             */
/*   Updated: 2022/12/06 15:17:35 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASSETS_H
# define ASSETS_H

# define PANELS_PATH "assets/textures/minecraft_spritesheet.bmp"
# define SKYBOX_PATH "assets/images/skybox.bmp"
# define FONT_PATH "assets/fonts/sci-fi_font.bmp"
# define UI_FRAME_PATH "assets/ui/ui_frame.bmp"
# define TITLESCREEN_PATH "assets/images/awakened3.bmp"
# define CROSSHAIR_PATH "assets/ui/crosshair.bmp"
# define POINTER_PATH "assets/ui/mouse_pointer.bmp"
# define SHIELD_PATH "assets/ui/shield.bmp"
# define HP_PATH "assets/ui/hp.bmp"
# define METER_PATH "assets/ui/meter.bmp"
# define MUSIC_PATH "assets/sounds/title_music.wav"
# define SOUND_LASER_PATH "assets/sounds/laser.wav"
# define SOUND_SHOT_PATH "assets/sounds/shot.wav"
# define SOUND_BUMP_PATH "assets/sounds/bump.wav"
# define TEXTS_PATH "assets/texts/texts.txt"
# define SPRITE_PATH1 "assets/legacy/cannon_64.bmp"
# define SPRITE_PATH2 "assets/legacy/pillar_64.bmp"
# define MAX_SPRITES 2
# define MAP_PATH "./testeditor/test.test"//"./testmaps/slopes"

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
	SDL_Surface		*meter;
	SDL_Surface		*sprite;
	SDL_Surface		*bg;
	SDL_Surface		*sprites[MAX_SPRITES];
}	t_assets;

#endif
