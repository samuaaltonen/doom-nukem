/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 15:48:10 by dpalacio          #+#    #+#             */
/*   Updated: 2023/01/05 13:04:33 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * Loads the texture assests.
*/
void	load_assets(t_app *app)
{
	app->assets.sprite = bmp_to_surface(PANELS_PATH);
	app->assets.objects = bmp_to_surface(OBJECT_ICON_PATH);
	app->assets.ui_frame = bmp_to_surface(UI_FRAME_PATH);
}

/**
 * Loads the font or resets it.
 */
void	load_font(t_app *app)
{
	if (!app->assets.font.font)
		app->assets.font.font = bmp_to_surface(FONT_PATH);
	if (!app->assets.font.font)
		exit_error(MSG_ERROR_FONT);
	change_font(app, 16, 0xFF000000);
}

/**
 * Colors the given surface with the given color.
*/
void	color_surface(SDL_Surface *surface, int color)
{
	int		x;
	int		y;
	int		pixel_pos;
	char	*pixel;

	x = 0;
	y = 0;
	while (y < surface->h)
	{
		while (x < surface->w)
		{
			pixel_pos = (y * surface->pitch) + (x * IMAGE_PIXEL_BYTES);
			pixel = surface->pixels + pixel_pos;
			if ((*(int *)pixel & 0xFF000000) != 0x00000000)
				put_pixel_to_surface(surface, x, y, color);
			x++;
		}
		x = 0;
		y++;
	}
}

/**
 * Checks if mouse position is inside the given rectangle.
*/
int	check_mouse(t_point screen_pos, t_rect rect)
{
	if (screen_pos.x >= rect.x
		&& screen_pos.y >= rect.y
		&& screen_pos.x <= (rect.x + rect.w)
		&& screen_pos.y <= (rect.y + rect.h))
		return (TRUE);
	return (FALSE);
}
