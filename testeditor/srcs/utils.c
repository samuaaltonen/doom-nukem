/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 15:48:10 by dpalacio          #+#    #+#             */
/*   Updated: 2022/12/29 15:26:48 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * Loads the texture assests.
*/
void	load_assets(t_app *app)
{
	app->assets.sprite = SDL_LoadBMP(PANELS_PATH);
	app->assets.objects = SDL_LoadBMP(OBJECTS_PATH);
	app->assets.ui_frame = SDL_LoadBMP(UI_FRAME_PATH);
}

/**
 * Loads the font or resets it.
 */
void	load_font(t_app *app)
{
	if (!app->assets.font.font)
		app->assets.font.font = SDL_LoadBMP(FONT_TX);
	if (!app->assets.font.font)
		exit_error(MSG_ERROR_FONT);
	change_font(app, 16, 0xFF000000);
}

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
			pixel_pos = (y * surface->pitch)
			+ (x * IMAGE_PIXEL_BYTES);
			pixel = surface->pixels + pixel_pos;
			if ((*(int *)pixel & 0xFF000000) != 0x00000000)
				put_pixel_to_surface(surface, x, y, color);
			x++;
		}
		x = 0;
		y++;
	}
}

int	check_mouse(t_point screen_pos, t_rect rect)
{
	if (screen_pos.x >= rect.x
		&& screen_pos.y >= rect.y
		&& screen_pos.x <= (rect.x + rect.w)
		&& screen_pos.y <= (rect.y + rect.h))
		return (1);
	return (0);
}
