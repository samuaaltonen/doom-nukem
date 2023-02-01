/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   level_validation_assets.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 16:46:11 by saaltone          #+#    #+#             */
/*   Updated: 2023/02/01 17:58:29 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * @brief Checks if ui element surfaces are correctly sized.
 * 
 * @param app 
 * @return t_bool 
 */
static t_bool	validate_ui_elements(t_app *app)
{
	return (app->assets.font.font->w != FONT_W
		|| app->assets.font.font->h != FONT_H
		|| app->assets.ui_frame->w != UI_FRAME_W
		|| app->assets.ui_frame->h != UI_FRAME_H
		|| app->assets.title_screen_image->w != TITLE_SCREEN_W
		|| app->assets.title_screen_image->h != TITLE_SCREEN_H
		|| app->assets.crosshair->w != CROSSHAIR_W
		|| app->assets.crosshair->h != CROSSHAIR_H
		|| app->assets.pointer->w != POINTER_W
		|| app->assets.pointer->h != POINTER_H
		|| app->assets.shield->w != SHIELD_W
		|| app->assets.shield->h != SHIELD_H
		|| app->assets.hp->w != HEALTH_W
		|| app->assets.hp->h != HEALTH_H
		|| app->assets.energy->w != ENERGY_W
		|| app->assets.energy->h != ENERGY_H
		|| app->assets.pistol->w != PISTOL_W
		|| app->assets.pistol->h != PISTOL_H
		|| app->assets.bullet->w != BULLET_W
		|| app->assets.bullet->h != BULLET_H
		|| app->assets.meter->w != METER_W
		|| app->assets.meter->h != METER_H
		|| app->assets.object_icon->w != OBJECT_ICON_W
		|| app->assets.object_icon->h != OBJECT_ICON_H);
}

/**
 * @brief Checks if sprite surfaces are correctly sized.
 * 
 * @param app 
 * @return t_bool 
 */
static t_bool	validate_sprites(t_app *app)
{
	return (app->assets.sprites[SMALL_SPRITE]->w != OBJECT_SMALL_W
		|| app->assets.sprites[SMALL_SPRITE]->h != OBJECT_SMALL_H
		|| app->assets.sprites[BIG_SPRITE]->w != OBJECT_BIG_W
		|| app->assets.sprites[BIG_SPRITE]->h != OBJECT_BIG_H
		|| app->assets.sprites[PROJECTILE_SPRITE]->w != PROJECTILE_W
		|| app->assets.sprites[PROJECTILE_SPRITE]->h != PROJECTILE_H
		|| app->assets.sprites[ENEMY_SPRITE_1]->w != ENEMY_1_W
		|| app->assets.sprites[ENEMY_SPRITE_1]->h != ENEMY_1_H
		|| app->assets.sprites[ENEMY_SPRITE_2]->w != ENEMY_2_W
		|| app->assets.sprites[ENEMY_SPRITE_2]->h != ENEMY_2_H);
}

static t_bool	validate_weapons(t_app *app)
{
	return (app->assets.weapon[0]->w != WEAPON_W
			|| app->assets.weapon[0]->h != WEAPON_H
			|| app->assets.weapon[1]->w != WEAPON_W
			|| app->assets.weapon[1]->h != WEAPON_H);
}

/**
 * @brief Checks if game assets are valid.
 * 
 * @param app 
 */
void	level_validation_assets(t_app *app)
{
	if (app->assets.panels->w != TEX_SIZE * MAX_TEX_COUNT
		|| app->assets.panels->h != TEX_SIZE
		|| app->assets.skybox->w != SKYBOX_W
		|| app->assets.skybox->h != SKYBOX_H
		|| validate_ui_elements(app)
		|| validate_sprites(app)
		|| validate_weapons(app))
		exit_error(MSG_ERROR_VALIDATION_ASSETS);
}
