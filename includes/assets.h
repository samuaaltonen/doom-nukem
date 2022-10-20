/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 14:38:52 by dpalacio          #+#    #+#             */
/*   Updated: 2022/10/20 14:11:44 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASSETS_H
# define ASSETS_H

# include "doomnukem.h"

# define TEXTURE_PANELS "./assets/textures/minecraft_spritesheet.bmp"
# define TEXTURE_BACKGROUND "./assets/textures/bg.bmp"
# define TEXTURE_FONT "fonts/doom-nukem_font.bmp"
# define TEXTURE_BUTTON "assets/ui/button_iddle.bmp"
# define MAP_PATH "./testeditor/test.test"

/**
 * Texture type enumeration.
*/
/* enum e_texture {
	FLOOR_STONE			= 0,
	FLOOR_LAMINATE		= 1,
	FLOOR_STONE_BRICK	= 2,
	FLOOR_GRAVEL		= 3,
	WALL_STONE_BRICK	= 15,
	WALL_FACE			= 16,
	WALL_ENGRAVED		= 17,
	WALL_DOOR			= 18
}; */

enum e_texture {
	MINECRAFT_CONCRETE_BLACK	= 0,
	MINECRAFT_CONCRETE_MAGENTA	= 1,
	MINECRAFT_DIRT_PODZOL_SIDE	= 2,
	MINECRAFT_DIRT_PODZOL_TOP	= 3,
	MINECRAFT_END_BRICKS		= 4,
	MINECRAFT_ENDSTONE			= 5,
	MINECRAFT_GRASS_SIDE		= 6,
	MINECRAFT_SNOW_SIDE			= 7,
	MINECRAFT_LOG_OAK			= 8,
	MINECRAFT_LOG_BIRCH			= 9,
	MINECRAFT_NETHER_BRICK		= 10,
	MINECRAFT_OBSIDIAN			= 11,
	MINECRAFT_PLANK_ACACIA		= 12,
	MINECRAFT_PLANKS_OAK		= 13,
	MINECRAFT_PLANKS_BIRCH		= 14,
	MINECRAFT_NETHER_BRICK_RED	= 15,
	MINECRAFT_REDSTONE_LAMP		= 16,
	MINECRAFT_TNT				= 17
};

/**
 * Struct for font.
 */
typedef struct s_font
{
	SDL_Surface	*font;
	int         size;
}	t_font;

/**
 * Struct for all assets.
 */
typedef struct s_assets
{
	t_font		font;
	SDL_Surface		*sprite;
	SDL_Surface		*bg;
}	t_assets;

#endif
