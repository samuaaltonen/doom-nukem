/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex_icons.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 15:36:43 by ssulkuma          #+#    #+#             */
/*   Updated: 2023/02/20 12:43:18 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * @brief Sets correct coordinate points and size for the icon rectangles.
 * 
 * @param rect
 * @param point
 * @param size
*/
void	set_icon_rect(t_rect *rect, t_point point, t_point size)
{
	rect->x = point.x;
	rect->y = point.y;
	rect->w = size.x;
	rect->h = size.y;
}

/**
 * @brief Gets the max amount of the asset based on what asset it is.
 * 
 * @param app
 * @param asset
 * @return int
*/
static int	find_max(t_app *app, SDL_Surface *asset)
{
	if (asset == app->assets.sprite)
		return (MAX_TEX_COUNT);
	if (asset == app->assets.objects && app->active)
		return (MAX_DECOR_COUNT);
	if (asset == app->assets.objects)
		return (MAX_UNIQUE_OBJECTS);
	return (0);
}

/**
 * @brief Defines size of icon to either 32x32 or 64x64 if the icon is
 * the middle one.
 * 
 * @param index
 * @param point
 * @return t_point
*/
static t_point	get_icon_size(int index, t_point *point)
{
	if (index == 2)
	{
		point->y -= 14;
		return ((t_point){ICON_SIZE, ICON_SIZE});
	}
	else
		return ((t_point){SMALL_ICON, SMALL_ICON});
}

/**
 * @brief Renders five icons on the help menu sidebar, where the icon in
 * the middle is bigger than the two on the left and right.
 * 
 * @param app
 * @param point
 * @param id
 * @param asset
*/
void	render_icons(t_app *app, t_point point, int id, SDL_Surface *asset)
{
	t_rect		src;
	t_rect		icon;
	int			index;
	int			tex;

	index = -1;
	while (++index < 5)
	{
		tex = TEX_SIZE * ((index + id - 2) % (find_max(app, asset)));
		if (tex < 0 && asset == app->assets.objects && !app->active)
			tex += TEX_SIZE * MAX_UNIQUE_OBJECTS;
		if (tex < 0 && asset == app->assets.objects && app->active)
			tex += TEX_SIZE * MAX_DECOR_COUNT;
		if (asset == app->assets.objects)
			set_icon_rect(&src, (t_point){0, tex},
				(t_point){TEX_SIZE, TEX_SIZE});
		else
			set_icon_rect(&src, (t_point){tex, 0},
				(t_point){TEX_SIZE, TEX_SIZE});
		set_icon_rect(&icon, point, get_icon_size(index, &point));
		blit_surface(asset, &src, app->surface, &icon);
		point.x += (SMALL_ICON) + 10 + (SMALL_ICON * (index == 2));
		point.y += 14 * (index == 2);
	}
	render_ui_frame(app, (t_rect){108, point.y - 14, 66, 66}, 1, 0);
}

/**
 * @brief Renders same sized player menu icons on the help menu sidebar.
 * 
 * @param app
 * @param asset
 * @param point
 * @param max
*/
void	render_player_icons(t_app *app, SDL_Surface *asset,
										t_point point, int max)
{
	t_rect		src;
	t_rect		icon;
	int			index;
	int			start_x;

	index = 0;
	start_x = point.x;
	while (index < max)
	{
		if (max == MAX_WEAPONS)
			set_icon_rect(&src, (t_point){0, TEX_SIZE * (index + 5)},
				(t_point){TEX_SIZE, TEX_SIZE});
		else
			set_icon_rect(&src, (t_point){0, TEX_SIZE * (index)},
				(t_point){TEX_SIZE, TEX_SIZE});
		set_icon_rect(&icon, point, (t_point){SMALL_ICON, SMALL_ICON});
		blit_surface(asset, &src, app->surface, &icon);
		point.x += (SMALL_ICON) + 10;
		if (index % 5 == 0 && index != 0)
		{
			point.y += (SMALL_ICON) + 10;
			point.x = start_x;
		}
		index++;
	}
}
