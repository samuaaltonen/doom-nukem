/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_assets_surface.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 19:57:52 by saaltone          #+#    #+#             */
/*   Updated: 2023/01/12 15:22:35 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * @brief Exports surface pixel data.
 * 
 * @param header 
 * @param index 
 * @param fd 
 * @param path 
 */
void	export_surface(t_level_header *header, int index, int fd,
	const char *path)
{
	SDL_Surface	*surface;

	surface = bmp_to_surface(path);
	if (!surface)
		exit_error(MSG_ERROR_IMAGE_LOAD);
	header->asset_info[index].width = surface->w;
	header->asset_info[index].height = surface->h;
	header->asset_info[index].size = surface->w * surface->h
		* IMAGE_PIXEL_BYTES;
	if (write(fd, surface->pixels, header->asset_info[index].size) == -1)
		exit_error(MSG_ERROR_FILE_WRITE);
	SDL_FreeSurface(surface);
}

/**
 * @brief Exports all game images as surface pixel data.
 * 
 * @param header 
 * @param fd 
 */
void	export_surfaces(t_level_header *header, int fd)
{
	export_surface(header, EXPORT_PANELS, fd, PANELS_PATH);
	export_surface(header, EXPORT_SKYBOX, fd, SKYBOX_PATH);
	export_surface(header, EXPORT_FONT, fd, FONT_PATH);
	export_surface(header, EXPORT_UI_FRAME, fd, UI_FRAME_PATH);
	export_surface(header, EXPORT_TITLESCREEN, fd, TITLESCREEN_PATH);
	export_surface(header, EXPORT_CROSSHAIR, fd, CROSSHAIR_PATH);
	export_surface(header, EXPORT_POINTER, fd, POINTER_PATH);
	export_surface(header, EXPORT_SHIELD, fd, SHIELD_PATH);
	export_surface(header, EXPORT_HP, fd, HP_PATH);
	export_surface(header, EXPORT_PISTOL, fd, PISTOL_PATH);
	export_surface(header, EXPORT_BULLET, fd, BULLET_PATH);
	export_surface(header, EXPORT_METER, fd, METER_PATH);
	export_surface(header, EXPORT_ICON, fd, OBJECT_ICON_PATH);
	export_surface(header, EXPORT_WEAPON_HD, fd, WEAPON_HD_PATH);
	export_surface(header, EXPORT_PICKUP, fd, PICKUP_PATH);
	export_surface(header, EXPORT_OBJECT, fd, OBJECT_PATH);
	export_surface(header, EXPORT_SPRITE, fd, SPRITE_PATH);
	export_surface(header, EXPORT_MONSTER_1, fd, MONSTER_1_PATH);
	export_surface(header, EXPORT_MONSTER_2, fd, MONSTER_2_PATH);
}
