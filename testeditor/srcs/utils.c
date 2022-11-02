/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 15:48:10 by dpalacio          #+#    #+#             */
/*   Updated: 2022/11/02 15:25:30 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * Loads the texture assests.
*/
void	load_assets(t_app *app)
{
	app->assets.sprite = SDL_LoadBMP(PANELS_PATH);
}

/**
 * Loads the font or resets it.
 */
void	load_font(t_app *app)
{
	if (!app->assets.font.font)
		app->assets.font.font = SDL_LoadBMP(FONT_TX);
	if (!app->assets.font.font)
		exit_error("MSG_ERROR_FONT");
	change_font(app, 16, 0xFF000000);
}
