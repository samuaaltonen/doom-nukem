/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex_icons.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 15:36:43 by ssulkuma          #+#    #+#             */
/*   Updated: 2022/12/08 18:10:03 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * Sets correct coordinate points and size for the icon rectangles.
*/
void	set_icon_rect(t_rect *rect, t_point point, t_point size)
{
	rect->x = point.x;
	rect->y = point.y;
	rect->w = size.x;
	rect->h = size.y;
}

/**
 * Gets the max amount of the asset based on what asset it is.
*/
static int	find_max(t_app *app, SDL_Surface *asset)
{
	if (asset == app->assets.sprite)
		return (MAX_OBJECTS);
	return (0);
}

/**
 * Defines size of icon to either 32x32 or 64x64 if the icon is the middle one.
*/
static t_point	get_icon_size(int index, t_point *point)
{
	if (index == 2)
	{
		point->y -= 14;
		return ((t_point){ICON_SIZE, ICON_SIZE});
	}
	else
		return ((t_point){ICON_SIZE / 2, ICON_SIZE / 2});
}

/**
 * Renders five icons on the help menu sidebar, where the icon in the middle
 * is bigger than the two on the left and right.
*/
void	render_icons(t_app *app, t_point point, int id, SDL_Surface *asset)
{
	t_rect		src;
	t_rect		icon;
	t_point		size;
	int			index;
	int			tex;

	index = 0;
	while (index < 5)
	{
		size = get_icon_size(index, &point);
		tex = ICON_SIZE * ((index + id - 2) % (find_max(app, asset) + 1));
		set_icon_rect(&src, (t_point){tex, 0}, size);
		set_icon_rect(&icon, point, size);
		blit_surface(asset, &src, app->surface, &icon);
		point.x += (ICON_SIZE / 2) + 10;
		if (index == 2)
		{
			point.x += (ICON_SIZE / 2);
			point.y += 14;
		}
		index++;
	}
	render_ui_frame(app, (t_rect){108, point.y - 14, 66, 66}, 1, 0);
}

/**
* Renders same sized player menu icons on the help menu sidebar.
*/
void	render_player_icons(t_app *app, SDL_Surface *asset,
										t_point point, int max)
{
	t_rect		src;
	t_rect		icon;
	int			index;
	int			start_x;

	index = 1;
	start_x = point.x;
	while (index < max)
	{
		set_icon_rect(&src, (t_point){ICON_SIZE * index, 0},
			(t_point){ICON_SIZE / 2, ICON_SIZE / 2});
		set_icon_rect(&icon, point, (t_point){ICON_SIZE / 2, ICON_SIZE / 2});
		blit_surface(asset, &src, app->surface, &icon);
		point.x += (ICON_SIZE / 2) + 10;
		if (index % 5 == 0)
		{
			point.y += (ICON_SIZE / 2) + 10;
			point.x = start_x;
		}
		index++;
	}
}
