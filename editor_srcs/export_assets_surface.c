/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_assets_surface.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 19:57:52 by saaltone          #+#    #+#             */
/*   Updated: 2023/01/16 21:46:41 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * @brief Calculates and updates surface exporting progress.
 * 
 * @param info 
 * @param index 
 * @param current_batch 
 */
void	calculate_progress_assets(t_import_info *info, int index,
	int current_batch)
{
	double	starting_progress;
	double	current_progress;

	starting_progress = 4.0 + 500.0 * (double)index
		/ (double)(EXPORT_SOUND_BUMP + 1);
	current_progress = 500.0 * (double)current_batch
		/ (double)info->header.asset_info[index].size
		/ (double)(EXPORT_SOUND_BUMP + 1);
	info->imported = (int)(starting_progress + current_progress);
	export_update_progress(info);
}

/**
 * @brief Writes surface pixels into file descriptor.
 * 
 * @param info 
 * @param fd 
 * @param pixels 
 * @param index 
 */
void	write_surface_pixels(t_import_info *info, int fd, t_uint8 *pixels,
	int index)
{
	int	i;
	int	write_length;

	i = 0;
	while (i < info->header.asset_info[index].size)
	{
		if (i + MAX_UNCOMPRESS_BATCH < info->header.asset_info[index].size)
			write_length = MAX_UNCOMPRESS_BATCH;
		else
			write_length = info->header.asset_info[index].size - i;
		if (write(fd, pixels + i, write_length) == -1)
			exit_error(MSG_ERROR_FILE_WRITE);
		calculate_progress_assets(info, index, i);
		i += MAX_UNCOMPRESS_BATCH;
	}
}

/**
 * @brief Exports surface pixel data.
 * 
 * @param info 
 * @param index 
 * @param fd 
 * @param path 
 */
void	export_surface(t_import_info *info, int index, int fd,
	const char *path)
{
	SDL_Surface	*surface;

	surface = bmp_to_surface(path);
	if (!surface)
		exit_error(MSG_ERROR_IMAGE_LOAD);
	info->header.asset_info[index].width = surface->w;
	info->header.asset_info[index].height = surface->h;
	info->header.asset_info[index].size = surface->w * surface->h
		* IMAGE_PIXEL_BYTES;
	write_surface_pixels(info, fd, (t_uint8 *)surface->pixels, index);
	SDL_FreeSurface(surface);
}

/**
 * @brief Exports all game images as surface pixel data.
 * 
 * @param info 
 * @param fd 
 */
void	export_surfaces(t_import_info *info, int fd)
{
	export_surface(info, EXPORT_PANELS, fd, PANELS_PATH);
	export_surface(info, EXPORT_SKYBOX, fd, SKYBOX_PATH);
	export_surface(info, EXPORT_FONT, fd, FONT_PATH);
	export_surface(info, EXPORT_UI_FRAME, fd, UI_FRAME_PATH);
	export_surface(info, EXPORT_TITLESCREEN, fd, TITLESCREEN_PATH);
	export_surface(info, EXPORT_CROSSHAIR, fd, CROSSHAIR_PATH);
	export_surface(info, EXPORT_POINTER, fd, POINTER_PATH);
	export_surface(info, EXPORT_SHIELD, fd, SHIELD_PATH);
	export_surface(info, EXPORT_HP, fd, HP_PATH);
	export_surface(info, EXPORT_PISTOL, fd, PISTOL_PATH);
	export_surface(info, EXPORT_BULLET, fd, BULLET_PATH);
	export_surface(info, EXPORT_METER, fd, METER_PATH);
	export_surface(info, EXPORT_ICON, fd, OBJECT_ICON_PATH);
	export_surface(info, EXPORT_WEAPON_HD, fd, WEAPON_HD_PATH);
	export_surface(info, EXPORT_PICKUP, fd, PICKUP_PATH);
	export_surface(info, EXPORT_OBJECT, fd, OBJECT_PATH);
	export_surface(info, EXPORT_SPRITE, fd, SPRITE_PATH);
	export_surface(info, EXPORT_MONSTER_1, fd, MONSTER_1_PATH);
	export_surface(info, EXPORT_MONSTER_2, fd, MONSTER_2_PATH);
}
