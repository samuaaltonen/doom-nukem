/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import_assets_surface.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 18:45:28 by saaltone          #+#    #+#             */
/*   Updated: 2023/01/13 18:58:22 by saaltone         ###   ########.fr       */
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
static SDL_Surface	*import_surface(int asset_type, t_import_info *import_info)
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
	app->assets.panels = import_surface(EXPORT_PANELS, info);
	app->assets.skybox = import_surface(EXPORT_SKYBOX, info);
	app->assets.font.font = import_surface(EXPORT_FONT, info);
	app->assets.ui_frame = import_surface(EXPORT_UI_FRAME, info);
	app->assets.title_screen_image = import_surface(EXPORT_TITLESCREEN, info);
	app->assets.crosshair = import_surface(EXPORT_CROSSHAIR, info);
	app->assets.pointer = import_surface(EXPORT_POINTER, info);
	app->assets.shield = import_surface(EXPORT_SHIELD, info);
	app->assets.hp = import_surface(EXPORT_HP, info);
	app->assets.pistol = import_surface(EXPORT_PISTOL, info);
	app->assets.bullet = import_surface(EXPORT_BULLET, info);
	app->assets.meter = import_surface(EXPORT_METER, info);
	app->assets.object_icon = import_surface(EXPORT_ICON, info);
	app->assets.weapon = import_surface(EXPORT_WEAPON_HD, info);
	app->assets.sprites[SMALL_SPRITE] = import_surface(EXPORT_PICKUP, info);
	app->assets.sprites[BIG_SPRITE] = import_surface(EXPORT_OBJECT, info);
	app->assets.sprites[PROJECTILE_SPRITE] = import_surface(EXPORT_SPRITE,
			info);
	app->assets.sprites[ENEMY_SPRITE_1] = import_surface(EXPORT_MONSTER_1,
			info);
	app->assets.sprites[ENEMY_SPRITE_2] = import_surface(EXPORT_MONSTER_2,
			info);
}
