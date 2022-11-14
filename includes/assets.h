/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 14:38:52 by dpalacio          #+#    #+#             */
/*   Updated: 2022/11/14 12:38:07 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASSETS_H
# define ASSETS_H

# define PANELS_PATH		"assets/textures/minecraft_spritesheet.bmp"
# define SKYBOX_PATH		"assets/textures/bg.bmp"
# define FONT_PATH			"assets/fonts/sci-fi_font.bmp"
# define PROMPT_PATH		"assets/ui/prompt.bmp"
# define BUTTON_IDLE_PATH	"assets/ui/button_idle2.bmp"
# define BUTTON_SELECT_PATH	"assets/ui/button_select2.bmp"
# define BUTTON_PRESS_PATH	"assets/ui/button_press2.bmp"
# define TITLESCREEN_PATH	"assets/images/awakened3.bmp"
# define POINTER_PATH		"assets/ui/mouse_pointer.bmp"
# define MUSIC_PATH			"assets/sounds/title_music.wav"
# define LASER_PATH			"assets/sounds/laser.wav"
# define SHOT_PATH			"assets/sounds/shot.wav"
# define BUMP_PATH			"assets/sounds/bump.wav"
# define MAP_PATH			"./testeditor/test.test"

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
	SDL_Surface		*text_prompt;
	SDL_Surface		*button_idle;
	SDL_Surface		*button_select;
	SDL_Surface		*button_press;
	SDL_Surface		*title_screen_image;
	SDL_Surface		*pointer;
	SDL_Surface		*sprite;
	SDL_Surface		*bg;
}	t_assets;

#endif
