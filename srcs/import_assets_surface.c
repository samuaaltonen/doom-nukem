/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import_assets_surface.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 18:45:28 by saaltone          #+#    #+#             */
/*   Updated: 2023/02/14 15:53:36 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * @brief Imports surface pixel data.
 * 
 * @param info 
 * @param data 
 * @param imported 
 * @return SDL_Surface* 
 */
static SDL_Surface	*get_surface(int asset_type, t_import_info *import_info)
{
	t_export_asset	asset_info;
	SDL_Surface		*surface;

	asset_info = import_info->header.asset_info[asset_type];
	if (asset_info.size > import_info->length - import_info->imported
		|| asset_info.width >= MAX_BMP_WIDTH
		|| asset_info.height >= MAX_BMP_HEIGHT
		|| asset_info.size != asset_info.width * asset_info.height
		* IMAGE_PIXEL_BYTES)
		exit_error(MSG_ERROR_IMPORT_SURFACE);
	surface = SDL_CreateRGBSurface(0, asset_info.width, asset_info.height,
			IMAGE_PIXEL_BITS, 0, 0, 0, 0);
	if (!surface)
		exit_error(MSG_ERROR_IMAGE_INIT);
	ft_memcpy(surface->pixels, import_info->data + import_info->imported,
		asset_info.size);
	import_info->imported += asset_info.size;
	import_update_progress(import_info);
	return (surface);
}

/**
 * @brief Imports all game surfaces.
 * 
 * @param app 
 * @param thread 
 * @param info 
 */
void	import_surfaces(t_app *app, t_import_info *info)
{
	app->assets.panels = get_surface(EXPORT_PANELS, info);
	app->assets.skybox = get_surface(EXPORT_SKYBOX, info);
	app->assets.font.font = get_surface(EXPORT_FONT, info);
	app->assets.ui_frame = get_surface(EXPORT_UI_FRAME, info);
	app->assets.title_screen_image = get_surface(EXPORT_TITLESCREEN, info);
	app->assets.crosshair = get_surface(EXPORT_CROSSHAIR, info);
	app->assets.pointer = get_surface(EXPORT_POINTER, info);
	app->assets.shield = get_surface(EXPORT_SHIELD, info);
	app->assets.hp = get_surface(EXPORT_HP, info);
	app->assets.energy_sprite = get_surface(EXPORT_ENERGY, info);
	app->assets.pistol_sprite = get_surface(EXPORT_PISTOL, info);
	app->assets.bullet_sprite = get_surface(EXPORT_BULLET, info);
	app->assets.meter = get_surface(EXPORT_METER, info);
	app->assets.object_icon = get_surface(EXPORT_ICON, info);
	app->assets.weapon[0] = get_surface(EXPORT_WEAPON_ENERGY, info);
	app->assets.weapon[1] = get_surface(EXPORT_WEAPON_HD, info);
	app->assets.weapon[2] = get_surface(EXPORT_WEAPON_BOW, info);
	app->assets.sprites[SMALL_SPRITE] = get_surface(EXPORT_PICKUP, info);
	app->assets.sprites[BIG_SPRITE] = get_surface(EXPORT_OBJECT, info);
	app->assets.sprites[PROJECTILE_SPRITE] = get_surface(EXPORT_SPRITE, info);
	app->assets.sprites[ENEMY_SPRITE_1] = get_surface(EXPORT_MONSTER_1, info);
	app->assets.sprites[ENEMY_SPRITE_2] = get_surface(EXPORT_MONSTER_2, info);
	app->assets.sprites[ENEMY_SPRITE_3] = get_surface(EXPORT_MONSTER_3, info);
}
